//#version 130
#version 330

//in vec2 LVertexPos2D;
layout (location = 0) in vec3 LVertexPos2D;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 uv;
layout (location = 3) in uint translate;

out vec4 fColour;
out vec2 v_uv;
uniform mat4 u_mvp;
uniform mat4 u_proj;
void main()
{
	if(translate) {
		gl_Position = u_mvp * vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
	}
	else {
		gl_Position = u_proj * vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
	}
	fColour = colour;
	v_uv  = uv;
}
