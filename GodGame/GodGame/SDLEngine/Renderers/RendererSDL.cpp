#include "RendererSDL.h"
#include <SDL2/SDL.h>
#include "../EngineCamera.h"
#include "../GameEngine.h"

RendererSDL::RendererSDL()
{
}

RendererSDL::~RendererSDL()
{
}

bool RendererSDL::OnInit(SDL_Window * win, const UInt32 &flags)
{
	p_renderer = SDL_CreateRenderer(win, -1, flags);
	if (!p_renderer) {
		AddEngineErrorMessage(102, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Renderer\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
		return false;
	}

	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);

	InitRendererInfo();

	return true;
}

void RendererSDL::OnUpdate()
{
	//DOES SDL need to check for things.
}

void RendererSDL::OnDraw()
{
	p_drawCalls->uidata = 0;
	m_layerTimer.StartTimer(); //Times everything
	p_layerRenderTimeAvg->fdata = 0;
	int numLayers = 0;
	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i] != nullptr) {
			m_layerAvgTimer.StartTimer(); //Times one layer.
			DrawLayer(m_layers[i]);
			p_layerRenderTimeAvg->fdata += m_layerAvgTimer.GetTime();
			numLayers++;
		}
	}
	//DO post processing.
	//TODO post processing
	//Time post processing.
	p_layerRenderTimeAvg->fdata = p_layerRenderTimeAvg->fdata / numLayers;
	p_layerRenderTime->fdata = m_layerTimer.GetTime();


}

void RendererSDL::DrawLayer(RenderObjectLayer * layer) {
	if (!layer) {
		return;
	}

	EngineCamera camera = *GameEngine::GetRenderer()->camera;

	//Convert a RenderTile to an SDL2 Rect
	auto RenToRect = [](RenderTile r) {
		//Some type punning
		Rect rtn = *(Rect*)&r;
		return rtn;
	};

	//Convert a engine rect to an SDL2 Rect
	auto RectToSDLRect = [](Rect r) {
		//Some type punning
		SDL_Rect rtn = *(SDL_Rect*)&r;
		return rtn;
	};

	//Convert a engine rect to an SDL2 Rect
	auto RenToSDLRect = [](RenderTile r) {
		//Some type punning
		SDL_Rect rtn = *(SDL_Rect*)&r;
		return rtn;
	};

	RenderObject * renObject;
	size_t layerSize = layer->renderObjects.size();
	for (size_t i = 0; i < layerSize; i++) {
		renObject = layer->renderObjects[i];
		if (renObject != nullptr) {

			Rect destRect;

			destRect.x = renObject->x;
			destRect.y = renObject->y;
			destRect.height = renObject->height;
			destRect.width = renObject->width;

			if (renObject->translateWithCamera) {
				destRect = camera.TranslateWithCamera(destRect);
			}

			SDL_Rect sRect = RenToSDLRect(renObject->renderTile);
			SDL_Rect dRect = RectToSDLRect(destRect);
			SDL_Point center;
			center.x = renObject->x + (int)(renObject->width / 2);
			center.y = renObject->y + (int)(renObject->height / 2);

			SDL_RenderCopyEx(p_renderer, renObject->texture->texture, &sRect, &dRect, renObject->angle, &center, SDL_FLIP_NONE);
			p_drawCalls->uidata++;
		}
	}
	size_t subLayerSize = layer->objectLayer.size();
	for (size_t i = 0; i < layer->objectLayer.size(); i++) {
		DrawLayer(layer->objectLayer[i]);
	}
	
}