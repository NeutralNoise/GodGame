#include "VertexBufferLayout.h"
//This is how gcc wants it done and so does the c++ standard.
#if defined(__linux__)
template<>
void VertexBufferLayout::Push<float>(const UInt32 &count) {
	m_elements.push_back({GL_FLOAT, count, 0});
	m_stride += count * sizeof(float);
}
#endif