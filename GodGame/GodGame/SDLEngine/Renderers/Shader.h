#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <string>
#include "../typedefs.h>
struct Shader {
	UInt32 programID;
	std::string fragmentFile; //!< File where the fragment shader is stored.
	std::string vertexFile; //!< File where the vertex shader is stored
	
	Shader(const Uint32 &id, const std::string &fragStr, const std::string &vertStr) {
		programID = id;
		fragmentFile = fragStr;
		vertexFile = vertStr;
	}
	
};

#endif //SHADER_H_INCLUDED
