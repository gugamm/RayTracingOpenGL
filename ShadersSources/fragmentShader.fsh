#version 330 core

out vec4 color;

void main() {
  //gl_FragCoord = [0..w] or [0..h]
  //Red, green, blue, alpha
  color = vec4(0.0f,0.2f,0.4f,1.0f);
}
