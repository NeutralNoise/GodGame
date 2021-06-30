#include "FrameBufferOpenGL.h"
#include <assert.h>
#include <iostream>
#include <gl/glew.h>

bool FrameBufferOpenGL::Create(const FrameBufferSpec & spec)
{
	FrameBuffer::m_spec = spec;
	//Create the frame buffer
	glCreateFramebuffers(1, &(FrameBuffer::m_fboID));
	//Bind the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

	//Create Frame buffer colour attachment.
	glGenTextures(1, &m_colourAttachment);
	glBindTexture(GL_TEXTURE_2D, m_colourAttachment);
	glTexImage2D(GL_TEXTURE_2D, spec.level, GL_RGBA8, spec.width, spec.height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Attach it to the frame buffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		m_colourAttachment, spec.level);

	//NOTE Do we need a depth buffer.

	//Sanity check

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		//TODO error message
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //Does this have to be here
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void * FrameBufferOpenGL::GetAttachment()
{
	return (void*)m_colourAttachment;
}

void FrameBufferOpenGL::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
}

void FrameBufferOpenGL::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferOpenGL::Delete()
{
	glDeleteFramebuffers(1, &m_colourAttachment);
}
