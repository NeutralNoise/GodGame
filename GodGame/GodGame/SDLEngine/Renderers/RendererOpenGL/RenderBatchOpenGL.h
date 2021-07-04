/**
 * \file RenderBatchOpenGL.h
 * \author NeutralNoise
 * \brief Decribes a vertex buffer to be rendered to the screen.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef RENDER_BATCH_OPENGL_H_INCLUDED
#define RENDER_BATCH_OPENGL_H_INCLUDED
#include <vector>
#include "Vertex.h"
#include "../../typedefs.h"
#include "../../EngineConfig.h"
#include "../../Renderer.h"
#include "DefinesOpenGL.h"
#include <iostream>
//These are used to force GLM to sse2 or avx2
//#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
//#define GLM_FORCE_AVX2
//#define GLM_FORCE_SSE2
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** 
 * \struct VertexQuad
 * \brief Describes a drawable quad.
 * 
*/

struct VertexQuard
{
	Vertex points[4]; //!< The vertexs that make up the four points of a quad.
};

/**
 * \struct RenderBatchOpenGL
 * \brief A render batch that can be rendered to the screen.
*/

struct RenderBatchOpenGL
{

	/**
	 * \brief Construct a new RenderBatchOpenGL object
	 * \see MAX_BATCH_VERTICES
	 * \see MAX_BATCH_INDICES
	 * \see MAX_TEXTURE_UNITS
	*/

	RenderBatchOpenGL() {
		data = new Vertex[MAX_BATCH_VERTICES];
		indices = new UInt32[MAX_BATCH_INDICES];
		//TODO ask OpenGL the number of texture slots we have access to.
		p_textureBuffer = new UInt32[MAX_TEXTURE_UNITS];
	}

	/**
	 * \brief Adds a RenderObejct to the render batch.
	 * 
	 * \param ro The RenderObject to add to the batch.
	 * \return Int32 Returns -1 if the RenderObject was not added due to either hitting the MAX_RENDER_OBJECTS size or MAX_TEXTURE_UNITS. Returns 1 other wise.
	 * \see RenderObject
	 * \see MAX_TEXTURE_UNITS
	 * \see MAX_RENDER_OBJECTS
	*/
	//TODO move this to the RenderBatchOpenGL.cpp file.
	Int32 AddQuard(const RenderObject &ro) {
		if (quardCount == MAX_RENDER_OBJECTS) {
			return -1;
		}
		//We check to see if we are other the texture limit in here.
		if (!GenerateVertexs(ro)) {
			return -1;
		}
		UInt32 startIndex = m_vertexIndex;
		UInt32 countStart = count;
		//Add the vertexs and the indexs

		//Bottom left
		//Top Left
		*(data+m_vertexIndex) = vq.points[0];
		m_vertexIndex++;
		
		//Bottom right
		//Top right
		*(data + m_vertexIndex) = vq.points[1];
		m_vertexIndex++;

		//Top right
		//Bottom right
		*(data + m_vertexIndex) = vq.points[2];
		m_vertexIndex++;

		//Top left
		//Bottom Left
		*(data + m_vertexIndex) = vq.points[3];
		m_vertexIndex++;
		/*
		*(indices + (countStart)) = startIndex;			//0 Top left.
		*(indices + (countStart + 1)) = startIndex + 2;	//1 Bottom Right.
		*(indices + (countStart + 2)) = startIndex + 3;	//2 Bottom left.
		*/

		*(indices + (countStart)) = startIndex;				//0 Top left.
		*(indices + (countStart + 1)) = startIndex + 3;		//2 Bottom left.
		*(indices + (countStart + 2)) = startIndex + 2;		//1 Bottom Right.
		
		*(indices + (countStart + 3)) = startIndex;		//0 Top left.
		*(indices + (countStart + 4)) = startIndex + 2;	//1 Bottom right.
		*(indices + (countStart + 5)) = startIndex + 1;	//3 Top right.

		count += 6;

		quardCount++;
		return 1;
	};

	/**
	 * \brief Clear the render batch.
	 * 
	 * \warning This doesn't delete any memory just resets the counters back to zero/-1.
	*/

	void Clear() {
		m_vertexIndex = 0;
		count = 0;
		quardCount = 0;
		//Clear the texture buffer
		m_textureMaxSlot = -1;
		m_textureCache = 0;
	};

	/**
	 * \brief Destroys the render batch by deleting any allocated memory.
	 * 
	*/

	void Destroy() {
		//delete data;
		delete[] data;
		delete[] indices;
	};

	/**
	 * \brief Calculates the position of the RenderObjects vertexs.
	 * 
	 * \param ro The RenderObject to calculate the positions of.
	 * \return bool Returns false if the MAX_TEXTURE_UNITS limit has been hit otherwise true.
	 * \see RenderObject
	 * \see MAX_TEXTURE_UNITS
	*/

	bool DrawQuad(const RenderObject &ro);

	/**
	 * \brief Calculates the position of the RenderObjects vertexs and applys a rotation transform matrix.
	 * 
	 * \param ro The RenderObject to calculate the positions of and to rotate.
	 * \return bool Returns false if the MAX_TEXTURE_UNITS limit has been hit otherwise true.
	 * \see RenderObject
	 * \see MAX_TEXTURE_UNITS
	*/

	bool DrawRotatedQuad(const RenderObject &ro);

