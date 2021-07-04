/**
 * \file Vertex.h
 * \author NeutralNoise
 * \brief Vertex structs.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include <GLM/glm.hpp>
#include "../../typedefs.h"

typedef glm::vec4 ColourRGBA;

/**
 *  \struct Vertex
 *  \brief Decribes a Vertex
 * 
*/

struct Vertex
{
	// 12 bytes
	glm::vec3 position; //!< The position of the vertex in 3D space
	// 16 bytes
	ColourRGBA colour;	//!< The colour of the vertex.
	// 8 bytes
	glm::vec2 uv;		//!< The UV cords of the vertex.
	// 4 byte
	UInt32 translate; 	//!< Does the vertex translate with the camera. Set to 1 if true.
	// 4 bytes
	UInt32 texture; 	//!< The texture slot used to render this vertex.
	//TODO add stuff here for things like textures and uv maps.
};

#endif //VERTEX_H_INCLUDED
