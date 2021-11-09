#include "CameraManager.h"
#include "EngineCamera.h"
#include <assert.h>
void CameraManager::Init()
{
	if (!p_instance) {
		p_instance = new CameraManager;
	}
}

EngineCamera* CameraManager::AddCamera(const std::string& name, const CameraSpec & spec)
{
	//Check if the camera is all ready there.
	auto IDiter = m_cameraID.find(name);
	if (IDiter != m_cameraID.end()) {
		auto iter = m_cameras.find(IDiter->second);
		if (iter != m_cameras.end()) {
			*(iter->second) = EngineCamera(spec.x, spec.y, spec.width, spec.height, spec.scale);
			return iter->second;
		}

	}

	Int32 tmpID  = 0;

	if (m_freeIDs.size()) {
		tmpID = m_freeIDs.front();
		m_freeIDs.pop_front();
	}
	else {
		//m_maxCameraID starts at 0 so we just add one to it.
		tmpID = m_maxCameraID + 1;
	}

	m_addingStrCamera = true;

	return AddCamera(tmpID, spec);;
}

EngineCamera* CameraManager::AddCamera(const Int32 & id, const CameraSpec & spec)
{
	//TODO define this limit.
	if (id > 1000) {
		//TODO error.
		assert(id <= 1000);
	}

	//Do we just need to make a new camera that has a string id.
	if (m_addingStrCamera) {
		EngineCamera * newCamera = BuildCamera(id, spec);
		m_addingStrCamera = false;
		return newCamera;
	}

	//Check if the camera is there already.
	auto iter = m_cameras.find(id);
	if (iter != m_cameras.end()) {
		*(iter->second) = EngineCamera(spec.x, spec.y, spec.width, spec.height, spec.scale);
		return iter->second;
	}

	//Check to see if the ID is greater the m_maxCameraID
	//If it is greater then it lift it up to where it should be.
	if (id > m_maxCameraID) {
		for (Int32 i = m_maxCameraID; i < id; i++) {
			m_freeIDs.push_back(i);
		}
		m_maxCameraID = id;
	}
	return BuildCamera(id, spec);;
}

EngineCamera * CameraManager::GetCamera(const std::string & id)
{
	auto iter = m_cameraID.find(id);
	if (iter != m_cameraID.end()) {
		return GetCamera(iter->second);
	}
	return nullptr;
}

EngineCamera * CameraManager::GetCamera(const Int32 & id)
{
	auto iter = m_cameras.find(id);
	if (iter != m_cameras.end()) {
		return iter->second;
	}
	return nullptr;
}

void CameraManager::RemoveCamera(const std::string & id)
{
	auto iter =  m_cameraID.find(id);
	if (iter != m_cameraID.end()) {
		RemoveCamera(iter->second);
		m_cameraID.erase(id);
	}
}

void CameraManager::RemoveCamera(const Int32 & id)
{
	EngineCamera * rm = GetCamera(id);
	delete rm;
	m_cameras.erase(id);
	m_freeIDs.push_back(id);
}

void CameraManager::SetActiveCamera(const std::string & name)
{
	auto iter = m_cameraID.find(name);

	if (iter != m_cameraID.end()) {
		SetActiveCamera(iter->second);
	}
	else {
		p_activeCamera = nullptr;
	}
	assert(p_activeCamera != nullptr);
}

void CameraManager::SetActiveCamera(const Int32 & id)
{
	auto iter = m_cameras.find(id);

	if (iter != m_cameras.end()) {
		p_activeCamera = iter->second;
	}
	else {
		p_activeCamera = nullptr;
	}
	assert(p_activeCamera != nullptr);
}

EngineCamera* CameraManager::BuildCamera(const Int32 & id, const CameraSpec& spec)
{
	EngineCamera * newCamera = new EngineCamera(spec.x, spec.y, spec.width, spec.height, spec.scale);
	m_cameras.emplace(id, newCamera);
	return newCamera;
}

CameraManager * CameraManager::p_instance = nullptr;