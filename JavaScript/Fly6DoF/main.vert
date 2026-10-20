#version 300 es

in vec3 position;
in vec4 color;
out vec4 vertexColor;

void main(void) {
  gl_Position = vec4(position, 1.);
  vertexColor = color;
}
