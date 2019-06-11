#pragma once
#include <string>
#include <deque>
#include <map>
#include <functional>

/** \enum EngineErrorTypes
 * \brief What level of error the error message is.
 * 
*/

enum EngineErrorTypes
{
	ERR_TYPE_NONE, //!< There is no error message.
	ERR_TYPE_FATEL, //!< The engine has crashed.
	ERR_TYPE_WARNING, //!< The engine can keep going but this should be checked out.
	ERR_TYPE_LOW_WARN //!< The engine can keep going and nothing is really broken.
};

/** \struct EngineErrorMessage
 * \brief Data structure representing an error message.
 * 
*/

struct EngineErrorMessage
{
	unsigned int code; //!< The error code.
	int type = -1; //!< What type of error is this.  \see EngineErrorTypes
	std::string msg; //!< Whats the message this error gives.
	void * data = nullptr; //!< Some data that the engine put here. Can be used for anything really.

	/**
	 * \brief Construct a new EngineErrorMessage object
	 * 
	*/

	EngineErrorMessage() {

	}

	/**
	 * \brief Construct a new EngineErrorMessage object
	 * 
	 * \param code The code of this error.
	 * \param type What type of error this is. \ EngineErrorTypes
	 * \param msg What is the string message of this error.
	*/

	EngineErrorMessage(const unsigned int & code, const int & type, const std::string & msg) {
		this->code = code;
		this->type = type;
		this->msg = msg;
	}

	/**
	 * \brief Construct a new EngineErrorMessage object
	 * 
	 * \param code The code of this error.
	 * \param type What type of error this is. \ EngineErrorTypes
	*/


	EngineErrorMessage(const unsigned int & code, const int & type) {
		this->code = code;
		this->type = type;
	}
};

/** \class ErrorEngine
 * \brief Manages the error messages generated by the engine.
 * 
*/

/** \struct ErrorMessageFunctions
 * \brief Functions that can be called on a given error code.
 *
*/

struct ErrorMessageFunctions
{
	std::string (*strFunc)(const EngineErrorMessage&) = nullptr;
	void * (*dataFunc)(const EngineErrorMessage&) = nullptr;
	EngineErrorMessage (*onAdd)(const std::string&) = nullptr;
	/**
	 * \brief Construct a new ErrorMessageFunctions object
	 * 
	*/

	ErrorMessageFunctions() {

	}

	/**
	 * \brief Construct a new ErrorMessageFunctions object with a pointer to a string function.
	 * 
	 * \param strFunc The string function to call.
	*/

	ErrorMessageFunctions(std::string(*strFunc)(const EngineErrorMessage&)) {
		this->strFunc = strFunc;
	}

	/**
	 * \brief Construct a new ErrorMessageFunctions object with a pointer to a data function.
	 * 
	 * \param dataFunc The data function that will be called.
	*/

	ErrorMessageFunctions(void * (*dataFunc)(const EngineErrorMessage&)) {
		this->dataFunc = dataFunc;
	}

	ErrorMessageFunctions(EngineErrorMessage(*onAdd)(const std::string&)) {
		this->onAdd = onAdd;
	}

	/**
	 * \brief Construct a new ErrorMessageFunctions object with both a string function and a data function.
	 * 
	 * \param strFunc The string function to call.
	 * \param dataFunc The data function to call.
	 * \param onAdd A function called when the given error code is added.
	*/

	ErrorMessageFunctions(std::string(*strFunc)(const EngineErrorMessage&), void * (*dataFunc)(const EngineErrorMessage&), EngineErrorMessage(*onAdd)(const std::string&)) {
		this->strFunc = strFunc;
		this->dataFunc = dataFunc;
		this->onAdd = onAdd;
	}

};

class ErrorEngine
{
public:

	/**
	 * \brief Construct a new ErrorEngine object
	 * 
	*/

	ErrorEngine();

	/**
	 * \brief Destroy the ErrorEngine object
	 * 
	*/

	~ErrorEngine();

	/**
	 * \brief Create a new instance of the error engine.
	 * * \warn This should only be called once and it should be called before the ErrorEngine is used.
	 * 
	*/

	static void InitErrorEngine();

	/**
	 * \brief Sets the functions for a given error code.
	 * 
	 * \param code The error code to set the functions of.
	 * \param funcs The functions to set. \see ErrorMessageFunctions
	*/

	void RegCodeFunc(const unsigned int &code, ErrorMessageFunctions funcs);

	/**
	 * \brief Sets the string functions for a given error code.
	 * \warn This will override anything that is already there.
	 * \param code The error code the function belongs too.
	 * \param strFunc The function to add.
	*/

	void RegCodeFunc(const unsigned int &code, std::string (*strFunc)(const EngineErrorMessage&));

	/**
	 * \brief 
	 * 
	 * \param code 
	 * \param dataFunc 
	*/

