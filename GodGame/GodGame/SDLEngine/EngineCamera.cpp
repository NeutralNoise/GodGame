#include "EngineCamera.h"
#include <assert.h>
#include "CameraManager.h"

EngineCamera::EngineCamera(const float & x, const float & y, const float & width, const float & height, float scale, const char & proj)
{
	pos = Rect(x, y, width, height);
	halfWidth = width / 2;
	halfHeight = height / 2;
	centerPos.x = pos.x + halfWidth;
	centerPos.y = pos.y + halfHeight;
	this->scale = scale;
	m_projectionType = proj;
	switch (m_projectionType)
	{
	case CameraProjectionType::CAM_PROJ_ORTHO:
		projection = glm::ortho(0.0f, width, height, 0.0f);
		break;
	default:
		//TODO error message
		assert(false);
		break;
	}
}
