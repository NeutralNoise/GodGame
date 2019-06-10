#include "ErrorEngine.h"



ErrorEngine::ErrorEngine()
{
}


ErrorEngine::~ErrorEngine()
{
}

void ErrorEngine::RegCodeFunc(const unsigned int & code, ErrorMessageFunctions funcs)
{
	m_errorFunction[code] = funcs;
}

void ErrorEngine::AddErrorMessage(const unsigned int & code, const int & type)
{
	m_messages.push_back(EngineErrorMessage(code, type));
}

void ErrorEngine::AddErrorMessage(const unsigned int & code, const int & type, const std::string & msg)
{
	m_messages.push_back(EngineErrorMessage(code, type, msg));
}

EngineErrorMessage ErrorEngine::GetLastMessage()
{
	EngineErrorMessage pk = PeekLastMessage();
	if (pk.type != -1) {
		m_messages.pop_back();
		return pk;
	}
	return EngineErrorMessage();
}

EngineErrorMessage ErrorEngine::PeekLastMessage()
{

	if (m_messages.size() != 0) {
		EngineErrorMessage rtn = m_messages.back();
		return rtn;
	}

	return EngineErrorMessage();
}

std::string ErrorEngine::GetLastErrorMessageString()
{
	if (m_messages.size() != 0) {
		EngineErrorMessage err = m_messages.back();
		m_messages.pop_back();
		std::string rtn = CallErrrorCodeStrFunc(err);
		if (rtn.size() == 0) {
			rtn = err.msg;
		}
		return rtn;
	}

	return std::string();
}

std::string ErrorEngine::PeekLastErrorMessageString()
{

	if (m_messages.size() != 0) {
		EngineErrorMessage err = m_messages.back();
		std::string rtn = CallErrrorCodeStrFunc(err);
		if (rtn.size() == 0) {
			rtn = err.msg;
		}
		return rtn;
	}

	return std::string();
}

unsigned int ErrorEngine::GetLastErrorMessageCode()
{
	unsigned int pk = PeekLastErrorMessageCode();
	if (pk != -1) {
		m_messages.pop_back();
		return pk;
	}
	return -1;
}

unsigned int ErrorEngine::PeekLastErrorMessageCode()
{
	if (m_messages.size() != 0) {
		EngineErrorMessage err = m_messages.back();
		return err.code;
	}
	return -1;
}

void ErrorEngine::ClearLastError()
{
	if (m_messages.size() != 0) {
		m_messages.pop_back();
	}
}

void ErrorEngine::ClearAllErrors()
{
	m_messages.erase(m_messages.begin(), m_messages.end());
}

std::string ErrorEngine::CallErrrorCodeStrFunc(const EngineErrorMessage& err)
{
	//Find out if we have a function that needs to be called on this error code.
	auto iter = m_errorFunction.find(err.code);

	if (iter != m_errorFunction.end()) {
		if (iter->second.strFunc != nullptr) {
			return iter->second.strFunc(err);
		}
	}
	return std::string();
}

void * ErrorEngine::CallErrrorCodeDataFunc(const EngineErrorMessage & err)
{
	//Find out if we have a function that needs to be called on this error code.
	auto iter = m_errorFunction.find(err.code);

	if (iter != m_errorFunction.end()) {
		if (iter->second.dataFunc != nullptr) {
			return iter->second.dataFunc(err);
		}
	}
	return nullptr;
}

ErrorEngine * ErrorEngine::p_instance = nullptr;