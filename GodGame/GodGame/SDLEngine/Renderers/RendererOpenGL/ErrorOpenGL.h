#ifndef OPENGL_ERROR_H_INCLUDED
#define OPENGL_ERROR_H_INCLUDED

#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <gl/glew.h>

//#define NO_GL_ERROR_CHECK

#define GLASSERT(x) if (!(x)) assert(false)

#ifdef NO_GL_ERROR_CHECK
#define GLCall(x) x;
#else 
#define GLCall(x) \
	GLClearError();\
    x;\
    GLASSERT(GLCheckError(#x))
#endif


inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLCheckError(const char * func)
{
	while (GLenum error = glGetError())
	{
		printf("%s\n", func);
		std::cout << "[OpenGL Error] ";
		switch (error) {
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument.";
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_OPERATION : A numeric argument is out of range.";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION : The specified operation is not allowed in the current state.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION : The framebuffer object is not complete.";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY : There is not enough memory left to execute the command.";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW : An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW : An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		default:
			std::cout << "Unrecognized error" << error;
		}
		std::cout << "\n";
		return false;
	}
	return true;
}

#endif //OPENGL_ERROR_H_INCLUDED