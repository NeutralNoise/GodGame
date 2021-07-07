/**
 * \file FrameBuffer.h
 * \author NeutralNoise
 * \brief Frame buffer template class.
 * \version 1.0
 * \date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef FRAMEBUFFER_H_INCLUDED
#define FRAMEBUFFER_H_INCLUDED
#include "typedefs.h"

/**
 * \struct Data structure used to describe a frame buffer.
 * \brief 
 * 
*/

struct FrameBufferSpec {
	UInt32 width; //!< The width of the frame buffer in pixels.
	UInt32 height; //!< The height of the frame buffer in pixels.
	Int32 level = 0; //!< Specifies the level-of-detail number.
	//What else is needed.
};

/**
 * \class FrameBuffer
 * \brief Frame buffer object inherited by renderer frame buffers.
 * 
*/

class FrameBuffer {
public:

	/**
	 * \brief Creates the new frame buffer.
	 * 
	 * \param spec \see FrameBufferSpec
	 * \return bool Returns true if frame buffer has need created false ofther wise.
	*/

	virtual bool Create(const FrameBufferSpec& spec) = 0;

	virtual bool Resize() = 0;

	/**
	 * \brief Gets the colour attachment object.
	 * 
	 * The colour attachment object is the texture used display the frame buffer.
	 * 
	 * \return void* The internal data structure of the colour attachment can be anything.
	*/

	virtual void * GetAttachment() = 0;

	/**
	 * \brief Binds the frame buffer to be renderer too.
	 * 
	*/

	virtual void Bind() = 0;

	/**
	 * \brief Unbinds the frame buffer so it is no longer rendered too.
	 * 
	*/

	virtual void Unbind() = 0;

	/**
	 * \brief Deletes the frame buffer from memory.
	 * 
	*/

	virtual void Delete() = 0;

	void SetFrameBufferSpec(const FrameBufferSpec& spec) { m_spec = spec; m_specChanged = true; }

protected:
	UInt32 m_fboID; //!< The id of the frame buffer.
	FrameBufferSpec m_spec; //!< The specification of the frame buffer.
	bool m_specChanged; //!< Has the FrameBufferSpec been changed.
};

#endif //FRAMEBUFFER_H_INCLUDED
