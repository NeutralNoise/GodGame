#pragma once
#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Texture;

struct Texture
{
	std::string file;
	//This should be hiden really buts its kind of needed atm.
	SDL_Texture * texture;
	int RefCount;
};

class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	static bool LoadTexture(const std::string &file);
	static Texture* GetTexture(const std::string &file);

private:
	static std::map<std::string, Texture*> m_textures;
};