	void RegCodeFunc(const unsigned int &code, void *(*dataFunc)(const EngineErrorMessage&));

	/**
	 * \brief Add a new error message.
	 * 
	 * \param code The code of the error.
	 * \param type The type of error message. \see ErrorMessageTypes
	*/

	void AddErrorMessage(const unsigned int &code, const int &type);

	void AddErrorMessage(const unsigned int &code, const std::string &msg);

	/**
	 * \brief Add a new error message.
	 * 
	 * \param code The code of the error.
	 * \param type The type of error message. \see ErrorMessageTypes
	 * \param msg The string message of this error.
	*/

	void AddErrorMessage(const unsigned int &code, const int &type, const std::string &msg);

	/**
	 * \brief Gets the last error message added.
	 * 	This gets the last error message added then removes it.
	 * \return A copy of the last EngineErrorMessage added. The error message type will be set to -1 if there are no messages.
	 * \see EngineErrorMessage 
	*/

	EngineErrorMessage GetLastMessage();

	/**
	 * \brief Gets the last error message added.
	 * 	This gets a the last error message added. But does not remove it.
	 * \return A copy of the last EngineErrorMessage added. The error message type will be set to -1 if there are no messages.
	 * \see EngineErrorMessage 
	*/

	EngineErrorMessage PeekLastMessage();

	/**
	 * \brief Get the last ErrorMessage string. \see ErrorMessage
	 * 
	 * This gets the last error messages string and calls the strFunc of the error code if there is one.
	 *  It then removes the error.
	 * 
	 * \return std::string 
	 * \see ErrorMessageFunctions
	*/

	std::string GetLastErrorMessageString();

	/**
	 * \brief Get the last ErrorMessage string. \see ErrorMessage
	 * This gets the last error messages string and calls the strFunc of the error code if there is one.
	 * But it doesn't remove the error message.
	 * \return std::string 
	*/

	std::string PeekLastErrorMessageString();

	/**
	 * \brief Gets the last ErrorMessage code.
	 * \warn This will remove the error message.
	 * \return The ErrorMessage code. \see ErrorMessage
	*/

	unsigned int GetLastErrorMessageCode();

	/**
	 * \brief Gets the last ErrorMessage code.
	 * \warn This will NOT remove the error message.
	 * \return The ErrorMessage code. \see ErrorMessage
	*/

	unsigned int PeekLastErrorMessageCode();

	/**
	 * \brief Clears the last error message.
	 * 
	*/

	void ClearLastError();

	/**
	 * \brief Clears all error messages.
	 * 
	*/

	void ClearAllErrors();

	/**
	 * \brief Calls the strFunc on a given ErrorMessage.
	 * 
	 * \param err The error message to call the strFunc on.
	 * \return The string generated by the strFunc or the msg in the ErrorMessage. If on message string length is 0.
	 * \see ErrorMessage
	 * \see ErrorMessageFunctions
	*/

	std::string CallErrrorCodeStrFunc(const EngineErrorMessage& err);

	/**
	 * \brief Calls the dataFunc on a given ErrorMessage.
	 * 
	 * \param err The error message to call the strFunc on.
	 * \return What error dataFunc returns. If no function it returns nulptr.
	 * \see ErrorMessage
	 * \see ErrorMessageFunctions
	*/

	void *CallErrrorCodeDataFunc(const EngineErrorMessage& err);

	/**
	 * \brief Get the p_instance object
	 * 
	 * \return Pointer to an instance of this class.
	*/

	static ErrorEngine * GetInstance() { return p_instance; }

	/**
	 * \brief Called when a fatel error has happened.
	 * 
	*/

	void OnFatel();

private:
	std::map<unsigned int, ErrorMessageFunctions> m_errorFunction; //!< Functions that are ran on a given error code. Mainly used for generating the error message.
	std::deque<EngineErrorMessage> m_messages; //!< Storeage for errors that have been generated.
	static ErrorEngine * p_instance; //!< Instance of this class to handle system wid errors.
	bool m_hasFatel = false;
};

/**
 * \brief Helper to get the last error message added.
 * This gets the last error message added then removes it.
 * \return A copy of the last EngineErrorMessage added. The error message type will be set to -1 if there are no messages.
 * \see EngineErrorMessage 
*/

inline EngineErrorMessage GetLastEngineError() {
	return ErrorEngine::GetInstance()->GetLastMessage();
}

/**
 * \brief A helper to add a new error message.
 * 
 * \param code The code of the error.
 * \param type The type of error message. \see ErrorMessageTypes
 * \param msg The string message of this error.
*/

inline void AddEngineErrorMessage(const unsigned int &code, const int &type, const std::string &msg) {
	ErrorEngine::GetInstance()->AddErrorMessage(code, type, msg);
}

extern void DisplayErrors();