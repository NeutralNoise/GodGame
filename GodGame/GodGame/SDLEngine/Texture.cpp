#include "Texture.h"
#include <SDL2/SDL.h>
#include "GameEngine.h"
#include <iostream> //TODO Remove this when doing real error messages.

bool Texture::CreateBlankTexture(const int &access, const int &w/* = 0*/, const int &h/* = 0*/, SDL_Renderer * r /*= nullptr*/)
{
	SDL_Renderer * tmpRenderer;
	if (r == nullptr) {
		tmpRenderer = GameEngine::GetRenderer()->sdl_renderer;
	}
	else {
		tmpRenderer = r;
	}

	if (!tmpRenderer) {
		//TODO Error message about texture not having a renderer.
		return false;
	}

	SDL_RendererInfo info;

	if (SDL_GetRendererInfo(tmpRenderer, &info) < 0) {
		//TODO Error Message
		return false;
	}

	width = w;

	if (width == -1) {
		width = info.max_texture_width;
	}
	height = h;

	if (height == -1) {
		height = info.max_texture_height;
	}

	//SDL_TEXTUREACCESS_TARGET
	format = SDL_PIXELFORMAT_RGBA8888;
	this->access = access;
	this->textureData.textureTexture = SDL_CreateTexture(tmpRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);

	if (this->textureData.textureTexture == NULL) {
		//TODO error message
		return false;
	}
	UInt32 Testformat;
	SDL_QueryTexture(this->textureData.textureTexture, &Testformat, NULL, NULL, NULL);

	m_createdTexture = true;

	return true;
}

Texture* Texture::LoadTexture(const std::string & path)
{
	std::cout << "Can not load Texture as there is no function here\n";
	return nullptr;
}

void Texture::CleanTexture()
{
	if (m_createdTexture == true) {
		SDL_DestroyTexture(this->textureData.textureTexture);
		m_createdTexture = false;
	}
}
