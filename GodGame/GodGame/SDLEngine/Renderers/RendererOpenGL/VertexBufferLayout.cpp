#include "VertexBufferLayout.h"
//This is how gcc wants it done and so does the c++ standard.
//TODO Check to see if we are in clang or gcc.
#if defined(__linux__)
template<>
void VertexBufferLayout::Push<float>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count, 0 });
	m_stride += count * sizeof(float);
}

template<>
void VertexBufferLayout::Push<bool>(const UInt32 &count) {
	m_elements.push_back({ GL_BOOL, count, 0 });
	m_stride += count * sizeof(bool);
}

template<>
void VertexBufferLayout::Push<unsigned char>(const UInt32 &count) {
	m_elements.push_back({ GL_UNSIGNED_BYTE, count, 0 });
	m_stride += count * sizeof(unsigned char);
}

template<>
void VertexBufferLayout::Push<UInt32>(const UInt32 &count) {
	m_elements.push_back({ GL_UNSIGNED_INT, count, 0 });
	m_stride += count * sizeof(UInt32);
}

//Just treat the vec3/vec4 as floats.
template<>
void VertexBufferLayout::Push<glm::vec2>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count * 2, 0 });
	m_stride += count * sizeof(glm::vec2);
}

template<>
void VertexBufferLayout::Push<glm::vec3>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count * 3, 0 });
	m_stride += count * sizeof(glm::vec3);
}

template<>
void VertexBufferLayout::Push<glm::vec4>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count * 4, 0 });
	m_stride += count * sizeof(glm::vec4);
}

#endif