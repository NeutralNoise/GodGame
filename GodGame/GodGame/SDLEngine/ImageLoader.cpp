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


Texture * ImageLoader::LoadTexture(const std::string &file) {
	//This shouldn't do anything.
	//std::map<std::string, Texture*>::const_iterator
	std::cout << "Loading image: " << file << "\n";
	auto iter = p_instance->m_textures.find(file);
	if (iter != p_instance->m_textures.end()) {
		return iter->second;
	}
	return p_instance->TextureLoader(file);
	{
		//TODO move this into SDL texture loading.
		/*
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
			tmp->textureData.textureTexture = newTexture;

			SDL_FreeSurface(loadedSurface);
			m_textures[file] = tmp;
			return true;
		}
		else {
			//This reloading of the textures needs a smart point or something.
			SDL_DestroyTexture(iter->second->textureData.textureTexture);
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
			tmp->textureData.textureTexture = newTexture;

			SDL_FreeSurface(loadedSurface);
			m_textures[file] = tmp;

		}
		return true;
		*/
	}
}

Texture* ImageLoader::GetTexture(const std::string &file) {
	//std::map<std::string, Texture*>::const_iterator
	auto iter = p_instance->m_textures.find(file);

	 if (iter == p_instance->m_textures.end()) {
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

void ImageLoader::AddTexture(const std::string & file, Texture* tex)
{
	//std::map<std::string, Texture*>::iterator
	auto iter = p_instance->m_textures.find(file);
	if (iter == p_instance->m_textures.end()) {
		p_instance->m_textures.emplace(file, tex);
	}
	else {
		//NOTE we might have to delete the texture here.
		iter->second = tex;
	}
}

Texture * ImageLoader::TextureLoader(const std::string & path)
{
	std::cout << "Can not loat Texture as there is no function here.\n";
	return nullptr;
}

ImageLoader * ImageLoader::p_instance = nullptr;
