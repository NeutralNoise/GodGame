#include "Shader.h"
#include <iostream>
#include <fstream>

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
	
}

void Shader::Bind() const {
	
}

void Shader::Unbind() const {
	
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
