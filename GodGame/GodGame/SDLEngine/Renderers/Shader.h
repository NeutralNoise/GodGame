#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <string>
#include "../typedefs.h"
#include <unordered_map>

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
	void SetUniformu1ui(const std::string &name, const UInt32 &val);
	void SetUniformu1f(const std::string &name, const float &val);
	void SetUniformu2f(const std::string &name, const float &val1, const float &val2);
	void SetUniformu3f(const std::string &name, const float &val1, const float &val2, const float &val3);
	void SetUniformu4f(const std::string &name, const float &val1, const float &val2, const float &val3, const float &val4);
	
private:
	int GetUniform(const std::string &name);
	std::string LoadSourceFile(const std::string &file);
	ShaderProgam m_program;
	std::unordered_map<std::string, Int32> m_uniformCache;
};

#endif //SHADER_H_INCLUDED
