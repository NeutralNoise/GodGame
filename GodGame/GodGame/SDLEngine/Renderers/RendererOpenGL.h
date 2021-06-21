#pragma once

#include "../Renderer.h"
#include "VertexBuffer.h"
#include "VertexAtribArray.h"
#include "IndexBuffer.h"

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

	bool OnInit(SDL_Window * win, const UInt32 &flags) override;

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
	
	bool CompileShader(UInt32 *id, const std::string &frag, const std::string &vert) override;

private:
	void * p_GLContext;
	UInt32 programID = 0;
	//TODO remove these
	Int32 gVertexPos2DLocation = -1;
	UInt32 gVBO = 0;
	UInt32 gIBO = 0;
	IndexBuffer m_IBO; // We only need one of these for now.
	VertexBuffer m_VBO; // We only need one of these for now.
	VertexArray m_VAA;
	
	int flash = 0;
};
