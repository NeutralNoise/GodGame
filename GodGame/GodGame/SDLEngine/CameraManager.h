#ifndef CAMERA_MANAGER_H_INCLUDED
#define CAMERA_MANAGER_H_INCLUDED

#include <unordered_map>
#include <vector>
#include <deque>
#include "typedefs.h"

class EngineCamera;

enum CameraProjectionType {
	CAM_PROJ_ORTHO
};

struct CameraSpec {
	float x;
	float y;
	float width;
	float height;
	float scale = 1.0f;
	char projection;
};

class CameraManager {
public:

	CameraManager() {};
	static void Init();
	static CameraManager* GetInstance() { return p_instance; };
	EngineCamera* AddCamera(const std::string& name, const CameraSpec& spec);
	EngineCamera* AddCamera(const Int32& id, const CameraSpec & spec);
	EngineCamera* GetCamera(const std::string &id);
	EngineCamera* GetCamera(const Int32 &id);
	void RemoveCamera(const std::string &id);
	void RemoveCamera(const Int32 &id);
	void SetActiveCamera(const std::string &name);
	void SetActiveCamera(const Int32 &id);
	EngineCamera* GetActiveCamera() { return p_activeCamera; }
	

private:
	EngineCamera* BuildCamera(const Int32& id, const CameraSpec& spec);
	static CameraManager * p_instance;
	std::unordered_map<Int32, EngineCamera*> m_cameras;
	std::unordered_map<std::string, Int32> m_cameraID;
	std::deque<Int32> m_freeIDs;
	Int32 m_maxCameraID = 0;
	bool m_addingStrCamera = false;
	EngineCamera* p_activeCamera = nullptr;
};


#endif //CAMERA_MANAGER_H_INCLUDED
