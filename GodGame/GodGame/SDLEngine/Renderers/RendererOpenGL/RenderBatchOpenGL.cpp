#include "RenderBatchOpenGL.h"

bool RenderBatchOpenGL::DrawQuad(const RenderObject & ro)
{
	bool translate = ro.translateWithCamera;
	//OpenGL renders starting from the Bottom left working around counter clockwise
	//Top left	
	vq.points[0].position.x = ro.x;
	vq.points[0].position.y = ro.y;	
	vq.points[0].colour = c1;
	//vq.points[0].uv.x = 0.0f;
	//vq.points[0].uv.y = 0.0f;
	vq.points[0].uv = ro.renderTile.topLeft;

	//Top right
	vq.points[1].position.x = ro.x + ro.width;
	vq.points[1].position.y = ro.y;
	vq.points[1].colour = c2;
	vq.points[1].uv = ro.renderTile.topRight;
	vq.points[1].translate = translate;
	//Bottom right
	vq.points[2].position.x = ro.x + ro.width;
	vq.points[2].position.y = ro.y + ro.height;
	//vq.points[2].position = transform * m_rotateQuad[2];
	vq.points[2].colour = c3;
	vq.points[2].uv = ro.renderTile.bottomRight;
	vq.points[2].translate = translate;
	//Bottom left
	vq.points[3].position.x = ro.x;
	vq.points[3].position.y = ro.y + ro.height;
	//vq.points[3].position = transform * m_rotateQuad[3];
	vq.points[3].colour = c4;
	vq.points[3].uv = ro.renderTile.bottomLeft;
	vq.points[3].translate = translate;

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
				*(p_textureBuffer + m_textureMaxSlot) = (UInt32)ro.texture->GetTexure();
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
}

bool RenderBatchOpenGL::DrawRotatedQuad(const RenderObject & ro)
{	
	//NOTE this is slow as fuck;
	//Should this be done by the client?
	//The answer is always yes.
	/*
	orbit = glm::translate(glm::mat4(1.0f), glm::vec3(ro.x + ro.pivoitPoint.x, ro.y + ro.pivoitPoint.y, 0.0f))
		* glm::rotate(glm::mat4(1.0), glm::radians(ro.orbit_angle), { 0.0,0.0,1.0 })
		* glm::translate(glm::mat4(1.0f), glm::vec3(-(ro.x + ro.pivoitPoint.x), -(ro.y + ro.pivoitPoint.y), 0.0f));
		*/
	/*
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(ro.x, ro.y, 0.0f))
		* glm::rotate(glm::mat4(1.0), glm::radians(ro.spin_angle),
			{ 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0), { ro.width, ro.height, 1.0f });
	*/
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(ro.x , ro.y, 0.0f))
		* glm::rotate(glm::mat4(1.0), glm::radians(ro.spinAngle),
			{ 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0), { ro.width, ro.height, 1.0f });

	float normx=0.0f;
	float normy=0.0f;
	if (ro.pivoitPoint.x != 0.0f) {
		normx = ro.pivoitPoint.x / ro.width;
	}
	if (ro.pivoitPoint.y != 0.0f) {
		normy = ro.pivoitPoint.y / ro.height;
	}

	//move the vertexs of the rotate quad.
	m_rotateQuad[0].x = m_staticRotateQuad[0].x - normx;
	m_rotateQuad[0].y = m_staticRotateQuad[0].y - normy;

	m_rotateQuad[1].x = m_staticRotateQuad[1].x - normx;
	m_rotateQuad[1].y = m_staticRotateQuad[1].y - normy;

	m_rotateQuad[2].x = m_staticRotateQuad[2].x - normx;
	m_rotateQuad[2].y = m_staticRotateQuad[2].y - normy;

	m_rotateQuad[3].x = m_staticRotateQuad[3].x - normx;
	m_rotateQuad[3].y = m_staticRotateQuad[3].y - normy;

	bool translate = ro.translateWithCamera;
	//OpenGL renders starting from the Bottom left working around counter clockwise
	//Top left	
	//vq.points[0].position = orbit * transform * m_staticRotateQuad[0];
	vq.points[0].position = transform * m_rotateQuad[0];
	vq.points[0].colour = c1;
	vq.points[0].uv = ro.renderTile.topLeft;
	vq.points[0].translate = translate;

	//Top right
	//vq.points[1].position = orbit * transform * m_staticRotateQuad[1];
	vq.points[1].position = transform * m_rotateQuad[1];
	vq.points[1].colour = c2;
	vq.points[1].uv = ro.renderTile.topRight;
	vq.points[1].translate = translate;
	//Bottom right
	//vq.points[2].position = orbit * transform * m_staticRotateQuad[2];
	vq.points[2].position = transform * m_rotateQuad[2];
	vq.points[2].colour = c3;
	vq.points[2].uv = ro.renderTile.bottomRight;
	vq.points[2].translate = translate;
	//Bottom left
	//vq.points[3].position = orbit * transform * m_staticRotateQuad[3];
	vq.points[3].position = transform * m_rotateQuad[3];
	vq.points[3].colour = c4;
	vq.points[3].uv = ro.renderTile.bottomLeft;
	vq.points[3].translate = translate;

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
				*(p_textureBuffer + m_textureMaxSlot) = (UInt32)ro.texture->GetTexure();
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
}
