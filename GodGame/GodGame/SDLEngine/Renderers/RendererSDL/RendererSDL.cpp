#include "RendererSDL.h"
#include <SDL2/SDL.h>
//#include "../../EngineCamera.h"
#include "../../GameEngine.h"
#include <memory>

RendererSDL::RendererSDL()
{
}

RendererSDL::~RendererSDL()
{
}

bool RendererSDL::OnInit(SDL_Window * win, const UInt32 &flags, EngineRenderer * info)
{
	p_SDLwin = win;
	p_renderer = SDL_CreateRenderer(win, -1, flags);
	if (!p_renderer) {
		AddEngineErrorMessage(102, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Renderer\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
		return false;
	}

	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);

	InitRendererInfo();

	//Create Blank Texture for rendering.
	p_renderTexture = new Texture;
	int w = GameEngine::GetRenderer()->window_width;
	int h = GameEngine::GetRenderer()->window_height;
	if (p_renderTexture->CreateBlankTexture(SDL_TEXTUREACCESS_TARGET, w, h, p_renderer) == false) {
		AddEngineErrorMessage(102, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Renderer\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
	}

	p_lightTexture = new Texture;
	if (p_lightTexture->CreateBlankTexture(SDL_TEXTUREACCESS_TARGET, w, h, p_renderer) == false) {
		AddEngineErrorMessage(102, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Renderer\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
	}

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
	//Draw everything to an offscreen texture.
	SDL_SetRenderTarget(p_renderer, p_renderTexture->texture);
	//Clear the offscreen texture.
	SDL_RenderClear(p_renderer);
	int numLayers = 0;
	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i] != nullptr) {
			m_layerAvgTimer.StartTimer(); //Times one layer.
			DrawLayer(m_layers[i]);
			p_layerRenderTimeAvg->fdata += m_layerAvgTimer.GetTime();
			numLayers++;
		}
	}

	DrawLighting();
	//DO post processing.
	//TODO post processing
	//Time post processing.
	//Switch to the the defualt render target.
	SDL_SetRenderTarget(p_renderer, NULL);
	//Render the offsreen texture to the window.
	SDL_RenderCopy(p_renderer, p_renderTexture->texture, NULL, NULL);
	//SDL_RenderCopy(p_renderer, p_lightTexture->texture, NULL, NULL);

	p_layerRenderTimeAvg->fdata = p_layerRenderTimeAvg->fdata / numLayers;
	p_layerRenderTime->fdata = m_layerTimer.GetTime();
}


void RendererSDL::OnCleanUp()
{
	p_renderTexture->CleanTexture();
	p_lightTexture->CleanTexture();
	SDL_DestroyRenderer(p_renderer);
}

void RendererSDL::DrawLighting()
{
	//WARN THIS WILL NOT WORK NOW!!!
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

	SDL_SetRenderTarget(p_renderer, p_lightTexture->texture);
	SDL_RenderClear(p_renderer);
	EngineCamera camera = *GameEngine::GetRenderer()->camera;
	//Draw the lights to the light texture.
	for (size_t i = 0; i < m_layers.size(); i++) {
		if (m_layers[i] != nullptr) {
			
			if (m_layers[i]->lights.size() != 0) {
				std::vector<RenderObject*> lights = m_layers[i]->lights;
				for (size_t l = 0; l < lights.size(); l++) {
					if (lights[l] != nullptr) {
						Rect destRect;
						destRect.x = lights[l]->x;
						destRect.y = lights[l]->y;
						destRect.height = lights[l]->height;
						destRect.width = lights[l]->width;
						if (lights[l]->translateWithCamera) {
							destRect = camera.TranslateWithCamera(destRect);
						}
						SDL_Rect sRect = RenToSDLRect(lights[l]->renderTile);
						SDL_Rect dRect = RectToSDLRect(destRect);
						SDL_RenderCopy(p_renderer, lights[l]->texture->texture, &sRect, &dRect);
					}
					else {
						break;
					}
				}
			}
		}
	}

	SDL_SetTextureBlendMode(p_lightTexture->texture, SDL_BLENDMODE_MOD);
	SDL_SetRenderTarget(p_renderer, p_renderTexture->texture);
	SDL_RenderCopy(p_renderer, p_lightTexture->texture, NULL, NULL);
	SDL_SetTextureBlendMode(p_lightTexture->texture, SDL_BLENDMODE_NONE);

}

void RendererSDL::DrawLayer(RenderObjectLayer * layer) {
	if (!layer) {
		return;
	}

	EngineCamera camera = *GameEngine::GetRenderer()->camera;

	//WARN THIS WILL NOT WORK NOW!!!!
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
			//Make the center of the render object the center.
			center.x = renObject->x + (int)(renObject->width / 2);
			center.y = renObject->y + (int)(renObject->height / 2);

			SDL_RenderCopyEx(p_renderer, renObject->texture->texture, &sRect, &dRect, renObject->angle, &center, SDL_FLIP_NONE);
			p_drawCalls->uidata++;
		}
	}
	//Render each sub lay of this layer.
	size_t subLayerSize = layer->objectLayer.size();
	for (size_t i = 0; i < layer->objectLayer.size(); i++) {
		DrawLayer(layer->objectLayer[i]);
	}
	
}
