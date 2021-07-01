#include "VertexBuffer.h"
#include <GL/glew.h>
#include <iostream>
#include "ErrorOpenGL.h"

VertexBuffer::VertexBuffer() {}

VertexBuffer::VertexBuffer(const void *data, const UInt32 &size) {
	if (data) {
		GLCall(glGenBuffers(1, &m_bufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}
	else {
		GLCall(glGenBuffers(1, &m_bufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	}
}

VertexBuffer::~VertexBuffer() {
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer( GL_ARRAY_BUFFER, m_bufferID ));
}

void VertexBuffer::Unbind() const {
	GLCall(glBindBuffer( GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetData(const void * data, const UInt32 & size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}

void VertexBuffer::DeleteBuffer()
{
	GLCall(glDeleteBuffers(1, &m_bufferID));
}
