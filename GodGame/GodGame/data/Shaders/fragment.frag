#version 130

out vec4 LFragment;

in vec4 vertPos;

void main() {
	//LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );
	LFragment = vec4((1.0 * vertPos.x), (1.0 * vertPos.y), 1.0 * sqrt(pow(gl_FragCoord.x - vertPos.x, 2) + pow(gl_FragCoord.y - vertPos.y,2)) ,1.0);
}
