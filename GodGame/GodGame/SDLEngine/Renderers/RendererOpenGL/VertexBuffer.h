#ifndef VERTEX_BUFFER_H_INCLUDED
#define VERTEX_BUFFER_H_INCLUDED
#include "../../typedefs.h"

class VertexBuffer
{
    public:
		VertexBuffer(); // This does nothing 
        VertexBuffer(const void *data, const UInt32 &size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

		void SetData(const void *data, const UInt32 &size);

		void DeleteBuffer();

    private:
        UInt32 m_bufferID;
};



#endif //VERTEX_BUFFER_H_INCLUDED