	/**
	 * \brief Gets what texture if needed and assigns a texture slot to attach the texture to.
	 * 
	 * \param ro The RenderObject to get the texture of.
	 * \param tslot Pointer to an int that is set with the assigned texture slot.
	 * \return bool Returns false if MAX_TEXTURE_UNITS limit has beedn reached otherwise returns true.
	 * \see RenderObject
	 * \see MAX_TEXTURE_UNITS
	*/

	bool GetTextureSlot(const RenderObject &ro, Int32 * tslot) {
		//Check if we have a texture already taking up a slot.
		if (m_textureMaxSlot != -1) {
			//Add the texture to the list.
			if (m_textureCache != (UInt32)ro.texture->GetTexure()) {
				m_textureCache = (UInt32)ro.texture->GetTexure();
				//Check to see if we have the texture in the buffer.
				for (UInt32 i = 0; i < m_textureMaxSlot + 1; i++) {
					if (*(p_textureBuffer + i) == m_textureCache) {
						//We already have the texture in the buffer.
						*tslot = i;
						m_currentTextureSlot = i;
						break;
					}
				}
				//We need to add the texture to the buffer.
				if (*tslot == -1) {
					//Check to make sure we are not over the max texture units.
					if ((m_textureMaxSlot + 1) > MAX_TEXTURE_UNITS) {
						return false;
					}
					m_textureMaxSlot++;
					*tslot = m_textureMaxSlot;
					m_currentTextureSlot = *tslot;
					*(p_textureBuffer + m_textureMaxSlot) = (UInt32)ro.texture->GetTexure();
				}
			}
			else {
				*tslot = m_currentTextureSlot;
			}
		}
		else {
			//We can just add  the texture now.
			m_textureMaxSlot++;
			*tslot = m_textureMaxSlot;
			m_textureCache = (UInt32)ro.texture->GetTexure();
			m_currentTextureSlot = m_textureMaxSlot;
			*(p_textureBuffer + m_textureMaxSlot) = (UInt32)ro.texture->GetTexure();
		}
	}
	//std::vector<Vertex>* data = nullptr;
	//std::vector<UInt32>* indices = nullptr;
	Vertex* data = nullptr; //!< Stores the vertex data. \see Vertex
	UInt32 * indices = nullptr; //!< Stores the render order of the vertex data.
	UInt32 count = 0; //!< The number of indices to draw.
	UInt32 quardCount = 0; //!< The total number of quads currently in the buffer.
	UInt32 *p_textureBuffer; //!< Stores the IDs of the textures to bind and assign.
	Int32 m_textureMaxSlot = -1; //!< The currently used number of texture slots.
	Int32 m_currentTextureSlot = -1; //!<  Cache  of the last texture slot used.
private:

	/**
	 * \brief Generate the Vertexs of a RenderObject
	 * 
	 * \param ro The RenderObject to generate the Vertexs of.
	 * \return bool Returns false if no Vertexs where generated otherwise true.
	 * \see RenderObject
	*/

	bool GenerateVertexs(const RenderObject &ro) {

		//bool translate = ro.translateWithCamera;
		//bool translate = false;

		if (!ro.doesRotate) {
			return DrawQuad(ro);
		}
		else {
			return DrawRotatedQuad(ro);
		}
		//we should never get here.
		//TODO Fatel Error message.
		return false;
	};
	UInt32 m_vertexIndex = 0; //!< The index we are looking at the the data pointer array.
	//TODO remove these.
	const glm::vec4 c1{ 1.0f,0.0f,0.0f,1.0f };
	const glm::vec4 c2{ 0.0f,1.0f,0.0f,1.0f };
	const glm::vec4 c3{ 0.0f,0.0f,1.0f,1.0f };
	const glm::vec4 c4{ 1.0f,1.0f,1.0f,1.0f };

	VertexQuard vq; //!< Temporary storeage of the vertex information. \see VertexQuard
	//Texture * p_textureBuffer = nullptr;
	UInt32 m_textureCache; //!< Cache of the last texture looked at.
#if defined(ROTATE_AROUND_TOP_LEFT)
	glm::vec4 m_staticRotateQuad[4] = { {0.0f, 0.0f, 0.0f, 1.0f},
									{1.0f, 0.0f,0.0f, 1.0f},
									{1.0f, 1.0f,0.0f, 1.0f},
									{0.0f, 1.0f,0.0f, 1.0f} };
	glm::vec4 m_rotateQuad[4] = { m_staticRotateQuad[0], m_staticRotateQuad[1], m_staticRotateQuad[2], m_staticRotateQuad[3] }; //!< Quad used to rotate.
#elif defined(ROTATE_AROUND_CENTER)
	glm::vec4 m_staticRotateQuad[4] = { {-0.5f, -0.5f, 0.0f, 1.0f},
									{0.5f, -0.5f,0.0f, 1.0f},
									{0.5f, 0.5f,0.0f, 1.0f},
									{-0.5f, 0.5f,0.0f, 1.0f} };
	glm::vec4 m_rotateQuad[4] = { m_staticRotateQuad[0], m_staticRotateQuad[1], m_staticRotateQuad[2], m_staticRotateQuad[3] };
#endif
	
	glm::mat4 transform; //!< Used to rotate an quad.
	glm::mat4 orbit; //!< Used to orbit a quad around a point. \note Not used.
};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
