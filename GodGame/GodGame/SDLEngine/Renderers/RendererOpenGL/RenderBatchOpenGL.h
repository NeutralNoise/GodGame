#ifndef RENDER_BATCH_OPENGL_H_INCLUDED
#define RENDER_BATCH_OPENGL_H_INCLUDED
#include <vector>
#include "Vertex.h"
#include "../../typedefs.h"
#include "../../EngineConfig.h"
#include "../../Renderer.h"
#include "DefinesOpenGL.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct VertexQuard
{
	Vertex points[4];
};

struct RenderBatchOpenGL
{
	RenderBatchOpenGL() {
		data = new Vertex[MAX_BATCH_VERTICES];
		indices = new UInt32[MAX_BATCH_INDICES];
		//TODO ask OpenGL the number of texture slots we have access to.
		p_textureBuffer = new UInt32[MAX_TEXTURE_UNITS];
	}
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

		*(indices + (countStart)) = startIndex;			//0 Top left.
		*(indices + (countStart + 1)) = startIndex + 2;	//1 Bottom Right.
		*(indices + (countStart + 2)) = startIndex + 3;	//2 Bottom left.

		*(indices + (countStart + 3)) = startIndex;		//0 Top left.
		*(indices + (countStart + 4)) = startIndex + 2;	//1 Bottom right.
		*(indices + (countStart + 5)) = startIndex + 1;	//3 Top right.

		count += 6;

		quardCount++;
		return 1;
	};

	void Clear() {
		m_vertexIndex = 0;
		count = 0;
		quardCount = 0;
		//Clear the texture buffer
		m_textureMaxSlot = -1;
		m_textureCache = 0;
	};

	void Destroy() {
		//delete data;
		delete[] data;
		delete[] indices;
	};

	bool DrawQuad(const RenderObject &ro);
	bool DrawRotatedQuad(const RenderObject &ro);

	//std::vector<Vertex>* data = nullptr;
	//std::vector<UInt32>* indices = nullptr;
	Vertex* data = nullptr;
	UInt32 * indices = nullptr;
	UInt32 count = 0; //!< The number of indices to draw.
	UInt32 quardCount = 0;
	UInt32 *p_textureBuffer;
	Int32 m_textureMaxSlot = -1;
	Int32 m_currentTextureSlot = -1;
private:
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
	UInt32 m_vertexIndex = 0;
	const glm::vec4 c1{ 1.0f,0.0f,0.0f,1.0f };
	const glm::vec4 c2{ 0.0f,1.0f,0.0f,1.0f };
	const glm::vec4 c3{ 0.0f,0.0f,1.0f,1.0f };
	const glm::vec4 c4{ 1.0f,1.0f,1.0f,1.0f };

	VertexQuard vq;
	//Texture * p_textureBuffer = nullptr;
	UInt32 m_textureCache;
#if defined(ROTATE_AROUND_TOP_LEFT)
	glm::vec4 m_staticRotateQuad[4] = { {0.0f, 0.0f, 0.0f, 1.0f},
									{1.0f, 0.0f,0.0f, 1.0f},
									{1.0f, 1.0f,0.0f, 1.0f},
									{0.0f, 1.0f,0.0f, 1.0f} };
	glm::vec4 m_rotateQuad[4] = { m_staticRotateQuad[0], m_staticRotateQuad[1], m_staticRotateQuad[2], m_staticRotateQuad[3] };
#elif defined(ROTATE_AROUND_CENTER)
	glm::vec4 m_staticRotateQuad[4] = { {-0.5f, -0.5f, 0.0f, 1.0f},
									{0.5f, -0.5f,0.0f, 1.0f},
									{0.5f, 0.5f,0.0f, 1.0f},
									{-0.5f, 0.5f,0.0f, 1.0f} };
	glm::vec4 m_rotateQuad[4] = { m_staticRotateQuad[0], m_staticRotateQuad[1], m_staticRotateQuad[2], m_staticRotateQuad[3] };
#endif
	
	glm::mat4 transform;
	glm::mat4 orbit;
};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
