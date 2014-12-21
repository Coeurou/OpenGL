#version 410 core

in vec3 fColor;
out vec4 outputColor;

void main() {
	outputColor = vec4(fColor, 1.0);
}