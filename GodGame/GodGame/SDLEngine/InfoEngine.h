#pragma once
#include <string>
#include <map>

enum Engine_Info_Types {
	EI_TYPE_NONE,
	EI_TYPE_INT,
	EI_TYPE_UINT,
	EI_TYPE_STRING,
	EI_TYPE_ENGINE_INFO

};

struct EngineInfo
{
	std::string name;
	int type = EI_TYPE_NONE;

	union 
	{
		int idata = 0;
		unsigned int uidata;
	};
	std::string sdata;
	EngineInfo * edata = nullptr;

	EngineInfo() {

	}
	EngineInfo(const std::string &name, const int &type) {
		this->name = name;
		this->type = type;
	}

};

class InfoEngine
{
public:
	static bool AddEngineInfo(EngineInfo * info) {
		auto iter = m_info.find(info->name);

		if (iter == m_info.end()) {
			m_info[info->name] = info;
			return true;
		}
		//We could just over ride whats there. But I don't know.
		//TODO error message
		return false;
	}

	static EngineInfo* GetEngineInfo(const std::string &name) {
		auto iter = m_info.find(name);

		if (iter != m_info.end()) {
			return m_info[name];
		}
		//TODO error message
		return nullptr;
	}

	static void CleanInfoEngine() {
		for (auto iter = m_info.begin(); iter != m_info.end(); iter++) {
			delete iter->second;
		}
	}

private:
	static std::map<std::string, EngineInfo*> m_info;
};


std::map<std::string, EngineInfo*> InfoEngine::m_info;