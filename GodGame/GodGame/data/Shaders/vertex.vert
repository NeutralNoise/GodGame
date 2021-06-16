#version 130

in vec2 LVertexPos2D;

out vec4 vertPos;

void main() 
{ 
	gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
	vertPos = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );
}
