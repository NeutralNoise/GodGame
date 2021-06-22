#include "Shader.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>

void printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
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
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
        
        //Allocate string
        char* infoLog = new char[ maxLength ];
        
        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
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
	m_program.programID = glCreateProgram();
	std::cout << "Compiling vertex shader: " << vertFile << "\n";
	//Create vertex shader
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	const GLchar* vertexShaderSource[] =
	{
		vertSource.c_str()
	};
	
	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
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
		glAttachShader(m_program.programID, vertexShader);
		std::cout << "Compiling fragment shader: " << fragFile << "\n";

		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//Get fragment source
		
		const GLchar* fragmentShaderSource[] =
		{
			fragSource.c_str()
		};
		
		//Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
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
			glAttachShader(m_program.programID, fragmentShader);

			//Link program
			glLinkProgram(m_program.programID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(m_program.programID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				//TODO Better error message.
				//printf( "Error linking program %d!\n", gProgramID );
				std::cout << "Error linking program:" << m_program.programID << "\n";
				printProgramLog( m_program.programID );
				//success = false;
			}
			else {

				//TODO this needs to be done another way.
				//Get vertex attribute location
				/*
				gVertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1)
				{
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				*/
			}
		}

	}

	//Double check if we have compiled the shader and set the id to 0 if we haven't.
	if (!success) {
		if (m_program.programID) {
			glDeleteProgram(m_program.programID); //Is this needed?
			m_program.programID = 0;
		}
	}
	else {
		std::cout << "Compiled Shader: " << m_program.programID << "\n";
	}


	return success;
}

void Shader::Bind() const {
	glUseProgram(m_program.programID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniformu1ui(const std::string & name, const UInt32 & val)
{
	glUniform1ui(GetUniform(name), val);
}

void Shader::SetUniformu1f(const std::string & name, const float & val)
{
	glUniform1f(GetUniform(name), val);
}

void Shader::SetUniformu2f(const std::string & name, const float & val1, const float & val2)
{
	glUniform2f(GetUniform(name), val1, val2);
}

void Shader::SetUniformu3f(const std::string & name, const float & val1, const float & val2, const float & val3)
{
	glUniform3f(GetUniform(name), val1, val2, val3);
}

void Shader::SetUniformu4f(const std::string & name, const float & val1, const float & val2, const float & val3, const float & val4)
{
	glUniform4f(GetUniform(name), val1, val2, val3, val4);
}

int Shader::GetUniform(const std::string & name)
{
	if (m_uniformCache.find(name) != m_uniformCache.end()) {
		return m_uniformCache[name];
	}
	//We haven't gotten it yet so we need to get the location.
	Int32 loc = glGetUniformLocation(m_program.programID, name.c_str());
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
