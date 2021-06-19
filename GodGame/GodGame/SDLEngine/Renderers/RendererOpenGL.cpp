#include "RendererOpenGL.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>

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

RendererOpenGL::RendererOpenGL() {
	
}

RendererOpenGL::~RendererOpenGL() {
	
}

bool RendererOpenGL::OnInit(SDL_Window * win, const UInt32 &flags) {
	p_SDLwin = win;
	p_GLContext = SDL_GL_CreateContext(win);
	
	if(p_GLContext == NULL) {
		std::cout << "Failed to create OpenGL context!\n";
		return false;
	}
	
	if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to Start Glew!\n";
        return false;
    }
	
	//TODO Add config to disable this
	//Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}
	
	std::cout << "Version: " + std::string((const char*)glGetString(GL_VERSION)) + "\n";
	std::cout << "Created SDL OpenGL Render Context!\n";
	
	//Load a test shader
	if(CompileShader(&programID, "data/Shaders/fragment.frag","data/Shaders/vertex.vert")) {
		
		//Set the clear colour
		glClearColor(0.0,0.0,0.0,1.0);
		//VBO data
		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 3 };

		//Create VBO
		glGenBuffers( 1, &gVBO );
		glBindBuffer( GL_ARRAY_BUFFER, gVBO );
		glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

		//Create IBO
		glGenBuffers( 1, &gIBO );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
	}	
	else {
		return false;
	}
	
	return true;
}

void RendererOpenGL::OnUpdate() {
	//Update screen
    SDL_GL_SwapWindow(p_SDLwin);
}

void RendererOpenGL::OnDraw() {

	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
	//Bind program
	glUseProgram( programID );

	//Enable vertex position
	glEnableVertexAttribArray( gVertexPos2DLocation );

	//Set vertex data
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

	//Set index data and render
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

	//Disable vertex position
	glDisableVertexAttribArray( gVertexPos2DLocation );

	//Unbind program
	glUseProgram(0);   
}

void RendererOpenGL::OnCleanUp() {
	
}

bool RendererOpenGL::CompileShader(UInt32 *id, const std::string &frag, const std::string &vert) {

	bool success = false;

	auto LoadSource = [](std::string path) {
		std::string source;
		std::string line;
		std::ifstream myfile(path.c_str());
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				source += line + "\n";
			}
			myfile.close();
		}
		else {
			std::cout << "Failed to open shader source: " << path << "\n";
		}
		return source;
	};

	//Create a new program.
	*id = glCreateProgram();
	//Check if we have created a program.
	if (!*id) {
		std::cout << "Failed to create openGL program\n";
		//TODO better error message.
	}
	else {
		std::cout << "Compiling vertex shader: " << vert << "\n";
		//Create vertex shader
		GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//Load the source code
		std::string vertFile = LoadSource(vert);
		const GLchar* vertexShaderSource[] =
		{
			vertFile.c_str()
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
			std::cout << "Vertex shader compiled: " << vert << "\n";
			//Attach vertex shader to program
			glAttachShader(*id, vertexShader);
			std::cout << "Compiling fragment shader: " << frag << "\n";

			//Create fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			std::string fragFile = LoadSource(frag);
			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				fragFile.c_str()
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
				std::cout << "Fragment shader compiled: " << frag << "\n";

				//Attach fragment shader to program
				glAttachShader(*id, fragmentShader);

				//Link program
				glLinkProgram(*id);

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(*id, GL_LINK_STATUS, &programSuccess);
				if (programSuccess != GL_TRUE)
				{
					//TODO Better error message.
					//printf( "Error linking program %d!\n", gProgramID );
					std::cout << "Error linking program:" << *id << "\n";
					//printProgramLog( gProgramID );
					//success = false;
				}
				else {
					//TODO this needs to be done another way.
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
					if (gVertexPos2DLocation == -1)
					{
						printf("LVertexPos2D is not a valid glsl program variable!\n");
						success = false;
					}
				}
			}

		}
	}
	//Double check if we have compiled the shader and set the id to 0 if we haven't.
	if (!success) {
		if (*id) {
			glDeleteProgram(*id); //Is this needed?
			*id = 0;
		}
	}
	else {
		std::cout << "Compiled Shader: " << *id << "\n";
	}
	return success;
}
