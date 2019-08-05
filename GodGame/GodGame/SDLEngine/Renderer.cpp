#include "Renderer.h"

bool Renderer::OnInit(SDL_Window * win, const UInt32 &flags)
{
	//ERR_TYPE_LOW_WARN
	//ERR_TYPE_FATEL
	AddEngineErrorMessage(200, ERR_TYPE_LOW_WARN, "This is the defualt renderer. There is no other Init.");
	return false;
}

void Renderer::OnUpdate()
{
	AddEngineErrorMessage(201, ERR_TYPE_LOW_WARN, "This is the defualt renderer. There is no other Update.");
}

void Renderer::OnDraw()
{
	AddEngineErrorMessage(202, ERR_TYPE_LOW_WARN, "This is the defualt renderer. There is no other Draw.");
}

void Renderer::OnCleanUp()
{

	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i] != nullptr) {
			m_layers[i]->CleanUp();
			delete m_layers[i];
			m_layers[i] = nullptr;
		}
	}

}

void Renderer::AddRenderObject(RenderObject * renderObject)
{
	//TODO Sub render layer
	
	if (renderObject) {
		size_t main_layerSize = m_layers.size();
		if (main_layerSize == 0) {
			m_layers.push_back(new RenderObjectLayer());
		}
		//Add layers that till we get to the right one.
		if ((size_t)renderObject->layer >= main_layerSize) {
			int layerSize = m_layers.size();
			for (int i = layerSize; m_layers.size() < (size_t)renderObject->layer + 1; i++) {
				AddEmptyLayer();
			}
		}

		RenderObjectLayer * objectLayer = m_layers[renderObject->layer];
		//Create the layer if there isn't one.
		if (objectLayer == nullptr) {
			m_layers[renderObject->layer] = new RenderObjectLayer();
			objectLayer = m_layers[renderObject->layer];
		}

		//Check if the tile is at a different sublayer.
		if (renderObject->sublayer > 0) {
			int subLayerminusOne = renderObject->sublayer - 1;
			if ((size_t)subLayerminusOne >= objectLayer->objectLayer.size()) {
				int layersize = objectLayer->objectLayer.size();
				for (int i = layersize; objectLayer->objectLayer.size() < (size_t)subLayerminusOne + 1; i++) {
					AddEmptySublayer(renderObject->layer);
				}
			}

			RenderObjectLayer * subLayer = objectLayer->objectLayer[subLayerminusOne];

			if (subLayer == nullptr) {
				objectLayer->objectLayer[subLayerminusOne] = new RenderObjectLayer;
				subLayer = objectLayer->objectLayer[subLayerminusOne];
			}			

			int tileIndex = FindEmptyTile(subLayer);
			if (tileIndex != -1) {
				subLayer->renderObjects[tileIndex] = renderObject;
				//subLayer->freeTile--;
			}
			else {
				subLayer->renderObjects.push_back(renderObject);
			}

			return;
		} 

		//int tileIndex = FindEmptyTile(renderObject->layer);
		int tileIndex = FindEmptyTile(objectLayer);

		if (tileIndex != -1) {
			objectLayer->renderObjects[tileIndex] = renderObject;
			//objectLayer->freeTiles--;
		}
		else {
			objectLayer->renderObjects.push_back(renderObject);
		}
	}

}

void Renderer::ClearRenderObjects()
{
	//TODO check if tile layer is to big for to long and remove some elements.
	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i] != nullptr) {
			m_layers[i]->Clear();
		}
	}

}

void Renderer::ToggleLayerClear(const UInt32 & layer)
{
	if (layer < m_layers.size()) {
		if (m_layers[layer] != nullptr) {
			if (m_layers[layer]->needsClear == true) {
				m_layers[layer]->needsClear = false;
			}
			else {
				m_layers[layer]->needsClear = true;
			}
		}
	}
}

void Renderer::InitRendererInfo()
{
	p_layerRenderTime = new EngineInfo("layer_render_time", Engine_Info_Types::EI_TYPE_FLOAT);
	p_layerRenderTimeAvg = new EngineInfo("layer_render_time_avg", Engine_Info_Types::EI_TYPE_FLOAT);
	p_drawCalls = new EngineInfo("ren_draw_calls", Engine_Info_Types::EI_TYPE_UINT);
	InfoEngine::AddEngineInfo(p_drawCalls);
	InfoEngine::AddEngineInfo(p_layerRenderTime);
	InfoEngine::AddEngineInfo(p_layerRenderTimeAvg);
}

int Renderer::FindEmptyTile(const int &layer)
{
	//TODO use tile index tracker.
	RenderObjectLayer * tmpLayer = m_layers[layer];
	if (tmpLayer->freeTile != 0) {
		if (tmpLayer->renderObjects.size() > 0) {
			for (size_t i = 0; i < tmpLayer->renderObjects.size(); i) {
				if (tmpLayer->renderObjects[i] == nullptr) {
					return i;
				}
			}
		}
	}

#if 0
	if (tmpLayer->freeTileIndex.size() != 0) {
		if (tmpLayer->renderObjects.size() > 0) {
			int rtn = tmpLayer->freeTileIndex.front();
			tmpLayer->freeTileIndex.pop_front();
			return rtn;
		}
	}
#endif
	return -1;
}

int Renderer::FindEmptyTile(RenderObjectLayer * layer)
{
#if 0
	//TODO use tile index tracker.
	if (layer->freeTiles != 0) {
		if (layer->renderObjects.size() > 0) {
			for (size_t i = 0; i < layer->renderObjects.size(); i) {
				if (layer->renderObjects[i] == nullptr) {
					return i;
				}
			}
		}
	}

	if (layer->freeTileIndex.size() != 0) {
		if (layer->renderObjects.size() > 0) {
			int rtn = layer->freeTileIndex.back();
			layer->freeTileIndex.pop_back();
			return rtn;
		}
	}
#endif

	if (layer->freeTile < layer->maxFree) {
		return layer->freeTile++;
	}

	return -1;
}

void Renderer::AddEmptyLayer()
{
	m_layers.push_back(nullptr);
}

void Renderer::AddEmptySublayer(const int & layer)
{

	if (m_layers[layer] == nullptr) {
		m_layers[layer] = new RenderObjectLayer;
	}

	m_layers[layer]->objectLayer.push_back(nullptr);

}

EngineInfo * Renderer::p_layerRenderTime = nullptr;
EngineInfo * Renderer::p_layerRenderTimeAvg = nullptr;
EngineInfo * Renderer::p_drawCalls = nullptr;