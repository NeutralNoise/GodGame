#pragma once
#include <string>
#include "typedefs.h"

class ImageLoader;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

/** \struct Texture
 * \brief A structure representing a texture.
 *
 */

struct Texture
{
	friend ImageLoader;
	std::string file; //!< Path to the texture.
	//This should be hiden really buts its kind of needed atm.
	SDL_Texture * texture = NULL; //!< SDL2 Texture
	int width;
	int height;
	int access;
	UInt32 format;
	//Read Only

	bool CreateBlankTexture(const int &access, const int &w = -1, const int &h = -1, SDL_Renderer * r = nullptr);

	void CleanTexture();

	void GetPixels();

private:
	int RefCount = 0; //!< Not used ATM
	bool m_createdTexture = false;
};