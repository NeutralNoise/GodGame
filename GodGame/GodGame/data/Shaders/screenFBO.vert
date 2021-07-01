#version 330

layout (location = 0) in vec3 vertPos2D;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 uv;
layout (location = 3) in uint translate;
layout (location = 4) in uint tIndex;

out vec4 v_fragColour;
out vec2 v_uv;
out uint v_texIndex;

uniform mat4 u_proj; //The view projection.

void main() {
  gl_Position = u_proj * vec4(vertPos2D.x, vertPos2D.y, 0,1);
  v_fragColour = colour;
  v_uv = uv;
  v_texIndex = tIndex;
}
