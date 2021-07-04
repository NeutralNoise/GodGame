/**
 * \file Shader.h
 * \author NeutralNoise
 * \brief 
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <string>
#include <unordered_map>
#include <GLM/glm.hpp>
#include "../../typedefs.h"

/**
 * \struct ShaderProgam
 * \brief Stores data about a shader program.
 * 
*/

struct ShaderProgam {
	UInt32 programID; //!< The OpenGL shader program ID.
	std::string fragmentFile; //!< File path to where the fragment shader is stored.
	std::string vertexFile; //!< File path to where the vertex shader is stored

	/**
	 * \brief Construct a new ShaderProgam object
	 * 
	*/

	ShaderProgam() {};

	/**
	 * \brief Construct a new ShaderProgam object
	 * 
	 * \param id The shader program ID.
	 * \param fragStr The file path to the fragment shader source.
	 * \param vertStr The file path to the vertex shader source.
	*/

	ShaderProgam(const UInt32 &id, const std::string &fragStr, const std::string &vertStr) {
		programID = id;
		fragmentFile = fragStr;
		vertexFile = vertStr;
	}
};

/**
 * \class Shader
 * \brief Describes a shader.
 * 
*/

class Shader {
	
public:

	/**
	 * \brief Construct a new Shader object
	 * 
	*/

	Shader() { };

	/**
	 * \brief Compile a new shader.
	 * 
	 * \param fragFile File path to a fragment shader source.
	 * \param vertFile File path to a vertex shader source.
	 * \return bool Returns true if source compiled otherwise false.
	*/

	bool CompileShader(const std::string &fragFile, const std::string &vertFile);
	
	/**
	 * \brief Bind the shader.
	 * 
	*/

	void Bind() const;

	/**
	 * \brief Unbind the shader.
	 * 
	*/

	void Unbind() const;

	/**
	 * \brief Set one unsigned int uniform.
	 * 
	 * \param name Name of the uniform.
	 * \param val The value to set the uniform to.
	*/

	void SetUniformu1ui(const std::string &name, const UInt32 &val);

	/**
	 * \brief Set one float uniform.
	 * 
	 * \param name Name of the uniform.
	 * \param val The value to set the uniform to.
	*/

	void SetUniformu1f(const std::string &name, const float &val);

	/**
	 * \brief Set two float uniforms (vec2).
	 * 
	 * \param name Name of the uniform.
	 * \param val1 The first value to set the uniform to.
	 * \param val2 The second value to set the uniform to.
	*/

	void SetUniformu2f(const std::string &name, const float &val1, const float &val2);

	/**
	 * \brief Set three float uniforms (vec3).
	 * 
	 * \param name Name of the uniform.
	 * \param val1 The first value to set the uniform to.
	 * \param val2 The second value to set the uniform to.
	 * \param val3 The third value to set the uniform to.
	*/

	void SetUniformu3f(const std::string &name, const float &val1, const float &val2, const float &val3);

	/**
	 * \brief Set four float uniforms (vec4).
	 * 
	 * \param name Name of the uniform.
	 * \param val1 The first value to set the uniform to.
	 * \param val2 The second value to set the uniform to.
	 * \param val3 The third value to set the uniform to.
	 * \param val4 The forth value to set the uniform to.
	*/

	void SetUniformu4f(const std::string &name, const float &val1, const float &val2, const float &val3, const float &val4);

	/**
	 * \brief Set a 4x4 matrix uniform.
	 * 
	 * \param name The name of the uniform.
	 * \param mat4 The value to set the uniform to.
	*/

	void SetUniformuMatrix4f(const std::string &name, const glm::mat4 &mat4);
	
private:

	/**
	 * \brief Get a uniform location.
	 * 
	 * \param name The name of the uniform to get.
	 * \return int Returns -1 if uniform was not found otherwise the location of the uniform.
	*/

	int GetUniform(const std::string &name);

	/**
	 * \brief Loads a shader source file into a string.
	 * 
	 * \param file File path to the source file to load.
	 * \return std::string Returns a string containing the shader source.
	*/

	std::string LoadSourceFile(const std::string &file);
	ShaderProgam m_program; //!< Shader program information. \see ShaderProgam
	std::unordered_map<std::string, Int32> m_uniformCache; //!< cache or uniform locations.
};

#endif //SHADER_H_INCLUDED
