#include "VertexBuffer.h"
#include <GL/glew.h>
#include <iostream>

VertexBuffer::VertexBuffer() {}

VertexBuffer::VertexBuffer(const void *data, const UInt32 &size) {
	glGenBuffers( 1, &m_bufferID );
	glBindBuffer( GL_ARRAY_BUFFER, m_bufferID );
	glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
}

VertexBuffer::~VertexBuffer() {
}

void VertexBuffer::Bind() const {
	glBindBuffer( GL_ARRAY_BUFFER, m_bufferID );
}

void VertexBuffer::Unbind() const {
	glBindBuffer( GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}
