#include "IndexBuffer.h"
#include <GL/glew.h>
#include <iostream>

IndexBuffer::IndexBuffer(){}

IndexBuffer::IndexBuffer(const UInt32* indices, const UInt32 &count)
  : m_Count(count)
{
	if (indices) {
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, GL_STATIC_DRAW);
	}
	else {
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, GL_DYNAMIC_DRAW);
	}
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const UInt32 * indices, const UInt32 & count)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(UInt32), (const void*)indices);
}

void IndexBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_indexBufferID);
}
