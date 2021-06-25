#ifndef TEXTURE_OPENGL_H_INCLUDED
#define TEXTURE_OPENGL_H_INCLUDED
#include "../../Texture.h"

class TextureOpenGL : public Texture
{
public:
	Texture * LoadTexture(const std::string &path) override;
	void Bind(const UInt32 &slot) override;
	void Unbind() override;

private:
	UInt32 m_textureID;
};


#endif //TEXTURE_OPENGL_H_INCLUDED
