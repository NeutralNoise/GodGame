#include "VertexBufferLayout.h"
//This is how gcc wants it done and so does the c++ standard.
//TODO Check to see if we are in clang or gcc.
#if defined(__linux__)
template<>
void VertexBufferLayout::Push<float>(const UInt32 &count) {
	m_elements.push_back({GL_FLOAT, count, 0});
	m_stride += count * sizeof(float);
}

template<>
void Push<glm::vec3>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count * 3, 0 });
	m_stride += count * sizeof(glm::vec3);
}

template<>
void Push<glm::vec4>(const UInt32 &count) {
	m_elements.push_back({ GL_FLOAT, count * 4, 0 });
	m_stride += count * sizeof(glm::vec4);
	}

#endif