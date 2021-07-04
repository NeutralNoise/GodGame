#include "RendererOpenGL.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../../../ImGUI/imgui.h"
#include "../../../ImGUI/imgui_impl_sdl.h"
#include "../../../ImGUI/imgui_impl_opengl3.h"
#include "Vertex.h"
#include "ImageLoaderOpenGL.h"
#include "TextureOpenGL.h"
#include  "../../EngineCamera.h"
#include "../../GameEngine.h"
#include "ErrorOpenGL.h"


RendererOpenGL::RendererOpenGL() {
}

RendererOpenGL::~RendererOpenGL() {
	
}

bool RendererOpenGL::OnInit(SDL_Window * win, const UInt32 &flags, EngineRenderer * info) {
	std::cout << "Creating OpenGL Renderer\n";
	//Fill out the EngineRenderer information;

	p_version = &(info->version);

	p_version->major = 0;
	p_version->minor = 1;
	p_version->patch = 0;

	Renderer::m_renName = "OpenGL";

	p_SDLwin = win;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
	Int32 texCount = 0;
	GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texCount));
	std::cout << "GL_MAX_TEXTURE_IMAGE_UNITS: " << texCount << "\n";
	//Set the clear colour
	GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
	//Set blends mode for textures
	GLCall(glEnable(GL_TEXTURE_2D));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	//Enable backface culling
	//TODO set config to turn this off or change to front face.
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	if (!m_fboShader.CompileShader("data/Shaders/screenFBO.frag", "data/Shaders/screenFBO.vert")) {
		//TODO error message this is fatel.
		return false;
	}

	//Load a test shader
	if(CompileShader("data/Shaders/fragment.frag","data/Shaders/vertex.vert")) {
				
		m_VAA = VertexArray(1);
		m_VBO = VertexBuffer(nullptr, sizeof(Vertex) * MAX_BATCH_VERTICES);
		m_IBO = IndexBuffer(nullptr, sizeof(UInt32) * MAX_BATCH_INDICES);
		VertexBufferLayout layout;
	
		layout.Push<glm::vec3>(1); //Vertex position.
		layout.Push<ColourRGBA>(1); //Vertex colour.
		layout.Push<glm::vec2>(1);	//Texture uv
		layout.Push<UInt32>(1); //Translate vertex.
		layout.Push<UInt32>(1); //Texture ID vertex.
		m_VAA.AddBuffer(m_VBO, layout);		
	}	
	else {
		//TODO error message this is fatel.
		return false;
	}
	
	//TODO move this.
	//Init ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//TODO ImGUI io.
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(win, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init("#version 130");

	ImageLoader::Init<ImageLoaderOpenGL>();

	FrameBufferSpec spec;
	spec.width = info->window_width;
	spec.height = info->window_height;
	if (!m_renObjFBO.Create(spec)) {
		//We need the FBO
		std::cout << "Failed to create frame buffer object\n";
		return false;
	}
	TextureOpenGL * texture = new TextureOpenGL;
	texture->SetTexure(m_renObjFBO.GetAttachment());
	ImageLoader::AddTexture("FrameBuffer", (Texture*)texture);
	//Set up the quard to render the frame buffers too.
	m_mainScreenQuard.x = 0.0;
	m_mainScreenQuard.y = 0.0;
	m_mainScreenQuard.width = WINDOW_WIDTH;
	m_mainScreenQuard.height = WINDOW_HEIGHT;
	m_mainScreenQuard.translateWithCamera = false;
	m_mainScreenQuard.texture = texture;
	//invert the V of the UV to flip the texture.
	RenderTile fboUV = RenderTile(0.0f,1.0f,1.0f,0.0f);
	m_mainScreenQuard.renderTile = fboUV;

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
	GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glEnable(GL_DEPTH_TEST));
	GenerateBatchs();
	if (m_needsRender) {
		EngineCamera camera = *GameEngine::GetRenderer()->camera;
		m_renObjFBO.Bind();
		GLCall(glClearColor(0.1, 0.1,0.1, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		//Bind program
		m_shader.Bind();
		m_shader.SetUniformu1f("u_time", time);
		//Translate the world around the camera.
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-camera.pos.x, -camera.pos.y, 0));
		m_shader.SetUniformuMatrix4f("u_mvp", camera.cameraMatrix * model);
		m_shader.SetUniformuMatrix4f("u_proj", camera.projection);
		//Enable vertex position
		m_VAA.Bind();
		
		m_stats.ClearData();
		m_stats.p_batchCount->uidata = m_renderBatchs.size();

		for (size_t i = 0; i < m_batchIndex + 1; i++) {
			//Set vertex data
			m_VBO.SetData(m_renderBatchs[i].data, sizeof(Vertex)* (m_renderBatchs[i].quardCount * 4));
			//Set index data
			m_IBO.SetData(m_renderBatchs[i].indices, m_renderBatchs[i].count);
			//Bind the Textures
			BindBatchTextures(m_renderBatchs[i]);
			//Render
			GLCall(glDrawElements(GL_TRIANGLES, m_renderBatchs[i].count, GL_UNSIGNED_INT, NULL));
			m_stats.p_drawCalls->uidata += 1;
			m_stats.p_vertexCount->uidata += m_renderBatchs[i].quardCount * 4;
			m_stats.p_quardCount->uidata += m_renderBatchs[i].quardCount;
			m_stats.p_renderBacthUsedMem->uidata += ((sizeof(Vertex) * 4) * m_renderBatchs[i].quardCount) + (m_renderBatchs[i].count * sizeof(UInt32));
			UnBindBatchTextures();
		}

		//Disable vertex position
		m_IBO.Unbind();
		m_VBO.Unbind();
		m_VAA.Unbind();
		ClearBatchs();
		m_renObjFBO.Unbind();
		time += timeValue;
		if (time > 1.0) {
			timeValue = -timeValue;
		}
		else if (time < 0.0) {
			timeValue = -timeValue;
		}
		//Unbind program
		m_shader.Unbind();
	}
	m_needsRender = false;
	ClearBatchs();
	Renderer::ClearRenderObjects();

	RenderScreenFrame();

}

