#version 410 core

in vec3 fColor;
out vec4 outputColor;

uniform int windowHeight;
uniform float time;

void main() {
	float heightFactor = gl_FragCoord.y / windowHeight;
	outputColor = vec4(fColor, 1.0) * heightFactor;
}