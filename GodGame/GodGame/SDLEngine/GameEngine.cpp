#include "GameEngine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "ErrorEngine.h"
#include "EngineConfig.h"


GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

bool GameEngine::InitGameEngine() {
	EngineRenderer * newRenderer = new EngineRenderer(new Renderer(), WINDOW_WIDTH, WINDOW_HEIGHT,0);
	m_createdRenderer = true;
	return InitGameEngine("SDL_BASE_GAME_ENGINE", newRenderer, SDL_WINDOW_SHOWN);
}

bool GameEngine::InitGameEngine(const char * appName, EngineRenderer * renderer, const UInt32 & flags)
{
	//First we have to start the ErrorEngine
	ErrorEngine::InitErrorEngine();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		AddEngineErrorMessage(100, EngineErrorTypes::ERR_TYPE_FATEL, "Failed to start SDL2");
		return false;
	}

	SDL_version version;
	SDL_VERSION(&version);
	std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << "\n";

	p_window = SDL_CreateWindow("GodGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer->window_width,
		renderer->window_height, flags);

	if (p_window == NULL) {
		AddEngineErrorMessage(101, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Window\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
		return false;
	}


	p_renderer = renderer;
	bool rendererInit = renderer->InitRenderer(p_window);

	if (!rendererInit) {
		//Add a better error message.
		AddEngineErrorMessage(102, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create SDL2 Renderer\n" + std::string("Failed with error: " + std::string(SDL_GetError())));
		return false;
	}

	std::cout << p_renderer->GetVersionString() << "\n";

	//TODO this is jenky and needs to be replaced for when loading textures
	//p_renderer->sdl_renderer = SDL_GetRenderer(p_window);


	//Start PNG loading.
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "Failed to start SDL2_Image\n";
		AddEngineErrorMessage(103, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to start SDL2_Image\n" + std::string("Failed with error: " + std::string(IMG_GetError())));
		return false;
	}
	if (TTF_Init() == -1)
	{
		AddEngineErrorMessage(103, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to start SDL2_TTF\n" + std::string("Failed with error: " + std::string(TTF_GetError())));
		return false;
	}

	m_isRunning = true;
	return true;
}

void GameEngine::CloseGameEngine() {
	//SDL_DestroyRenderer(p_renderer->sdl_renderer); Done else where now
	delete p_renderer->camera;
	//delete p_renderer; This should be done by the user
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	m_isRunning = false;
}

void GameEngine::Draw()
{
	p_renderer->renderer->OnDraw();
}

void GameEngine::RenderCopy(Texture * tex, const Rect *rect, const Rect *winRect) {

	//Convert a engine rect to an SDL2 Rect
	auto RectToSDLRect = [](Rect r){
		//Some type punning
		SDL_Rect rtn = *(SDL_Rect*)&r;
		return rtn;
	};

	SDL_Rect sdlrect;
	if (rect) {
		sdlrect = RectToSDLRect(*rect);
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect = RectToSDLRect(*winRect);
			SDL_RenderCopy(p_renderer->sdl_renderer, tex->texture, &sdlrect, &sdlwinRect);
		}
		else {
			SDL_RenderCopy(p_renderer->sdl_renderer, tex->texture, &sdlrect, NULL);
		}
	}
	else {
		if (winRect) {
			SDL_Rect sdlwinRect;
			sdlwinRect = RectToSDLRect(*winRect);
			SDL_RenderCopy(p_renderer->sdl_renderer, tex->texture, NULL, &sdlwinRect);
		}
		else {
			SDL_RenderCopy(p_renderer->sdl_renderer, tex->texture, NULL, NULL);
		}
	}

}

void GameEngine::ClearScreen() {
	//SDL_RenderClear(p_renderer->sdl_renderer);
}

void GameEngine::UpdateWindow() {
	//TODO this needs to be moved.
	//SDL_RenderPresent(p_renderer->sdl_renderer);
	p_renderer->renderer->OnUpdate();
}

void GameEngine::EngineWait(const int &delay) {
	SDL_Delay(delay);
}

void GameEngine::SetRenderer(Renderer * renderer)
{
	if (p_renderer) {
		if (m_createdRenderer) {
			delete p_renderer->renderer;
		}
		p_renderer->renderer = renderer;
	}
	else {
		p_renderer = new EngineRenderer(new Renderer(), WINDOW_HEIGHT, WINDOW_WIDTH,0);
		p_renderer->renderer = renderer;
		m_createdRenderer = true;
	}
}

bool GameEngine::m_isRunning = false;
SDL_Window * GameEngine::p_window = NULL;
EngineRenderer * GameEngine::p_renderer = nullptr;
bool GameEngine::m_createdRenderer = false;
