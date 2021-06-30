//#version 130
#version 330

out vec4 texColor;

in vec4 fColour;
in vec2 v_uv;
in flat uint TexIndex;
//uniform float u_time;
uniform sampler2D u_Textures[32];

vec4 colour;

void main() {

	float tileFactor = 1.0f;
	/*
	vec4 tmpColour = fColour;
	tmpColour *= texture(u_Textures[TexIndex],v_uv);
	texColor = tmpColour;
	*/
	texColor = texture(u_Textures[TexIndex],v_uv * tileFactor);

	//Test gamma stuff.
	/*
	float gamma = 2.2;
	colour = texture(u_Texture,v_uv);
	LFragment.xyz = pow(colour.xyz, vec3(1.0/gamma));
	LFragment.w = colour.w;
	*/
}
