#include "FontEngine.h"
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameEngine.h"
#include "ErrorEngine.h"

EngineFont * FontEngine::LoadFont(const std::string &file, const int &fontsize) {
	//I think this is reight.
	try {
		p_font = new EngineFont;
	}
	catch (const std::exception &e) {
		AddEngineErrorMessage(900, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create new font: " + std::string(e.what()));
			ErrorEngine::GetInstance()->OnFatel();
	}
	p_font->textsize = fontsize;
	p_font->font = TTF_OpenFont(file.c_str(), fontsize);
	if (!p_font->font) {
		//Should this error be in the 100s? Yes i think it should be because its an SDL2_TTF error.
		AddEngineErrorMessage(150, std::string(TTF_GetError()));
		delete p_font;
		return nullptr;
	}

	try
	{
		p_font->texture = new Texture;
	}
	catch (const std::exception& e)
	{
		AddEngineErrorMessage(901, EngineErrorTypes::ERR_TYPE_FATEL,
			"Failed to create new texture: " + std::string(e.what()));
		TTF_CloseFont(p_font->font);
		delete p_font;
		ErrorEngine::GetInstance()->OnFatel();
	}

	return p_font;
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
		//Should this be fatel.
		AddEngineErrorMessage(307, EngineErrorTypes::ERR_TYPE_FATEL,
			"No font has been created. Call FontEngine::LoadFont()");
		return false;
	}

	SDL_Surface * textSurface = TTF_RenderText_Solid(p_font->font, text.c_str(), textColour);

	if (textSurface == NULL) {
		AddEngineErrorMessage(151, std::string(TTF_GetError()));
		return false;
	}
	else {
		//Create texture from the surface.
		p_font->texture->texture = SDL_CreateTextureFromSurface(GameEngine::GetRenderer()->renderer, textSurface);
		if (p_font->texture->texture == NULL) {
			AddEngineErrorMessage(111, EngineErrorTypes::ERR_TYPE_FATEL,
				"SDL2 Unable to create surface from texture. " + std::string(SDL_GetError()));
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
