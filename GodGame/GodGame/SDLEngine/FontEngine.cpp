#include "FontEngine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameEngine.h"

EngineFont * FontEngine::LoadFont(const std::string &file) {
	p_font = new EngineFont;
	p_font->font = TTF_OpenFont(file.c_str(), p_font->textsize);
	p_font->texture = new Texture;
	//DO Some struff

	return nullptr;
}

void FontEngine::CloseFontEngine() {
	if (p_font != NULL) {
		if (p_font->texture != NULL) {
			if (p_font->texture->texture != NULL) {
				SDL_DestroyTexture(p_font->texture->texture);
				p_font->texture->texture = NULL;
				delete p_font->texture;
				p_font->texture = NULL;
			}
		}
		delete p_font;
	}
}

bool FontEngine::LoadFromRenderedText(const std::string &text /*,const Colour &textColour*/) {
	SDL_Color textColour;
	textColour.r = 255;
	textColour.g = 0;
	textColour.b = 0;

	//Free the last texture;
	if (p_font != NULL) {
		if (p_font->texture != NULL) {
			if (p_font->texture->texture != NULL) {
				SDL_DestroyTexture(p_font->texture->texture);
				p_font->texture->texture = NULL;
			}
		}
	}
	else {
		return false;
	}

	SDL_Surface * textSurface = TTF_RenderText_Solid(p_font->font, text.c_str(), textColour);

	if (textSurface == NULL) {
		//TODO Error Message.
		return false;
	}
	else {
		//Create texture from the surface.
		p_font->texture->texture = SDL_CreateTextureFromSurface(GameEngine::GetRenderer()->renderer, textSurface);
		if (p_font->texture->texture == NULL) {
			//TODO ErrorMessage.
		}
		else {
			p_font->width = textSurface->w;
			p_font->height = textSurface->h;
			p_font->textsize = text.size();
		}
		SDL_FreeSurface(textSurface);
	}
	return p_font->texture != NULL;
}

void FontEngine::Draw(const Rect &pos/*, Texture * fontTex*/) {
	GameEngine ge;

	Rect drect;
	drect.x = pos.x;
	drect.y = pos.y;
	drect.width = p_font->width;
	drect.height = p_font->height;

	ge.RenderCopy(p_font->texture, NULL, &drect);

}