#include "ImageLoader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
		SDL_Texture * newTexture = NULL;
		Texture * tmp = new Texture;

		tmp->file = file;
		SDL_Surface *loadedSurface = IMG_Load(file.c_str());
		if (loadedSurface == NULL) {
			std::cout << "Failed to load image: " << file << "\n";
			delete tmp;
			return false;
		}

		//Create texture from pixel surface.
		newTexture = SDL_CreateTextureFromSurface(GameEngine::GetRenderer()->sdl_renderer, loadedSurface);

		if (!newTexture) {
			std::cout << "Failed to load image: " << file << "\n";
			SDL_FreeSurface(loadedSurface);
			delete tmp;
			return false;
		}
		SDL_QueryTexture(newTexture, &tmp->format, &tmp->access, &tmp->width, &tmp->height);
		tmp->texture = newTexture;
		
		SDL_FreeSurface(loadedSurface);
		m_textures[file] = tmp;
		return true;
	}
	else {
		//This reloading of the textures needs a smart point or something.
		SDL_DestroyTexture(iter->second->texture);
		SDL_Texture * newTexture = NULL;
		Texture * tmp = new Texture;

		tmp->file = file;
		SDL_Surface *loadedSurface = IMG_Load(file.c_str());
		if (loadedSurface == NULL) {
			std::cout << "Failed to load image: " << file << "\n";
			delete tmp;
			return false;
		}

		//Create texture from pixel surface.
		newTexture = SDL_CreateTextureFromSurface(GameEngine::GetRenderer()->sdl_renderer, loadedSurface);

		if (!newTexture) {
			std::cout << "Failed to load image: " << file << "\n";
			SDL_FreeSurface(loadedSurface);
			delete tmp;
			return false;
		}

		SDL_QueryTexture(newTexture, &tmp->format, &tmp->access, &tmp->width, &tmp->height);
		SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
		tmp->texture = newTexture;

		SDL_FreeSurface(loadedSurface);
		m_textures[file] = tmp;

	}
	return true;
}

Texture* ImageLoader::GetTexture(const std::string &file) {
	//std::map<std::string, Texture*>::iterator;
	 auto iter = m_textures.find(file);

	 if (iter == m_textures.end()) {
		 std::cout << "Failed to find loaded image: " << file << "\n";
		 std::cout << "Trying to load image " << file << "\n";
		 if (LoadTexture(file)) {
			 return GetTexture(file);
		 }
		 else {
			 return nullptr;
		 }
	 }
	 return iter->second;
}

std::map<std::string, Texture*> ImageLoader::m_textures;
