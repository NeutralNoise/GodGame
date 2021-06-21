#ifndef VERTEX_BUFFER_LAYOUT_H_INCLUDED
#define VERTEX_BUFFER_LAYOUT_H_INCLUDED

#include <vector>
#include <assert.h>
#include <GL/glew.h>
#include "../typedefs.h"

struct VertexBufferLayoutElement {
	
	UInt32 Type; //!< What type this element is.
	UInt32 Count; //!< How many of this element is there.
	UInt32 Normalized; //!< Does this need to be normalized.
	
	UInt32 GetSizeOfType() const
    {
        switch (Type)
        {
            case GL_FLOAT         : return sizeof(float);
            case GL_UNSIGNED_INT  : return sizeof(UInt32);
            //case GL_UNSIGNED_BYTE : return sizeof(unsigned char);
        }
        assert(false);
        return 0;
    }
};

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
#endif //__linux__
	/*
	template<>
	void Push<UInt32>(const UInt32 &count) {
		m_elements.push_back({GL_UNSIGNED_INT, count, 0});
		m_stride += count * sizeof(UInt32);
	}
	*/
	inline const std::vector<VertexBufferLayoutElement> GetElements() const& { return m_elements; };
	inline UInt32 GetStride() const { return m_stride; };
	
private:
	std::vector<VertexBufferLayoutElement> m_elements;
	UInt32 m_stride;
};

#endif //VERTEX_BUFFER_LAYOUT_H_INCLUDED
