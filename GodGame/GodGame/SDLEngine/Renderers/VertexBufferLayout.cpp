#include "VertexBufferLayout.h"

template<>
void VertexBufferLayout::Push<float>(const UInt32 &count) {
	m_elements.push_back({GL_FLOAT, count, 0});
	m_stride += count * sizeof(float);
}
