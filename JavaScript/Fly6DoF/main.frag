#version 300 es

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

out vec4 fragColor;

void main(void) {
  fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
