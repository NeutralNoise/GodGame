#pragma once
#include "../../ImageLoader.h"


class ImageLoaderOpenGL :  public ImageLoader
{
public:
	Texture * TextureLoader(const std::string &path) override;
private:

};