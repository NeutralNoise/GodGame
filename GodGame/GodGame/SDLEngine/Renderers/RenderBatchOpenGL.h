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

		//Add the vertexs and the indexs

		//Bottom left
		data->at(m_indicesIndex) = vq.points[0];
		indices->at(m_indicesIndex) = m_indicesIndex;
		m_indicesIndex++;
		count++;
		
		//Bottom right
		data->at(m_indicesIndex) = vq.points[1];
		indices->at(m_indicesIndex) = m_indicesIndex;
		m_indicesIndex++;
		count++;

		//Top right
		data->at(m_indicesIndex) = vq.points[2];
		indices->at(m_indicesIndex) = m_indicesIndex;
		m_indicesIndex++;
		count++;

		//Top left
		data->at(m_indicesIndex) = vq.points[3];
		indices->at(m_indicesIndex) = m_indicesIndex;
		m_indicesIndex++;
		count++;

		quardCount++;
		return 1;
	};

	void Clear() {
		m_indicesIndex = 0;
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
		//OpenGL renders starting from the Bottom left working around counter clockwise

		//Bottom left
		rtn.points[0].position.x = ro.x;
		rtn.points[0].position.y = ro.y;
		rtn.points[0].colour = { 1.0,0.0,0.0,1.0 };
		
		//Bottom right
		rtn.points[1].position.x = ro.x + ro.width;
		rtn.points[1].position.y = ro.y;
		rtn.points[1].colour = { 0.0,0.0,1.0,1.0 };

		//Top right
		rtn.points[2].position.x = ro.x + ro.width;
		rtn.points[2].position.y = ro.y + ro.height;
		rtn.points[2].colour = { 1.0,1.0,1.0,1.0 };

		//Top left
		rtn.points[3].position.x = ro.x;
		rtn.points[3].position.y = ro.y + ro.height;
		rtn.points[3].colour = { 0.0,1.0,0.0,1.0 };

		

		//Do a test print.
		/*
		std::cout << " " <<rtn.points[0].position.x << " " <<rtn.points[0].position.y << " " <<rtn.points[0].colour.x << " " <<rtn.points[0].colour.y << " " <<rtn.points[0].colour.z << " " <<std::endl;
		std::cout << " " <<rtn.points[1].position.x << " " <<rtn.points[1].position.y << " " <<rtn.points[1].colour.x << " " <<rtn.points[1].colour.y << " " <<rtn.points[1].colour.z << " " <<std::endl;
		std::cout << " " <<rtn.points[2].position.x << " " <<rtn.points[2].position.y << " " <<rtn.points[2].colour.x << " " <<rtn.points[2].colour.y << " " <<rtn.points[2].colour.z << " " <<std::endl;
		std::cout << " " <<rtn.points[3].position.x << " " <<rtn.points[3].position.y << " " <<rtn.points[3].colour.x << " " <<rtn.points[3].colour.y << " " <<rtn.points[3].colour.z << " " <<std::endl;
		*/
		return rtn;
	};
	UInt32 m_indicesIndex = 0;

};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
