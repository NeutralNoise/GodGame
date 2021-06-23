//#version 130
#version 330

out vec4 LFragment;

in vec4 fColour;

uniform float u_time;

void main() {
	//LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
	LFragment = vec4(fColour.r * u_time, fColour.g * u_time, fColour.b * u_time, 1.0);
}
