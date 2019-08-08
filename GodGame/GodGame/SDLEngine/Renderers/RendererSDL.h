#pragma once

#include "../Renderer.h"

struct SDL_Renderer;
struct Texture;

class RendererSDL : public Renderer
{
public:
	RendererSDL();
	~RendererSDL();

	bool OnInit(SDL_Window * win, const UInt32 &flags) override;

	void OnUpdate() override;

	void OnDraw() override;

	void OnCleanUp() override;

private:

	void DrawLighting();

	void DrawLayer(RenderObjectLayer * layer);
	Texture * p_renderTexture;
	Texture * p_lightTexture;
	SDL_Renderer * p_renderer;
};