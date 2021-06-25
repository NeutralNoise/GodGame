//#version 130
#version 330

out vec4 LFragment;

in vec4 fColour;
in vec2 v_uv;
//uniform float u_time;
uniform sampler2D u_Texture;

void main() {
	//LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
	//LFragment = vec4(fColour.r * u_time, fColour.g, fColour.b, 1.0);
	LFragment = texture(u_Texture,v_uv);
}
