#include "RenderEngine.h"
#include <iostream>
#include <algorithm>

RenderEngine::RenderEngine() {
	
}

RenderEngine::~RenderEngine() {

}

bool RenderEngine::InitRenderImage(GameEngine * ge) {
	if (!ge) {
		//TODO Error message
		return false;
	}
	p_gameEngine = ge;
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
	Update();

	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i]->Draw != nullptr) {
			m_layers[i]->Draw();
		}
		else {
			DrawLayer(m_layers[i]);
		}
	}

}

void RenderEngine::DrawLayer(RenderLayer * layer) {

	EngineCamera camera = *GameEngine::GetRenderer()->camera;
	//static int drawCalls = 0;
	for (size_t i = 0; i < m_layers.size(); i++) {
		for (size_t t = 0; t < m_layers[i]->tiles.size(); t++) {
			Rect srect;
			Rect drect;

			drect.x = m_layers[i]->tiles[t]->x;
			drect.y = m_layers[i]->tiles[t]->y;
			drect.height = m_layers[i]->tiles[t]->height;
			drect.width = m_layers[i]->tiles[t]->width;
			drect = camera.TranslateWithCamera(drect);

			//TODO Tile Mapping
			//We need a cliping plane. We can do that with a camera. DONE!
			if(camera.CollisionWithCamera(drect)) {
				srect.height = m_layers[i]->tiles[t]->height;
				srect.width = m_layers[i]->tiles[t]->width;
				p_gameEngine->RenderCopy(m_layers[i]->tiles[t]->texture, &srect, &drect);
				//drawCalls++;
			}
			
		}
	}
	//drawCalls = 0;
}

GameEngine * RenderEngine::p_gameEngine = nullptr;