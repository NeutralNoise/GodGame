#include "Shader.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "ErrorOpenGL.h"

void printProgramLog(GLuint program)
{
	GLCall(bool madeShader = glIsProgram(program));
	//Make sure name is shader
	if (madeShader)
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		GLCall(glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog));
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void printShaderLog( GLuint shader )
{
    //Make sure name is shader
	GLCall(bool isShader = glIsShader(shader));
    if(isShader)
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
		GLCall(glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength ));
        
        //Allocate string
        char* infoLog = new char[ maxLength ];
        
        //Get info log
		GLCall(glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog ));
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}

bool Shader::CompileShader(const std::string &fragFile, const std::string &vertFile) {
	bool success = true;
	std::string vertSource = LoadSourceFile(vertFile);
	std::string fragSource = LoadSourceFile(fragFile);

	//Create Shader program.
	GLCall(m_program.programID = glCreateProgram());
	std::cout << "Compiling vertex shader: " << vertFile << "\n";
	//Create vertex shader
	GLCall(GLint vertexShader = glCreateShader(GL_VERTEX_SHADER));
	//Create fragment shader
	GLCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	const GLchar* vertexShaderSource[] =
	{
		vertSource.c_str()
	};
	
	//Set vertex source
	GLCall(glShaderSource(vertexShader, 1, vertexShaderSource, NULL));

	//Compile vertex source
	GLCall(glCompileShader(vertexShader));

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled));
	if (vShaderCompiled != GL_TRUE)
	{
		//TODO Better error message
		//printf( "Unable to compile vertex shader %d!\n", vertexShader );
		std::cout << "Unable to compile vertex shader " << vertexShader << "\n";
		printShaderLog(vertexShader);
		success = false;
	}
	else {
		std::cout << "Vertex shader compiled.\n";
		//Attach vertex shader to program
		GLCall(glAttachShader(m_program.programID, vertexShader));
		std::cout << "Compiling fragment shader: " << fragFile << "\n";

		//Get fragment source
		
		const GLchar* fragmentShaderSource[] =
		{
			fragSource.c_str()
		};
		
		//Set fragment source
		GLCall(glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL));

		//Compile fragment source
		GLCall(glCompileShader(fragmentShader));

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled));
		if (fShaderCompiled != GL_TRUE)
		{
			//TODO Better error message
			//printf( "Unable to compile fragment shader %d!\n", fragmentShader );
			std::cout << "Unable to compile fragment shader " << vertexShader << "\n";
			printShaderLog(fragmentShader);
			success = false;
		}
		else {
			std::cout << "Fragment shader compiled\n";

			//Attach fragment shader to program
			GLCall(glAttachShader(m_program.programID, fragmentShader));

			//Link program
			GLCall(glLinkProgram(m_program.programID));

			//Check for errors
			GLint programSuccess = GL_TRUE;
			GLCall(glGetProgramiv(m_program.programID, GL_LINK_STATUS, &programSuccess));
			if (programSuccess != GL_TRUE)
			{
				//TODO Better error message.
				//printf( "Error linking program %d!\n", gProgramID );
				std::cout << "Error linking program:" << m_program.programID << "\n";
				printProgramLog( m_program.programID );
				success = false;
			}
		}

	}

	//Double check if we have compiled the shader and set the id to 0 if we haven't.
	if (!success) {
		if (m_program.programID) {
			GLCall(glDeleteProgram(m_program.programID)); //Is this needed?
			m_program.programID = 0;
		}
	}
	else {
		std::cout << "Compiled Shader: " << m_program.programID << "\n";
	}
	//We dont really need these now.
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return success;
}

void Shader::Bind() const {
	GLCall(glUseProgram(m_program.programID));
}

void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void Shader::SetUniformu1ui(const std::string & name, const UInt32 & val)
{
	GLCall(glUniform1ui(GetUniform(name), val));
}

void Shader::SetUniformu1f(const std::string & name, const float & val)
{
	GLCall(glUniform1f(GetUniform(name), val));
}

void Shader::SetUniformu2f(const std::string & name, const float & val1, const float & val2)
{
	GLCall(glUniform2f(GetUniform(name), val1, val2));
}

void Shader::SetUniformu3f(const std::string & name, const float & val1, const float & val2, const float & val3)
{
	GLCall(glUniform3f(GetUniform(name), val1, val2, val3));
}

void Shader::SetUniformu4f(const std::string & name, const float & val1, const float & val2, const float & val3, const float & val4)
{
	GLCall(glUniform4f(GetUniform(name), val1, val2, val3, val4));
}
void Shader::SetUniformuMatrix4f(const std::string & name, const glm::mat4 &mat4)
{
	GLCall(glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, &mat4[0][0]));
}

int Shader::GetUniform(const std::string & name)
{
	if (m_uniformCache.find(name) != m_uniformCache.end()) {
		return m_uniformCache[name];
	}
	//We haven't gotten it yet so we need to get the location.
	GLCall(Int32 loc = glGetUniformLocation(m_program.programID, name.c_str()));
	if (loc == -1) {
		std::cout << "No active uniform variable with name " << name << " found\n";
	}
	m_uniformCache[name] = loc;

	return loc;
}

std::string Shader::LoadSourceFile(const std::string &file) {
	std::string source;
	std::string line;
	std::ifstream myfile(file.c_str());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			source += line + "\n";
		}
		myfile.close();
	}
	else {
		std::cout << "Failed to open shader source: " << file << "\n";
	}
	return source;
}
