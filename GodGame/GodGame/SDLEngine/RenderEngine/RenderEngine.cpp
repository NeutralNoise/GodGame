#include "RenderEngine.h"
#include <iostream>
#include <algorithm>
#include "../InfoEngine.h"
#include "../ErrorEngine.h"
#include "../InfoEngine.h"

RenderEngine::RenderEngine() {
	
}

RenderEngine::~RenderEngine() {

}

bool RenderEngine::InitRenderImage(GameEngine * ge) {
	if (!ge) {
		AddEngineErrorMessage(200, EngineErrorTypes::ERR_TYPE_FATEL, "RenderEngine can not be passed nullptr");
		return false;
	}
	p_gameEngine = ge;
	EngineInfo * newInfo = new EngineInfo("rendered_textures", Engine_Info_Types::EI_TYPE_INT);
	p_layerRenderTime = new EngineInfo("layer_render_time", Engine_Info_Types::EI_TYPE_FLOAT);
	p_layerRenderTimeAvg = new EngineInfo("layer_render_time_avg", Engine_Info_Types::EI_TYPE_FLOAT);
	InfoEngine::AddEngineInfo(newInfo);
	InfoEngine::AddEngineInfo(p_layerRenderTime);
	InfoEngine::AddEngineInfo(p_layerRenderTimeAvg);
	return true;
}

void RenderEngine::AddLayer(RenderLayer * layer) {
	m_layers.push_back(layer);
}

void RenderEngine::RemoveLayer(const int &id) {
	
	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i]) {
			if (m_layers[i]->id == id) {
				delete m_layers[i];
				m_layers.erase(m_layers.begin() + i);
			}
		}
	}
}

void RenderEngine::Update() {

	if (m_layers.size() > 1) {


		//clean up a little
		for (size_t i = 0; i < m_layers.size(); i++) {
			if (m_layers[i] == nullptr) {
				m_layers.erase(m_layers.begin() + i);
			}
		}

		auto sort = [](RenderLayer * layer, RenderLayer * layer2) {
			if (layer->Sort != nullptr && layer2->Sort != nullptr) {
				return (layer->Sort() != layer2->Sort());
			}
			else if (layer->Sort != nullptr) {
				return (layer->Sort());
			}
			else if (layer2->Sort != nullptr) {
				return (layer2->Sort());
			}
			else {
				if (layer->layer < layer2->layer) {
					return true;
				}
			}
			return false;
		};



		std::sort(m_layers.begin(), m_layers.end(), sort);

	}

}

void RenderEngine::DrawLayers() {

	m_layerTimer.StartTimer();

	Update();
	p_layerRenderTimeAvg->fdata = 0;
	int numLayers = 0;
	for (size_t i = 0; i < m_layers.size(); i++) {
		m_layerAvgTimer.StartTimer();
		if (m_layers[i]->Draw != nullptr) {
			m_layers[i]->Draw();
		}
		else {
			DrawLayer(m_layers[i]);
		}
		p_layerRenderTimeAvg->fdata += m_layerAvgTimer.GetTime();
		numLayers++;
	}
	p_layerRenderTimeAvg->fdata = p_layerRenderTimeAvg->fdata / numLayers;
	p_layerRenderTime->fdata = m_layerTimer.GetTime();

}

void RenderEngine::DrawLayer(RenderLayer * layer) {
	EngineInfo* tmpInfo = InfoEngine::GetEngineInfo("rendered_textures");
	tmpInfo->idata = 0;
	EngineCamera camera = *GameEngine::GetRenderer()->camera;

	//Convert a engine rect to an SDL2 Rect
	auto RenTileToRect = [](RenderTile r) {
		//Some type punning
		Rect rtn = *(Rect*)&r;
		return rtn;
	};

	for (size_t i = 0; i < m_layers.size(); i++) {
		for (size_t t = 0; t < m_layers[i]->tiles.size(); t++) {
			Rect srect;
			Rect drect;

			drect.x = m_layers[i]->tiles[t]->x;
			drect.y = m_layers[i]->tiles[t]->y;
			drect.height = m_layers[i]->tiles[t]->height;
			drect.width = m_layers[i]->tiles[t]->width;
			if (m_layers[i]->tiles[t]->translateWithCamera) {
				drect = camera.TranslateWithCamera(drect);
			}

			//TODO Tile Mapping
			//We need a cliping plane. We can do that with a camera. DONE!
			if (m_layers[i]->tiles[t]->checkCameraCollision) {
				if (camera.CollisionWithCamera(drect)) {
					/*
					srect.height = m_layers[i]->tiles[t]->height;
					srect.width = m_layers[i]->tiles[t]->width;
					*/

					srect = RenTileToRect(m_layers[i]->tiles[t]->renderTile);
					/*
					srect.x = m_layers[i]->tiles[t]->renderTile.x;
					srect.y = m_layers[i]->tiles[t]->renderTile.y;
					srect.width = m_layers[i]->tiles[t]->renderTile.width;
					srect.height = m_layers[i]->tiles[t]->renderTile.height;
					*/
					p_gameEngine->RenderCopy(m_layers[i]->tiles[t]->texture, &srect, &drect);
					tmpInfo->idata++;
				}
			}
			else {
				//Just draw this no matter where it is.

				srect = RenTileToRect(m_layers[i]->tiles[t]->renderTile);
				/*
				srect.height = m_layers[i]->tiles[t]->height;
				srect.width = m_layers[i]->tiles[t]->width;
				srect.width = m_layers[i]->tiles[t]->renderTile.width;
				srect.height = m_layers[i]->tiles[t]->renderTile.height;
				*/
				p_gameEngine->RenderCopy(m_layers[i]->tiles[t]->texture, &srect, &drect);
				tmpInfo->idata++;
			}
		}
	}
}

GameEngine * RenderEngine::p_gameEngine = nullptr;
EngineInfo * RenderEngine::p_layerRenderTime = nullptr;
EngineInfo * RenderEngine::p_layerRenderTimeAvg = nullptr;