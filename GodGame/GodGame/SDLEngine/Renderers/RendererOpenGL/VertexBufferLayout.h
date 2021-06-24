#ifndef VERTEX_BUFFER_LAYOUT_H_INCLUDED
#define VERTEX_BUFFER_LAYOUT_H_INCLUDED

#include <vector>
#include <assert.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "../../typedefs.h"

struct VertexBufferLayoutElement {
	
	UInt32 Type; //!< What type this element is.
	UInt32 Count; //!< How many of this element is there.
	UInt32 Normalized; //!< Does this need to be normalized.
	
	UInt32 GetSizeOfType() const
    {
        switch (Type)
        {
            case GL_FLOAT		: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(UInt32);
			case GL_BOOL:		  return sizeof(bool);
			case GL_UNSIGNED_BYTE:return sizeof(unsigned char);
        }
        assert(false);
        return 0;
    }
};
//TODO add push for glm types.
class VertexBufferLayout {
	
public:

	VertexBufferLayout() {
		m_stride = 0;
	}

	template<typename T>
	void Push(const UInt32 &count) {
		assert(false);
	}

#if !defined(__linux__)
	template<>
	void Push<float>(const UInt32 &count) {
		m_elements.push_back({GL_FLOAT, count, 0});
		m_stride += count * sizeof(float);
	}

	template<>
	void Push<bool>(const UInt32 &count) {
		m_elements.push_back({ GL_BOOL, count, 0 });
		m_stride += count * sizeof(bool);
	}

	template<>
	void Push<unsigned char>(const UInt32 &count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, 0 });
		m_stride += count * sizeof(unsigned char);
	}

	template<>
	void Push<UInt32>(const UInt32 &count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, 0 });
		m_stride += count * sizeof(UInt32);
	}

	//Just treat the vec3/vec4 as floats.
	template<>
	void Push<glm::vec3>(const UInt32 &count) {
		m_elements.push_back({ GL_FLOAT, count  * 3, 0 });
		m_stride += count * sizeof(glm::vec3);
	}

	template<>
	void Push<glm::vec4>(const UInt32 &count) {
		m_elements.push_back({ GL_FLOAT, count * 4, 0 });
		m_stride += count * sizeof(glm::vec4);
	}

#endif //!__linux__

	inline const std::vector<VertexBufferLayoutElement> GetElements() const& { return m_elements; };
	inline UInt32 GetStride() const { return m_stride; };
	
private:
	std::vector<VertexBufferLayoutElement> m_elements;
	UInt32 m_stride;
};

#endif //VERTEX_BUFFER_LAYOUT_H_INCLUDED
