#include "IndexBuffer.h"
#include <GL/glew.h>
#include <iostream>
#include "ErrorOpenGL.h"

IndexBuffer::IndexBuffer(){}

IndexBuffer::IndexBuffer(const UInt32* indices, const UInt32 &count)
  : m_Count(count)
{
	if (indices) {
		GLCall(glGenBuffers(1, &m_indexBufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, GL_STATIC_DRAW));
	}
	else {
		GLCall(glGenBuffers(1, &m_indexBufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, GL_DYNAMIC_DRAW));
	}
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const UInt32 * indices, const UInt32 & count)
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(UInt32), (const void*)indices));
}

void IndexBuffer::DeleteBuffer()
{
	GLCall(glDeleteBuffers(1, &m_indexBufferID));
}
