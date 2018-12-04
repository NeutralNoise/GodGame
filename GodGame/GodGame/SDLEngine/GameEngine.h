#pragma once

#include "Rect.h"
#include "ImageLoader.h"
struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

struct EngineRenderer {
	SDL_Renderer * renderer;
	int window_height;
	int window_width;

	//Stats
	float fps;
	//We can add some more information here later.

	EngineRenderer() {
		renderer = nullptr;
		window_height = 0;
		window_width = 0;
		fps = 0.0f;
	}

	EngineRenderer(SDL_Renderer * renderer, const int &wh, const int &ww) {
		this->renderer = renderer;
		window_height = wh;
		window_width = ww;
		fps = 0.0f;
	}

};


class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool InitGameEngine();
	void CloseGameEngine();

	void RenderCopy(Texture * tex, const Rect *rect = nullptr, const Rect *winRect = nullptr);

	void ClearScreen();

	void UpdateWindow();

	void EngineWait(const int &delay);

	static const bool GetIsRunning() { return m_isRunning; };
	
	static SDL_Surface *GetWindowSurface() { return p_windowSurface; }

	static EngineRenderer *GetRenderer() { return p_renderer; };

private:
	static SDL_Window * p_window;
	//static SDL_Renderer * p_renderer;
	static SDL_Surface * p_windowSurface;
	static SDL_Surface * p_renderSurface;
	static SDL_Surface * p_thisRenderSurface;
	static EngineRenderer * p_renderer;
	static bool m_isRunning; //!< Used by the engine to make if it is not longer running. \note Read-ony
};

