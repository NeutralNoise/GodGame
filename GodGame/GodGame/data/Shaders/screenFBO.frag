#version 330

out vec4 screenColour;

in vec4 v_fragColour;
in vec2 v_uv;

uniform sampler2D u_Textures[32];

in flat uint v_texIndex;

void main() {
  screenColour = texture(u_Textures[v_texIndex], v_uv);
}
