#pragma once
#include <string>
#include "typedefs.h"

class ImageLoader;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

struct SDLTextureData
{
	SDL_Surface * textureSurface = nullptr;
	SDL_Texture * textureTexture = nullptr;
};

/** \class Texture
 * \brief A structure representing a texture.
 *
 */

class Texture
{
public:
	std::string file; //!< Path to the texture.
	//This should be hiden really buts its kind of needed atm.
	SDLTextureData textureData;
	//SDL_Texture * texture = NULL; //!< SDL2 Texture
	int width; //!< The width of the texture in pixels
	int height; //!< The height of the texture in pixels
	int access; //!< What SDL2 texture access this texture has.
	UInt32 format; //!< The pixel format of the texture.
	//Read Only

	/**
	 * \brief Create a BlankTexture object
	 * 
	 * \param access What SDL2 access we have to this texture.
	 * \param w The width of the texture.
	 * \param h The height of the texture.
	 * \param r Pointer to an SDL2_Renderer.
	 * \return True if texture was created.
	*/
	//TODO remove this.
	bool CreateBlankTexture(const int &access, const int &w = -1, const int &h = -1, SDL_Renderer * r = nullptr);

	virtual Texture* LoadTexture(const std::string& path);

	virtual void Bind(const UInt32 &slot) {};
	virtual void Unbind() {};

	/**
	 * \brief Cleans the texture.
	 * 
	*/
	//TODO this should be DestroyTexture
	void CleanTexture();

	/**
	 * \brief Get the Pixels of the texture.
	 * \warning currently does nothing.
	 * 
	*/

	void GetPixels();

	int RefCount = 0; //!< Not used ATM
	bool m_createdTexture = false; //!< Has this texture been created yet.
};