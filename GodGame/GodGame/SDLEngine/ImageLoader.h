#pragma once
#include <string>
#include <map>

struct SDL_Surface;

struct Texture
{
	std::string file;
	SDL_Surface * surface = NULL;
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

