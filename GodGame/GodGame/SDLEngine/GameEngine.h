#pragma once

#include "Rect.h"

struct SDL_Window;
struct SDL_Surface;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool InitGameEngine();
	void CloseGameEngine();

	void BlitToScreen(SDL_Surface * surface, const Rect *rect = nullptr, const Rect *winRect = nullptr);
	void BlitScaledToScreen(SDL_Surface * surface, const Rect *rect = nullptr, const Rect *winRect = nullptr);

	void UpdateWindow();

	void EngineWait(const int &delay);

	static const bool GetIsRunning() { return m_isRunning; };
	
	static SDL_Surface *GetWindowSurface() { return p_windowSurface; }

private:
	static SDL_Window * p_window;
	static SDL_Surface * p_windowSurface;
	static SDL_Surface * p_renderSurface;
	static SDL_Surface * p_thisRenderSurface;
	static bool m_isRunning; //!< Used by the engine to make if it is not longer running. \note Read-ony
};

