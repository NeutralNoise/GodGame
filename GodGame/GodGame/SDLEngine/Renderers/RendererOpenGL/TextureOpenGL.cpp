#include "TextureOpenGL.h"
#include <iostream>
#include <GL/glew.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include "ErrorOpenGL.h"

Texture * TextureOpenGL::LoadTexture(const std::string & path)
{
	unsigned char* m_LocalBuffer;
	//stbi_set_flip_vertically_on_load(1);
	this->file = path;
	int m_BPP = 0;

	m_LocalBuffer = stbi_load(path.c_str(), &(this->width), &(this->height), &m_BPP, 4);

	if (m_BPP >= 4)
		this->format = GL_RGBA8;
	else
		this->format = GL_RGB;

	GLCall(glGenTextures(1, &m_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//SDL_FreeSurface(this->textureData.textureSurface);
	return this;
}

void TextureOpenGL::Bind(const UInt32 & slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void TextureOpenGL::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void TextureOpenGL::SetTexure(void * tex)
{
	m_textureID = (UInt32)(tex);
}

void * TextureOpenGL::GetTexure()
{
	return (void *)m_textureID;
}
