#ifndef RENDER_BATCH_OPENGL_H_INCLUDED
#define RENDER_BATCH_OPENGL_H_INCLUDED
#include <vector>
#include "Vertex.h"
#include "../../typedefs.h"
#include "../../EngineConfig.h"
#include "../../Renderer.h"
#include <iostream>
struct VertexQuard
{
	Vertex points[4];
};

struct RenderBatchOpenGL
{
	RenderBatchOpenGL() {
		data = new Vertex[MAX_BATCH_VERTICES];
		indices = new UInt32[MAX_BATCH_INDICES];
	}
	Int32 AddQuard(const RenderObject &ro) {
		if (quardCount == MAX_RENDER_OBJECTS) {
			return -1;
		}
		GenerateVertexs(ro);
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
	};

	void Destroy() {
		//delete data;
		delete[] data;
		delete[] indices;
	};

	//std::vector<Vertex>* data = nullptr;
	//std::vector<UInt32>* indices = nullptr;
	Vertex* data = nullptr;
	UInt32 * indices = nullptr;
	UInt32 count = 0; //!< The number of indices to draw.
	UInt32 quardCount = 0;
private:
	void GenerateVertexs(const RenderObject &ro) {

		bool translate = ro.translateWithCamera;
		//bool translate = false;

		//OpenGL renders starting from the Bottom left working around counter clockwise
		//Top left
		vq.points[0].position.x = ro.x;
		vq.points[0].position.y = ro.y;
		vq.points[0].colour = c1;
		vq.points[0].uv.x = 0.0f;
		vq.points[0].uv.y = 0.0f;
		vq.points[0].translate = translate;
		//Top right
		vq.points[1].position.x = ro.x + ro.width;
		vq.points[1].position.y = ro.y;
		vq.points[1].colour = c2;
		vq.points[1].uv.x = 1.0f;
		vq.points[1].uv.y = 0.0f;
		vq.points[1].translate = translate;
		//Bottom right
		vq.points[2].position.x = ro.x + ro.width;
		vq.points[2].position.y = ro.y + ro.height;
		vq.points[2].colour = c3;
		vq.points[2].uv.x = 1.0f;
		vq.points[2].uv.y = 1.0f;
		vq.points[2].translate = translate;
		//Bottom left
		vq.points[3].position.x = ro.x;
		vq.points[3].position.y = ro.y + ro.height;
		vq.points[3].colour = c4;
		vq.points[3].uv.x = 0.0f;
		vq.points[3].uv.y = 1.0f;
		vq.points[3].translate = translate;
	};
	UInt32 m_vertexIndex = 0;

	const glm::vec4 c1{ 1.0f,0.0f,0.0f,1.0f };
	const glm::vec4 c2{ 0.0f,1.0f,0.0f,1.0f };
	const glm::vec4 c3{ 0.0f,0.0f,1.0f,1.0f };
	const glm::vec4 c4{ 1.0f,1.0f,1.0f,1.0f };
	VertexQuard vq;
};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
