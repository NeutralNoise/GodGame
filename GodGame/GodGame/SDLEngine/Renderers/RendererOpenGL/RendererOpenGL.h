#pragma once

#include <vector>
#include "../../Renderer.h"
#include "VertexBuffer.h"
#include "VertexAtribArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderBatchOpenGL.h"

class RendererOpenGL : public Renderer
{
	
	public:
	
	RendererOpenGL();
	
	~RendererOpenGL();
	
	/**
	 * \brief 
	 * 
	 * \param win The SDL2 window to render too.
	 * \param flags SDL2 renderer flags to set for the renderer.
	 * \return Returns true if renderer started.
	 * \warning flags will change in the future. 
	*/

	bool OnInit(SDL_Window * win, const UInt32 &flags, EngineRenderer * info) override;

	/**
	 * \brief Does nothing
	 * 
	*/

	void OnUpdate() override;

	/**
	 * \brief Should be called each frame and renders each layer and sublayer
	 * 
	*/

	void OnDraw() override;

	/**
	 * \brief Cleans up the renderer and should be called when the program is closed
	 * 
	*/

	void OnCleanUp() override;
	
	bool CompileShader(const std::string &frag, const std::string &vert) override;

private:

	struct OpenGLRenderStats {
		EngineInfo * p_vertexCount;
		EngineInfo * p_quardCount;
		EngineInfo * p_batchCount;
		EngineInfo * p_drawCalls;

		OpenGLRenderStats() {
			p_vertexCount = new EngineInfo("ren_vertex_count", EI_TYPE_UINT);
			p_quardCount = new EngineInfo("ren_quard_count", EI_TYPE_UINT);
			p_batchCount = new EngineInfo("ren_batch_count", EI_TYPE_UINT);
			p_drawCalls = new EngineInfo("ren_draw_calls", EI_TYPE_UINT);

			InfoEngine::AddEngineInfo(p_vertexCount);
			InfoEngine::AddEngineInfo(p_quardCount);
			InfoEngine::AddEngineInfo(p_batchCount);
			InfoEngine::AddEngineInfo(p_drawCalls);
		}

		void ClearData() {
			p_vertexCount->uidata = 0;
			p_quardCount->uidata = 0;
			p_batchCount->uidata = 0;
			p_drawCalls->uidata = 0;
		}

	};

	void AddNewBatch();

	void GenerateBatchs();
	void ClearBatchs();

	void * p_GLContext;
	//TODO remove these
	/*
	Int32 gVertexPos2DLocation = -1;
	UInt32 gVBO = 0;
	UInt32 gIBO = 0;
	*/
	IndexBuffer m_IBO; // We only need one of these for now.
	VertexBuffer m_VBO; // We only need one of these for now.
	VertexArray m_VAA;
	Shader m_shader; //The shader used by this renderer.
	std::vector<RenderBatchOpenGL> m_renderBatchs;
	UInt32 m_batchIndex = 0;
	int flash = 0;
	OpenGLRenderStats m_stats;
};
