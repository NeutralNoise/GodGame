#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <string>
#include "../typedefs.h"

struct ShaderProgam {
	UInt32 programID;
	std::string fragmentFile; //!< File where the fragment shader is stored.
	std::string vertexFile; //!< File where the vertex shader is stored
	ShaderProgam() {};
	ShaderProgam(const UInt32 &id, const std::string &fragStr, const std::string &vertStr) {
		programID = id;
		fragmentFile = fragStr;
		vertexFile = vertStr;
	}
};

class Shader {
	
public:
	Shader() { };
	bool CompileShader(const std::string &fragFile, const std::string &vertFile);
	
	void Bind() const;
	void Unbind() const;
	
private:

	std::string LoadSourceFile(const std::string &file);
	ShaderProgam m_program;

};

#endif //SHADER_H_INCLUDED
