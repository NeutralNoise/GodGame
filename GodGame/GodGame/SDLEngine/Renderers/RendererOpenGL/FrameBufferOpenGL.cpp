#include "FrameBufferOpenGL.h"
#include <assert.h>
#include <iostream>
#include <gl/glew.h>
#include "ErrorOpenGL.h"

bool FrameBufferOpenGL::Create(const FrameBufferSpec & spec)
{
	FrameBuffer::m_spec = spec;
	//Create the frame buffer
	GLCall(glCreateFramebuffers(1, &(FrameBuffer::m_fboID)));
	//Bind the frame buffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

	//Create Frame buffer colour attachment.
	GLCall(glGenTextures(1, &m_colourAttachment));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_colourAttachment));
	GLCall(glTexImage2D(GL_TEXTURE_2D, spec.level, GL_RGBA8, spec.width, spec.height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//Attach it to the frame buffer.
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		m_colourAttachment, spec.level));

	//NOTE Do we need a depth buffer.

	//Sanity check

	GLASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	//assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		//TODO error message
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //Does this have to be here
		return false;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return true;
}

void * FrameBufferOpenGL::GetAttachment()
{
	return (void*)m_colourAttachment;
}

void FrameBufferOpenGL::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));
}

void FrameBufferOpenGL::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBufferOpenGL::Delete()
{
	GLCall(glDeleteFramebuffers(1, &m_colourAttachment));
}
