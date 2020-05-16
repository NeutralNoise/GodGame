#pragma once

#include "../Renderer.h"

struct SDL_Renderer;
struct Texture;

/** \class RendererSDL
 * \brief Used to render things to the screen using SDL2
 * \note overides Renderer
*/

class RendererSDL : public Renderer
{
public:

	/**
	 * \brief Construct a new RendererSDL object
	 * 
	*/

	RendererSDL();

	/**
	 * \brief Destroy the RendererSDL object
	 * 
	*/

	~RendererSDL();

	/**
	 * \brief 
	 * 
	 * \param win The SDL2 window to render too.
	 * \param flags SDL2 renderer flags to set for the renderer.
	 * \return Returns true if renderer started.
	 * \warning flags will change in the future. 
	*/

	bool OnInit(SDL_Window * win, const UInt32 &flags) override;

	/**
	 * \brief Does nothing
	 * 
	*/

	void OnUpdate() override;

	/**
	 * \brief Should be called each frame and renders each layer and sublayer
	 * 
	*/

	void OnDraw() override;

	/**
	 * \brief Cleans up the renderer and should be called when the program is closed
	 * 
	*/

	void OnCleanUp() override;

private:

	/**
	 * \brief Draws lighting objects.
	 * 
	*/

	void DrawLighting();

	/**
	 * \brief Draws an entire layer and its sublayers.
	 * 
	 * This is called in OnDraw.
	 * 
	 * \param layer The layer to draw
	*/

	void DrawLayer(RenderObjectLayer * layer);

	Texture * p_renderTexture; //!< Texture to render to offscreen.
	Texture * p_lightTexture; //!< Texture used to render lights too offscreen.
	SDL_Renderer * p_renderer; //!< SDL2 renderer used to render things to the screen.
};