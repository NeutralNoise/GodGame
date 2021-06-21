#ifndef VERTEX_ATRIB_ARRAY_H_INCLUDED
#define VERTEX_ATRIB_ARRAY_H_INCLUDED

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "../typedefs.h"

class VertexArray
{
public:
	VertexArray() {};
	VertexArray(const Int32 &count);
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
private:
	UInt32 m_atribArrayID;
};

#endif //VERTEX_ATRIB_ARRAY_H_INCLUDED
