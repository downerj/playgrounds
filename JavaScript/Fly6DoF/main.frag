#version 300 es

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

in vec4 vertexColor;
out vec4 fragColor;

void main(void) {
  fragColor = vertexColor;
}
