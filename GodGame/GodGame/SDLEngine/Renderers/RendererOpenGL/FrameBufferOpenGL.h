/**
 * \file FrameBufferOpenGL.h
 * \author NeutralNoise
 * \brief Defines an OpenGL frame buffer.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef FRAMEBUFFER_OPENGL_H_INCLUDED
#define FRAMEBUFFER_OPENGL_H_INCLUDED

#include "../../FrameBuffer.h"

/**
 * \class FrameBufferOpenGL
 * \brief A frame buffer object used too render to with OpenGL
 * 
*/

class FrameBufferOpenGL : public FrameBuffer {
public:

	/**
	 * \brief Creates a new OpenGL frame buffer object.
	 * 
	 * \param spec The Frame buffer spec to set the frame buffer too. \see FrameBufferSpec
	 * \return bool Returns true  if frame buffer was created.
	*/

	bool Create(const FrameBufferSpec& spec) override;

	bool  Resize() override;


	/**
	 * \brief Get the coolour attachment object
	 * 
	 * This is a OpenGL 2D texture ID stored as an unsigned int internally.
	 * 
	 * \return void* Casted void* to the OpenGL 2D texture ID.
	*/

	void * GetAttachment() override;

	/**
	 * \brief Bind the frame buffer to be rendered too.
	 * 
	*/

	void Bind() override;

	/**
	 * \brief Unbined the frame buffer from being rendered too.
	 * 
	*/

	void Unbind() override;

	/**
	 * \brief Delete the frame buffer from memory.
	 * 
	*/

	void Delete() override;

private:
	UInt32 m_colourAttachment; //!< OpenGL 2D texture ID.
};

#endif //FRAMEBUFFER_OPENGL_H_INCLUDED