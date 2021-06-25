#include "ImageLoaderOpenGL.h"
#include "TextureOpenGL.h"

Texture * ImageLoaderOpenGL::TextureLoader(const std::string & path)
{
	TextureOpenGL * rtn = new TextureOpenGL;
	if (rtn->LoadTexture(path)) {
		m_textures.emplace(path, (Texture*)rtn);
		return (Texture*)rtn;
	}
	delete rtn;
	return nullptr;
}
