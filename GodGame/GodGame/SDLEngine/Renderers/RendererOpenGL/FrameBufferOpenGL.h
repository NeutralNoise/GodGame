#ifndef FRAMEBUFFER_OPENGL_H_INCLUDED
#define FRAMEBUFFER_OPENGL_H_INCLUDED

#include "../../FrameBuffer.h"

class FrameBufferOpenGL : public FrameBuffer {
public:
	bool Create(const FrameBufferSpec& spec) override;
	void * GetAttachment() override;

	void Bind() override;
	void Unbind() override;
	void Delete() override;

private:
	UInt32 m_colourAttachment;
};

#endif //FRAMEBUFFER_OPENGL_H_INCLUDED