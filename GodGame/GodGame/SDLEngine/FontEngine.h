#pragma once
#include <string>
#include "ImageLoader.h"
#include "Rect.h"
//#include <SDL2/SDL_ttf.h>

typedef struct _TTF_Font TTF_Font;

struct EngineFont {
	
	TTF_Font * font = NULL;
	Texture * texture = NULL; //!< The last created texture for this font.
	int width = 0; //!< Size of the last created texture.
	int height = 0; //!< Size of the last created texture.
	int textsize = 32;
};

class FontEngine {

public:
	EngineFont * LoadFont(const std::string &file, const int &fontsize = 32);
	void CloseFontEngine();
	bool LoadFromRenderedText(const std::string &text /*,const Colour &textColour*/);
	void Draw(const Rect &pos/*, Texture * fontTex*/);
	EngineFont * GetFont(/*const std::string &file*/) { return p_font; };

private:
	EngineFont * p_font;
};