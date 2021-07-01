#include "VertexAtribArray.h"
#include <GL/glew.h>
#include <iostream>
#include "ErrorOpenGL.h"

VertexArray::VertexArray(const Int32 &count) {
	GLCall(glGenVertexArrays(count, &m_atribArrayID));
}

VertexArray::~VertexArray() {
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const std::vector<VertexBufferLayoutElement>& elements = layout.GetElements();
	UInt32 offset = 0;
	for(UInt32 i = 0; i < elements.size(); i++) {
		const VertexBufferLayoutElement& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.Count, element.Type, element.Normalized,
									  layout.GetStride(), (const void*)offset));
		offset += element.Count * element.GetSizeOfType();
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_atribArrayID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::DeleteArray()
{
	GLCall(glDeleteVertexArrays(1, &m_atribArrayID));
}
