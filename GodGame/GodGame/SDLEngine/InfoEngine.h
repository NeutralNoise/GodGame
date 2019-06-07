#pragma once
#include <string>
#include <map>

/** \enum Engine_Info_Types
 * \brief The type of data stored in the EngineInfo structure.
 * 
 */

enum Engine_Info_Types {
	EI_TYPE_NONE, //!< Unknown data type.
	EI_TYPE_INT, //!< Data type of int.
	EI_TYPE_UINT, //!< Data type of unsigned int.
	EI_TYPE_STRING, //!< Data type of std::string.
	EI_TYPE_ENGINE_INFO //!< Data type of EngineInfo structure. \see EngineInfo
};

/** \struct EngineInfo
 * \brief A structure representing a data the engine stores.
 * 
 * This is used for statistics. Such as frames per second and number of drawn textures.
 * 
 */

struct EngineInfo
{
	std::string name; //!< The ID name.
	int type = EI_TYPE_NONE; //!< The type of data stored. \see Engine_Info_Types

	union 
	{
		int idata = 0; //!< This is where the int data is stored.
		unsigned int uidata; //!< This is where the unsigned int data is stored.
	};
	std::string sdata; //!< This is where the string data is stored.
	EngineInfo * edata = nullptr; //!< A pointer to an EngineInfo object.

	/**
	 * \brief Construct a new EngineInfo object.
	 * 
	 */

	EngineInfo() {

	}

	/**
	 * \brief Construct a new EngineInfo object.
	 * \param name The name of the EngineInfo object. This is used for storeage and for look ups when getting the object.
	 * \param type The type of data this object stores. \see Engine_Info_Types
	 */

	EngineInfo(const std::string &name, const int &type) {
		this->name = name;
		this->type = type;
	}

};

/** \class InfoEngine
 * \brief Stores all the EngineInfo objects. \see EngineInfo
 * 
 */

class InfoEngine
{
public:

	/**
	 * \brief 
	 * 
	 * \param info 
	 * \return true 
	 * \return false 
	 */

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

	/**
	 * \brief Get a given EngineInfo object
	 * 
	 * \param name The ID name of the EngineInfo object \see EngineInfo
	 * \return A pointer to the given EngineInfo object else nullptr.
	 */

	static EngineInfo* GetEngineInfo(const std::string &name) {
		auto iter = m_info.find(name);

		if (iter != m_info.end()) {
			return m_info[name];
		}
		//TODO error message
		return nullptr;
	}

	/**
	 * \brief Deletes the pointers stored in the std::map but leaves the entrys there.
	 * 
	 */

	static void CleanInfoEngine() {
		for (auto iter = m_info.begin(); iter != m_info.end(); iter++) {
			delete iter->second;
			iter->second = nullptr;
		}
	}

private:
	static std::map<std::string, EngineInfo*> m_info; //!< Stores the EngineInfo objects.
};