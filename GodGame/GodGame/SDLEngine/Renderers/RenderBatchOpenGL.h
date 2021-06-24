#ifndef RENDER_BATCH_OPENGL_H_INCLUDED
#define RENDER_BATCH_OPENGL_H_INCLUDED
#include <vector>
#include "Vertex.h"
#include "../typedefs.h"
#include "../EngineConfig.h"
#include "../Renderer.h"
#include <iostream>
struct VertexQuard
{
	Vertex points[4];
};

struct RenderBatchOpenGL
{
	RenderBatchOpenGL() {
		data = new std::vector<Vertex>;
		indices = new std::vector<UInt32>;
		data->resize(MAX_BATCH_VERTICES);
		indices->resize(MAX_BATCH_INDICES);
	}
	Int32 AddQuard(const RenderObject &ro) {
		if (quardCount == MAX_RENDER_OBJECTS) {
			return -1;
		}
		VertexQuard vq = GenerateVertexs(ro);
		UInt32 startIndex = m_vertexIndex;
		UInt32 countStart = count;
		//Add the vertexs and the indexs

		//Bottom left
		data->at(m_vertexIndex) = vq.points[0];
		//indices->at(m_indicesIndex) = m_indicesIndex;
		m_vertexIndex++;
		
		//Bottom right
		data->at(m_vertexIndex) = vq.points[1];
		//indices->at(m_indicesIndex) = m_indicesIndex;
		m_vertexIndex++;

		//Top right
		data->at(m_vertexIndex) = vq.points[2];
		//indices->at(m_indicesIndex) = m_indicesIndex;
		m_vertexIndex++;

		//Top left
		data->at(m_vertexIndex) = vq.points[3];
		//indices->at(m_indicesIndex) = m_indicesIndex;
		m_vertexIndex++;

		indices->at(countStart) = startIndex;			//0 Bottom left.
		indices->at(countStart + 1) = startIndex + 2;	//1 Top Right.
		indices->at(countStart + 2) = startIndex + 3;	//2 Top left.

		indices->at(countStart + 3) = startIndex;		//0 Bottom left.
		indices->at(countStart + 4) = startIndex + 2;	//1 Top Right.
		indices->at(countStart + 5) = startIndex + 1;	//3 Bottom right.

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
		delete data;
		delete indices;
	};

	std::vector<Vertex>* data = nullptr;
	std::vector<UInt32>* indices = nullptr;
	UInt32 count = 0; //!< The number of indices to draw.
	UInt32 quardCount = 0;
private:
	VertexQuard GenerateVertexs(const RenderObject &ro) {
		VertexQuard rtn;

		bool translate = ro.translateWithCamera;
		//bool translate = false;

		//OpenGL renders starting from the Bottom left working around counter clockwise
		//Bottom left
		rtn.points[0].position.x = ro.x;
		rtn.points[0].position.y = ro.y;
		rtn.points[0].colour = { 1.0,0.0,0.0,1.0 };
		rtn.points[0].translate = translate;
		//Bottom right
		rtn.points[1].position.x = ro.x + ro.width;
		rtn.points[1].position.y = ro.y;
		rtn.points[1].colour = { 0.0,0.0,1.0,1.0 };
		rtn.points[1].translate = translate;
		//Top right
		rtn.points[2].position.x = ro.x + ro.width;
		rtn.points[2].position.y = ro.y + ro.height;
		rtn.points[2].colour = { 1.0,1.0,1.0,1.0 };
		rtn.points[2].translate = translate;
		//Top left
		rtn.points[3].position.x = ro.x;
		rtn.points[3].position.y = ro.y + ro.height;
		rtn.points[3].colour = { 0.0,1.0,0.0,1.0 };
		rtn.points[3].translate = translate;
		return rtn;
	};
	UInt32 m_vertexIndex = 0;

};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
