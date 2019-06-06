#pragma once
#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Texture;

class ImageLoader;

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
	//Read Only
private:
	int RefCount = 0; //!< Not used ATM
};

/** \class ImageLoader
 * \brief Loads and manages textures. \see Texture
 * 
 */

class ImageLoader
{
public:

	/**
	 * \brief Construct a new ImageLoader object
	 * 
	 */

	ImageLoader();

	/**
	 * \brief Destroy the ImageLoader object
	 * 
	 */

	~ImageLoader();

	/**
	 * \brief Laods a image into a texture
	 * 
	 * \param file Path to the image to load.
	 * \return true if image is loaded else false.
	 */

	static bool LoadTexture(const std::string &file);

	/**
	 * \brief Get the a Texture object
	 * 
	 * \param file Path to the image/texture to get.
	 * \return A pointer to the texture. \see Texture
	 */

	static Texture* GetTexture(const std::string &file);

private:
	static std::map<std::string, Texture*> m_textures; //!< Texture storeage. The string is the path to the image used to generate this texture.
};

