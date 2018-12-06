#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

bool GameEngine::InitGameEngine() {

	const int window_size_height = 600;
	const int window_size_width = 600;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to start SDL2\n";
		return false;
	}

	SDL_version version;
	SDL_VERSION(&version);
	std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << "\n";

	p_window = SDL_CreateWindow("GodGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_width, window_size_height, SDL_WINDOW_SHOWN);

	if (p_window == NULL) {
		std::cout << "Failed to create SDL2 Window\n";
		std::cout << "Failed with error: " << SDL_GetError();
		return false;
	}
	SDL_Renderer * newRenderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

	if (newRenderer == NULL) {
		std::cout << "Failed to create SDL2 Renderer\n";
		std::cout << "Failed with error: " << SDL_GetError();
		return false;
	}
	p_renderer = new EngineRenderer(newRenderer, window_size_height, window_size_width);

	SDL_SetRenderDrawColor(p_renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	//Start PNG loading.
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "Failed to start SDL2_Image\n";
		std::cout << "Failed with error: " << IMG_GetError();
		return false;
	}


	//p_windowSurface = SDL_GetWindowSurface(p_window);
	//p_renderSurface = new SDL_Surface();
	//p_thisRenderSurface = new SDL_Surface;
	//*p_renderSurface = *p_windowSurface;
	//*p_thisRenderSurface = *p_renderSurface;

	m_isRunning = true;
	return true;
}

void GameEngine::CloseGameEngine() {
	//SDL_FreeSurface(p_renderSurface);
	//SDL_FreeSurface(p_thisRenderSurface);
	SDL_DestroyRenderer(p_renderer->renderer);
	delete p_renderer->camera;
	delete p_renderer;
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	SDL_Quit();
	m_isRunning = false;
}

void GameEngine::RenderCopy(Texture * tex, const Rect *rect, const Rect *winRect) {

	SDL_Rect sdlrect;
	if (rect) {
		sdlrect.x = rect->x;
		sdlrect.y = rect->y;
		sdlrect.w = rect->width;
		sdlrect.h = rect->height;
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect.x = winRect->x;
			sdlwinRect.y = winRect->y;
			sdlwinRect.w = winRect->width;
			sdlwinRect.h = winRect->height;
			//SDL_BlitScaled(surface, &sdlrect, p_windowSurface, &sdlwinRect);
			SDL_RenderCopy(p_renderer->renderer, tex->texture, &sdlrect, &sdlwinRect);
		}
		else {
			//SDL_BlitScaled(surface, &sdlrect, p_windowSurface, NULL);
			SDL_RenderCopy(p_renderer->renderer, tex->texture, &sdlrect, NULL);
		}
	}
	else {
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect.x = winRect->x;
			sdlwinRect.y = winRect->y;
			sdlwinRect.w = winRect->width;
			sdlwinRect.h = winRect->height;
			//SDL_BlitScaled(surface, NULL, p_windowSurface, &sdlwinRect);
			SDL_RenderCopy(p_renderer->renderer, tex->texture, NULL, &sdlwinRect);
		}
		else {
			//SDL_BlitScaled(surface, NULL, p_windowSurface, NULL);
			SDL_RenderCopy(p_renderer->renderer, tex->texture, NULL, NULL);
		}
	}

}

void GameEngine::ClearScreen() {
	SDL_RenderClear(p_renderer->renderer);
}

void GameEngine::UpdateWindow() {
	//BlitToScreen(p_renderSurface);
	//SDL_UpdateWindowSurface(p_window);
	//SDL_FillRect(p_windowSurface, NULL, 0x000000);
	SDL_RenderPresent(p_renderer->renderer);
}

void GameEngine::EngineWait(const int &delay) {
	SDL_Delay(delay);
}

bool GameEngine::m_isRunning = false;
SDL_Window * GameEngine::p_window = NULL;
EngineRenderer * GameEngine::p_renderer = nullptr;