void RendererOpenGL::OnCleanUp() {
	
}

bool RendererOpenGL::CompileShader(const std::string &frag, const std::string &vert) {
	//TODO improve this.
	return m_shader.CompileShader(frag, vert);
}

void RendererOpenGL::AddNewBatch()
{
	//Add a  new batch
	if (((m_renderBatchs.size() - 1) < m_batchIndex) || (m_renderBatchs.size() == 0) ) {
		RenderBatchOpenGL newBatch;
		m_renderBatchs.push_back(newBatch);
		m_stats.p_renderBacthMaxMem->uidata += (sizeof(Vertex) * MAX_BATCH_VERTICES) + (sizeof(UInt32) * MAX_BATCH_INDICES);
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
				if (!renObject) {
					break;
				}
				//Generate Vertexs
				//If this fails we need a new batch
				if (m_renderBatchs[m_batchIndex].AddQuad(*renObject) == -1) {
					//Check if we need a new batch or if we can use an old one.
					m_batchIndex++;
					AddNewBatch();
					m_renderBatchs[m_batchIndex].AddQuad(*renObject); //We should now have a clear batch.
					m_needsRender = true;
				}
				else if (!m_needsRender) {
					m_needsRender = true;
				}
			}
		}
	}
}

void RendererOpenGL::BindBatchTextures(const RenderBatchOpenGL & batch)
{
	//Loop though the batch textures and bind them.
	for (UInt32 i = 0; i < batch.m_textureMaxSlot + 1; i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + i));
		UInt32 texID = *(batch.p_textureBuffer + i);
		GLCall(glBindTexture(GL_TEXTURE_2D, texID));
	}
}

void RendererOpenGL::UnBindBatchTextures()
{
	GLCall(glBindTexture(GL_TEXTURE_2D,0));
}

void RendererOpenGL::ClearBatchs()
{
	//Check the size of the render batch to make sure we have something there.
	if (m_renderBatchs.size()) {
		for (size_t i = 0; i < m_batchIndex +1; i++) { //plus one just incase there is only 1 render batch.
			m_renderBatchs[i].Clear();
		}
	}
	m_batchIndex = 0;
}

void RendererOpenGL::RenderScreenFrame()
{

	//Render the frame buffer
	GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glDisable(GL_DEPTH_TEST));
	AddRenderObject(&m_mainScreenQuard);
	GenerateBatchs();
	m_fboShader.Bind();
	EngineCamera camera = *GameEngine::GetRenderer()->camera;
	m_fboShader.SetUniformuMatrix4f("u_proj", camera.projection);
	//Enable vertex position
	m_VAA.Bind();

	m_stats.p_batchCount->uidata += m_renderBatchs.size();

	for (size_t i = 0; i < m_batchIndex + 1; i++) {
		//Set vertex data
		m_VBO.SetData(m_renderBatchs[i].data, sizeof(Vertex)* (m_renderBatchs[i].quardCount * 4));
		//Set index data
		m_IBO.SetData(m_renderBatchs[i].indices, m_renderBatchs[i].count);
		BindBatchTextures(m_renderBatchs[i]);
		//Render
		GLCall(glDrawElements(GL_TRIANGLES, m_renderBatchs[i].count, GL_UNSIGNED_INT, NULL));
		m_stats.p_drawCalls->uidata += 1;
		m_stats.p_vertexCount->uidata += m_renderBatchs[i].quardCount * 4;
		m_stats.p_quardCount->uidata += m_renderBatchs[i].quardCount;
		m_stats.p_renderBacthUsedMem->uidata += ((sizeof(Vertex) * 4) * m_renderBatchs[i].quardCount) + (m_renderBatchs[i].count * sizeof(UInt32));
		UnBindBatchTextures();
	}
	m_fboShader.Unbind();
	ClearBatchs();
	Renderer::ClearRenderObjects();
}
