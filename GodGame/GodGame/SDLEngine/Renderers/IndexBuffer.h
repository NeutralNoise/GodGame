#ifndef INDEX_BUFFER_H_INCLUDED
#define INDEX_BUFFER_H_INCLUDED
#include "../typedefs.h"

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const UInt32 *indices, const UInt32 &count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const UInt32 * indices, const UInt32 &count);

	void DeleteBuffer();

	inline UInt32 GetCount() const { return m_Count; }

private:
	UInt32 m_indexBufferID;
	UInt32 m_Count;
};

#endif //INDEX_BUFFER_H_INCLUDED
