/**
 * \file ImageLoaderOpenGL.h
 * \author NeutralNoise
 * \brief Used to load an image for OpenGL to use.
 * \version 1.0
 * \date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#pragma once
#include "../../ImageLoader.h"

/**
 * \brief Loads an image and stores it on the GPU.
 * 
*/

class ImageLoaderOpenGL :  public ImageLoader
{
public:
	/**
	 * \brief Loads an image.
	 * 
	 * \param path File path to the image.
	 * \return Texture* Pointer to the texture.
	 * \see Texture
	*/
	Texture * TextureLoader(const std::string &path) override;
private:

};