/**
 * \file TextureOpenGL.h
 * \author NeutralNoise
 * \brief An OpenGL texture.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef TEXTURE_OPENGL_H_INCLUDED
#define TEXTURE_OPENGL_H_INCLUDED
#include "../../Texture.h"

/**
 * \class TextureOpenGL
 * \brief Descibes an OpenGL texture.
 * 
*/

class TextureOpenGL : public Texture
{
public:

	/**
	 * \brief Loads the texture and uploads it to the GPU.
	 * 
	 * \param path File path to the texture image to load.
	 * \return Texture* Returns a pointer to the texture.
	*/

	Texture * LoadTexture(const std::string &path) override;

	/**
	 * \brief Binds the texture to be rendered.
	 * 
	 * \param slot The texture slot to bind the texture too.
	*/

	void Bind(const UInt32 &slot) override;

	/**
	 * \brief Unbind a texture.
	 * 
	*/

	void Unbind() override;

	/**
	 * \brief Sets the texture to be used.
	 * 
	 * \param tex The texture ID to use.
	*/

	void SetTexure(void * tex) override;

	/**
	 * \brief Get the Texure object
	 * 
	 * \return void* Returns the Texture ID.
	*/

	void* GetTexure() override;

private:
	UInt32 m_textureID; //!< The texture ID.
};


#endif //TEXTURE_OPENGL_H_INCLUDED
