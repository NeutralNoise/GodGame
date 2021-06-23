//#version 130
#version 330

//in vec2 LVertexPos2D;
layout (location = 0) in vec3 LVertexPos2D;
layout (location = 1) in vec4 colour;

out vec4 fColour;

void main()
{
	gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
	fColour = colour;
}
