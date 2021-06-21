#include "IndexBuffer.h"
#include <GL/glew.h>
#include <iostream>

IndexBuffer::IndexBuffer(){}

IndexBuffer::IndexBuffer(const UInt32* indices, const UInt32 &count)
  :
    m_Count(count)
{
    glGenBuffers(1, &m_indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    UInt32 testCount = count * sizeof(UInt32);
    std::cout << "test Count: " << testCount << "\n";
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(UInt32), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexBufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}