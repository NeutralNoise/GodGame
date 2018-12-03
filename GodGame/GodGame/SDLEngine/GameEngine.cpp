#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <iostream>

GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

bool GameEngine::InitGameEngine() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to start SDL2\n";
		return false;
	}

	SDL_version version;
	SDL_VERSION(&version);
	std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << "\n";

	p_window = SDL_CreateWindow("GodGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	if (p_window == NULL) {
		std::cout << "Failed to create SDL2 Window\n";
		std::cout << "Failed with error: " << SDL_GetError();
		return false;
	}
	p_windowSurface = SDL_GetWindowSurface(p_window);
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
	SDL_DestroyWindow(p_window);
	SDL_Quit();
	m_isRunning = false;
}

void GameEngine::BlitToScreen(SDL_Surface * surface, const Rect *rect, const Rect *winRect) {
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
			SDL_BlitSurface(surface, &sdlrect, p_windowSurface, &sdlwinRect);
		}
		else {
			SDL_BlitSurface(surface, &sdlrect, p_windowSurface, NULL);
		}
	}
	else {
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect.x = winRect->x;
			sdlwinRect.y = winRect->y;
			SDL_BlitSurface(surface, NULL, p_windowSurface, &sdlwinRect);
		}
		else {
			SDL_BlitSurface(surface, NULL, p_windowSurface, NULL);
		}
	}
}

void GameEngine::BlitScaledToScreen(SDL_Surface * surface, const Rect *rect, const Rect *winRect) {
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
			SDL_BlitScaled(surface, &sdlrect, p_windowSurface, &sdlwinRect);
		}
		else {
			SDL_BlitScaled(surface, &sdlrect, p_windowSurface, NULL);
		}
	}
	else {
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect.x = winRect->x;
			sdlwinRect.y = winRect->y;
			sdlwinRect.w = winRect->width;
			sdlwinRect.h = winRect->height;
			SDL_BlitScaled(surface, NULL, p_windowSurface, &sdlwinRect);
		}
		else {
			SDL_BlitScaled(surface, NULL, p_windowSurface, NULL);
		}
	}
}

void GameEngine::UpdateWindow() {
	BlitToScreen(p_renderSurface);
	SDL_UpdateWindowSurface(p_window);
	SDL_FillRect(p_windowSurface, NULL, 0x000000);
}

void GameEngine::EngineWait(const int &delay) {
	SDL_Delay(delay);
}

bool GameEngine::m_isRunning = false;
SDL_Surface * GameEngine::p_windowSurface = NULL;
SDL_Window * GameEngine::p_window = NULL;
SDL_Surface * GameEngine::p_renderSurface = NULL;
SDL_Surface * GameEngine::p_thisRenderSurface = NULL;