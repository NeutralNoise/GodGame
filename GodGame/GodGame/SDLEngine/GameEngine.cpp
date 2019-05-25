#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
	return InitGameEngine("SDL_BASE_GAME_ENGINE", window_size_width, window_size_height, SDL_WINDOW_SHOWN);
}

bool GameEngine::InitGameEngine(const char * appName, const int &winWidth, const int &winHeight, const unsigned int &flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to start SDL2\n";
		return false;
	}

	SDL_version version;
	SDL_VERSION(&version);
	std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << "\n";

	p_window = SDL_CreateWindow("GodGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, flags);

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
	p_renderer = new EngineRenderer(newRenderer, winHeight, winWidth);

	//SDL_SetRenderDrawColor(p_renderer->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawColor(p_renderer->renderer, 0, 0, 0, 255);

	//Start PNG loading.
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "Failed to start SDL2_Image\n";
		std::cout << "Failed with error: " << IMG_GetError();
		return false;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "Failed to start SDL2_TTF\n";
		std::cout << "Failed with error: " << TTF_GetError();
		return false;
	}

	m_isRunning = true;
	return true;
}

void GameEngine::CloseGameEngine() {
	SDL_DestroyRenderer(p_renderer->renderer);
	delete p_renderer->camera;
	delete p_renderer;
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	TTF_Quit();
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
			SDL_RenderCopy(p_renderer->renderer, tex->texture, &sdlrect, &sdlwinRect);
		}
		else {
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
			SDL_RenderCopy(p_renderer->renderer, tex->texture, NULL, &sdlwinRect);
		}
		else {
			SDL_RenderCopy(p_renderer->renderer, tex->texture, NULL, NULL);
		}
	}

}

void GameEngine::ClearScreen() {
	SDL_RenderClear(p_renderer->renderer);
}

void GameEngine::UpdateWindow() {
	SDL_RenderPresent(p_renderer->renderer);
}

void GameEngine::EngineWait(const int &delay) {
	SDL_Delay(delay);
}

bool GameEngine::m_isRunning = false;
SDL_Window * GameEngine::p_window = NULL;
EngineRenderer * GameEngine::p_renderer = nullptr;