/**
 * \file RendererOpenGL.h
 * \author NeutralNoise
 * \brief Renders OpenGL
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#pragma once

#include <vector>
#include "../../Renderer.h"
#include "VertexBuffer.h"
#include "VertexAtribArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderBatchOpenGL.h"
#include "FrameBufferOpenGL.h"

class RendererOpenGL : public Renderer
{
	
	public:
	
	RendererOpenGL();
	
	~RendererOpenGL();
	
	/**
	 * \brief Creates an OpenGL contex and sets up the renderer.
	 * 
	 * \param win The SDL2 window to render too.
	 * \param flags SDL2 renderer flags to set for the renderer.
	 * \return Returns true if renderer started otherwise false.
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
	
	/**
	 * \brief Compiles an OpenGL shader.
	 * 
	 * \param frag File path to a fragment shader.
	 * \param vert File path to a vertex shader.
	 * \return bool Returns true if shader compiled otherwise false.
	*/

	bool CompileShader(const std::string &frag, const std::string &vert) override;

	FrameBufferOpenGL m_renObjFBO; //!< The frame buffer used to render the RenderObjects too. /warning this will be moved.

private:

	/**
	 *  \struct OpenGLRenderStats
	 *  \brief Stores render statistics.
	 * 
	*/

	struct OpenGLRenderStats {
		EngineInfo * p_vertexCount; //!< The number of vertexs rendered.
		EngineInfo * p_quardCount; //!< The number of quads rendered.
		EngineInfo * p_batchCount; //!< The number of render batchs.
		EngineInfo * p_drawCalls; //!< The number of draw calls.
		EngineInfo * p_renderBacthMaxMem; //!< The max memory allocated for render batchs.
		EngineInfo * p_renderBacthUsedMem; //!< The current amount of allocated render bacth memory used.

		/**
		 * \brief Construct a new OpenGLRenderStats object
		 * 
		*/

		OpenGLRenderStats() {
			p_vertexCount = new EngineInfo("ren_vertex_count", EI_TYPE_UINT);
			p_quardCount = new EngineInfo("ren_quard_count", EI_TYPE_UINT);
			p_batchCount = new EngineInfo("ren_batch_count", EI_TYPE_UINT);
			p_drawCalls = new EngineInfo("ren_draw_calls", EI_TYPE_UINT);
			p_renderBacthMaxMem = new EngineInfo("ren_max_batch_mem", EI_TYPE_UINT);
			p_renderBacthUsedMem = new EngineInfo("ren_used_batch_mem", EI_TYPE_UINT);

			InfoEngine::AddEngineInfo(p_vertexCount);
			InfoEngine::AddEngineInfo(p_quardCount);
			InfoEngine::AddEngineInfo(p_batchCount);
			InfoEngine::AddEngineInfo(p_drawCalls);
			InfoEngine::AddEngineInfo(p_renderBacthMaxMem);
			InfoEngine::AddEngineInfo(p_renderBacthUsedMem);
		}

		/**
		 * \brief Resets the statistics back to zero.
		 * 
		*/

		void ClearData() {
			p_vertexCount->uidata = 0;
			p_quardCount->uidata = 0;
			p_batchCount->uidata = 0;
			p_drawCalls->uidata = 0;
			p_renderBacthUsedMem->uidata = 0;
		}

	};

	/**
	 * \brief Add a new render batch.
	 * 
	*/

	void AddNewBatch();

	/**
	 * \brief Generates the render bachs.
	 * 
	*/

	void GenerateBatchs();

	/**
	 * \brief Bind a render batchs textures.
	 * 
	 * \param batch The batch to have its textures bound.
	 * \see RenderBatchOpenGL
	*/

	void BindBatchTextures(const RenderBatchOpenGL & batch);

	/**
	 * \brief Unbind the textures.
	 * 
	*/

	void UnBindBatchTextures();

	/**
	 * \brief Clear the render batchs.
	 * 
	*/

	void ClearBatchs();

	/**
	 * \brief Render m_renObjFBO to the screen.
	 * 
	*/

	void RenderScreenFrame();

	void * p_GLContext; //!< Our OpenGL rendering context ID.
	IndexBuffer m_IBO; // We only need one of these for now.
	VertexBuffer m_VBO; // We only need one of these for now.
	VertexArray m_VAA;
	Shader m_shader; //The shader used by this renderer.
	Shader m_fboShader;
	std::vector<RenderBatchOpenGL> m_renderBatchs; //!< Render batchs that are used to render to the screen.
	RenderObject m_mainScreenQuard; //!< A render object used to display the screen FBO.
	UInt32 m_batchIndex = 0; //!< Where we are currently looking in the RenderBatchs.
	bool m_needsRender = false; //!< Has anything been added to the RenderBatch.
	int flash = 0; //!< What
	OpenGLRenderStats m_stats; //!< Render statistics.
};
