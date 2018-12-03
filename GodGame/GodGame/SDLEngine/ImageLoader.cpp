#include "ImageLoader.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "GameEngine.h"

ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

bool ImageLoader::LoadTexture(const std::string &file) {
	//std::map<std::string, Texture*>::const_iterator
	auto iter = m_textures.find(file);

	if (iter == m_textures.end()) {
		Texture * tmp = new Texture;

		tmp->file = file;
		SDL_Surface *loadedSurface = SDL_LoadBMP(file.c_str());
		if (loadedSurface == NULL) {
			std::cout << "Failed to load image: " << file << "\n";
			delete tmp;
			return false;
		}
		tmp->surface = SDL_ConvertSurface(loadedSurface, GameEngine::GetWindowSurface()->format, NULL);
		if (tmp->surface == NULL) {
			std::cout << "Failed to Convert image: " << file << "\n";
			SDL_FreeSurface(loadedSurface);
			delete tmp;
			return false;
		}
		
		SDL_FreeSurface(loadedSurface);
		m_textures[file] = tmp;
		return true;
	}
	else {
		SDL_FreeSurface(iter->second->surface);
		iter->second->surface = SDL_LoadBMP(file.c_str());

		if (iter->second->surface == NULL) {
			std::cout << "Failed to load image: " << file << "\n";
			return false;
		}

	}
	return true;
}

Texture* ImageLoader::GetTexture(const std::string &file) {
	//std::map<std::string, Texture*>::iterator;
	 auto iter = m_textures.find(file);

	 if (iter == m_textures.end()) {
		 std::cout << "Failed to find loaded image: " << file << "\n";
		 return nullptr;
	 }
	 return iter->second;

}

std::map<std::string, Texture*> ImageLoader::m_textures;
