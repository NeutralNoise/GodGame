#pragma once

#include "../Renderer.h"

struct SDL_Renderer;

class RendererSDL : public Renderer
{
public:
	RendererSDL();
	~RendererSDL();

	bool OnInit(SDL_Window * win, const UInt32 &flags) override;

	void OnUpdate() override;

	void OnDraw() override;


private:

	void DrawLayer(RenderObjectLayer * layer);

	SDL_Renderer * p_renderer;
};