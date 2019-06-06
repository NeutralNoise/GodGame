#pragma once
#include <string>
#include "ImageLoader.h"
#include "Rect.h"
//#include <SDL2/SDL_ttf.h>

typedef struct _TTF_Font TTF_Font;

/** \struct EngineFont
 * \brief Data structure representing a font and text.
 * 
 */

struct EngineFont {
	
	TTF_Font * font = NULL; //!< The font file to use when drawing this text.
	Texture * texture = NULL; //!< The last created texture for this font. This is rendered to the screen.
	int width = 0; //!< Size of the last created texture.
	int height = 0; //!< Size of the last created texture.
	int textsize = 32; //!< The size of the text
};

/**	\class FontEngine
 * \brief Used to generate text to draw it to the screen.
 * 
 */

class FontEngine {

public:

	/**
	 * \brief Loads a font.
	 * 
	 * \param file Path to the font file.
	 * \param fontsize The size of the font.
	 * \return Pointer to the font \see EngineFont 
	 */

	EngineFont * LoadFont(const std::string &file, const int &fontsize = 32);

	/**
	 * \brief Destroys the font and cleans up.
	 * 
	 */

	void CloseFontEngine();

	/**
	 * \brief Converts given text into a texture to be drawn.
	 * 
	 * \param text The text to be converted.
	 * \return true if text is converted else false.
	 */

	bool LoadFromRenderedText(const std::string &text /*,const Colour &textColour*/);

	/**
	 * \brief Draws the current engine font to the screen.
	 * 
	 * \param pos the screen position to draw the text.
	 */

	void Draw(const Rect &pos/*, Texture * fontTex*/);

	/**
	 * \brief Get the EngineFont object
	 * 
	 * \return Pointer to the EngineFont currentlly used.
	 */

	EngineFont * GetFont(/*const std::string &file*/) { return p_font; };

private:
	EngineFont * p_font; //!< Font used for generating text.
};