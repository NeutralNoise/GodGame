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
		//vq.points[0].texture = (UInt32)ro.texture->GetTexure();
		//Top right
		vq.points[1].position.x = ro.x + ro.width;
		vq.points[1].position.y = ro.y;
		vq.points[1].colour = c2;
		vq.points[1].uv.x = 1.0f;
		vq.points[1].uv.y = 0.0f;
		vq.points[1].translate = translate;
		//vq.points[1].texture = (UInt32)ro.texture->GetTexure();
		//Bottom right
		vq.points[2].position.x = ro.x + ro.width;
		vq.points[2].position.y = ro.y + ro.height;
		vq.points[2].colour = c3;
		vq.points[2].uv.x = 1.0f;
		vq.points[2].uv.y = 1.0f;
		vq.points[2].translate = translate;
		//vq.points[2].texture = (UInt32)ro.texture->GetTexure();
		//Bottom left
		vq.points[3].position.x = ro.x;
		vq.points[3].position.y = ro.y + ro.height;
		vq.points[3].colour = c4;
		vq.points[3].uv.x = 0.0f;
		vq.points[3].uv.y = 1.0f;
		vq.points[3].translate = translate;
		//vq.points[3].texture = (UInt32)ro.texture->GetTexure();
		
		Int32 tslot = -1;

		//Check if we have a texture already taking up a slot.
		if (m_textureMaxSlot != -1) {
			//Add the texture to the list.
			if (m_textureCache != (UInt32)ro.texture->GetTexure()) {
				m_textureCache = (UInt32)ro.texture->GetTexure();
				//Check to see if we have the texture in the buffer.
				for (UInt32 i = 0; i < m_textureMaxSlot + 1; i++) {
					if (*(p_textureBuffer + i) == m_textureCache) {
						//We already have the texture in the buffer.
						tslot = i;
						m_currentTextureSlot = i;
						break;
					}
				}
				//We need to add the texture to the buffer.
				if (tslot == -1) {
					//Check to make sure we are not over the max texture units.
					if ((m_textureMaxSlot + 1) > MAX_TEXTURE_UNITS) {
						return false;
					}
					m_textureMaxSlot++;
					tslot = m_textureMaxSlot;
					m_currentTextureSlot = tslot;
					*(p_textureBuffer + m_textureMaxSlot) == (UInt32)ro.texture->GetTexure();
				}
			}
			else {
				tslot = m_currentTextureSlot;
			}
		}
		else {
			//We can just add  the texture now.
			m_textureMaxSlot++;
			tslot = m_textureMaxSlot;
			m_textureCache = (UInt32)ro.texture->GetTexure();
			m_currentTextureSlot = m_textureMaxSlot;
			*(p_textureBuffer + m_textureMaxSlot) = (UInt32)ro.texture->GetTexure();
		}

		vq.points[0].texture = tslot;
		vq.points[1].texture = tslot;
		vq.points[2].texture = tslot;
		vq.points[3].texture = tslot;
		return true;
	};
	UInt32 m_vertexIndex = 0;
	const glm::vec4 c1{ 1.0f,0.0f,0.0f,1.0f };
	const glm::vec4 c2{ 0.0f,1.0f,0.0f,1.0f };
	const glm::vec4 c3{ 0.0f,0.0f,1.0f,1.0f };
	const glm::vec4 c4{ 1.0f,1.0f,1.0f,1.0f };
	VertexQuard vq;
	//Texture * p_textureBuffer = nullptr;
	UInt32 m_textureCache;
};

#endif //RENDER_BATCH_OPENGL_H_INCLUDED
