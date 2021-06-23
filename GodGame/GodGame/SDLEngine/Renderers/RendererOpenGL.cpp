#include "RendererOpenGL.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Vertex.h"

RendererOpenGL::RendererOpenGL() {
}

RendererOpenGL::~RendererOpenGL() {
	
}

bool RendererOpenGL::OnInit(SDL_Window * win, const UInt32 &flags) {
	std::cout << "Creating OpenGL Renderer\n";
	p_SDLwin = win;
	p_GLContext = SDL_GL_CreateContext(win);
	//TODO Better error handling.
	if(p_GLContext == NULL) {
		std::cout << "Failed to create OpenGL context!\n";
		return false;
	}
	else {
		std::cout << "SDL2 created OpenGL Contex\n";
		std::cout << "Version: " + std::string((const char*)glGetString(GL_VERSION)) + "\n";
	}
	
	if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to Start Glew!\n";
        return false;
    }
    else {
		std::cout << "Glew Has Started\n";
		std::cout << "Version: " << glewGetString(GLEW_VERSION) << "\n";
	}
	
	//TODO Add config to disable this
	//Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}
	
	//Set the clear colour
	glClearColor(0.0, 0.0, 0.0, 1.0);

	//Load a test shader
	if(CompileShader("data/Shaders/fragment.frag","data/Shaders/vertex.vert")) {
		
		//VBO data
		GLfloat vertexData[] =
		{
			-0.5f, -0.5f, 1.0, 0.0, 0.0,
			 0.5f, -0.5f, 0.0, 1.0, 0.0,
			 0.5f,  0.5f, 0.0, 0.0, 1.0,
			-0.5f,  0.5f, 1.0, 1.0, 1.0
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2, 3 };
		
		m_VAA = VertexArray(1);
		//m_VBO = VertexBuffer(vertexData, 6 * 4 * sizeof(float));
		//m_IBO = IndexBuffer(indexData, 4);
		m_VBO = VertexBuffer(nullptr, sizeof(Vertex) * MAX_BATCH_VERTICES);
		m_IBO = IndexBuffer(nullptr, sizeof(UInt32) * MAX_BATCH_INDICES);
		VertexBufferLayout layout;
	
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAA.AddBuffer(m_VBO, layout);		
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
	static float time = 0.0f;
	static float timeValue = 0.01f;
	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
	//Bind program
	m_shader.Bind();
	m_shader.SetUniformu1f("u_time", time);
	//Enable vertex position
	m_VAA.Bind();

	/*
	//Set vertex data
	m_VBO.Bind();
	//Set index data and render
	m_IBO.Bind();
	*/
	int err = glGetError();
	bool hasError = false;

	RenderObject ro(-0.5f, -0.5f, 1.0f, 1.0f);
	m_rBatch.AddQuard(ro);
	m_VBO.SetData(m_rBatch.data->data(), sizeof(Vertex)* m_rBatch.count);
	err = glGetError();

	m_IBO.SetData(m_rBatch.indices->data(), m_rBatch.count);
	err = glGetError();

	glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

	int fdsf = 34;

	//Disable vertex position
	m_IBO.Unbind();
	m_VBO.Unbind();
	m_VAA.Unbind();
	m_rBatch.Clear();
	time += timeValue;
	if (time > 1.0) {
		timeValue = -timeValue;
	}
	else if (time < 0.0) {
		timeValue = -timeValue;
	}
	//Unbind program
	glUseProgram(0);   
}

void RendererOpenGL::OnCleanUp() {
	
}

bool RendererOpenGL::CompileShader(const std::string &frag, const std::string &vert) {
	return m_shader.CompileShader(frag, vert);
}
