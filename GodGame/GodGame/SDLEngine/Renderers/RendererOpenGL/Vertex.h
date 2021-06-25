#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include <GLM/glm.hpp>
#include "../../typedefs.h"

typedef glm::vec4 ColourRGBA;

struct Vertex
{
	glm::vec3 position; // 12 bytes
	ColourRGBA colour;	// 16 bytes
	glm::vec2 uv;		// 8 bytes
	UInt32 translate; // 1 byte
	//TODO add stuff here for things like textures and uv maps.
};

#endif //VERTEX_H_INCLUDED
