#include "RendererOpenGL.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Vertex.h"
#include  "../EngineCamera.h"
#include "../GameEngine.h"

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
				
		m_VAA = VertexArray(1);
		m_VBO = VertexBuffer(nullptr, sizeof(Vertex) * MAX_BATCH_VERTICES);
		m_IBO = IndexBuffer(nullptr, sizeof(UInt32) * MAX_BATCH_INDICES);
		VertexBufferLayout layout;
	
		layout.Push<glm::vec3>(1);
		layout.Push<ColourRGBA>(1); //Vertex colour
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
	EngineCamera camera = *GameEngine::GetRenderer()->camera;
	//Bind program
	m_shader.Bind();
	m_shader.SetUniformu1f("u_time", time);
	//Translate the world around the camera.
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-camera.pos.x, -camera.pos.y, 0));
	m_shader.SetUniformuMatrix4f("u_mvp", camera.cameraMatrix * model);
	m_shader.SetUniformuMatrix4f("u_proj", camera.projection);
	//Enable vertex position
	m_VAA.Bind();
	
	GenerateBatchs();
	for (size_t i = 0; i <= m_batchIndex; i++) {
		//Set vertex data
		m_VBO.SetData(m_renderBatchs[i].data->data(), sizeof(Vertex)* m_renderBatchs[i].count);
		//Set index data
		m_IBO.SetData(m_renderBatchs[i].indices->data(), m_renderBatchs[i].count);
		//Render
		glDrawElements(GL_TRIANGLE_FAN, m_renderBatchs[i].count, GL_UNSIGNED_INT, NULL);
	}

	//Disable vertex position
	m_IBO.Unbind();
	m_VBO.Unbind();
	m_VAA.Unbind();
	//m_rBatch.Clear();
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

void RendererOpenGL::AddNewBatch()
{
	//Add a  new batch
	if (((m_renderBatchs.size() - 1) < m_batchIndex) || (m_renderBatchs.size() == 0) ) {
		RenderBatchOpenGL newBatch;
		m_renderBatchs.push_back(newBatch);
	}
}

void RendererOpenGL::GenerateBatchs()
{
	AddNewBatch();
	//Loop through the layers and add them to the batch
	for (size_t i = 0; i < Renderer::m_layers.size(); i++) {
		//Make sure this layer is valid.
		if (Renderer::m_layers[i] != nullptr) {
			//Get the render objects.
			RenderObjectLayer* layer = Renderer::m_layers[i];
			RenderObject* renObject;
			//TODO use sublayers
			for (size_t t = 0; t < layer->renderObjects.size(); t++) {
				renObject = layer->renderObjects[t];

				//Generate Vertexs
				//If this fails we need a new batch
				if (m_renderBatchs[m_batchIndex].AddQuard(*renObject) == -1) {
					//Check if we need a new batch or if we can use an old one.
					m_batchIndex++;
					AddNewBatch();
					m_renderBatchs[m_batchIndex].AddQuard(*renObject); //We should now have a clear batch.
				}
				
			}
		}
	}
	

}

void RendererOpenGL::ClearBatchs()
{
	for (size_t i = 0; i <= m_batchIndex; i++) {
		m_renderBatchs[i].Clear();
	}
	m_batchIndex = 0;
}
