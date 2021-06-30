#ifndef FRAMEBUFFER_H_INCLUDED
#define FRAMEBUFFER_H_INCLUDED
#include "typedefs.h"

struct FrameBufferSpec {
	UInt32 width;
	UInt32 height;
	Int32 level = 0;
	//What else is needed.
};

class FrameBuffer {
public:

	virtual bool Create(const FrameBufferSpec& spec) = 0;
	virtual void * GetAttachment() = 0;
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Delete() = 0;
protected:
	UInt32 m_fboID;
	FrameBufferSpec m_spec;
	bool specChanged;
};

#endif //FRAMEBUFFER_H_INCLUDED
