#version 410 core

uniform vec2 windowSize;
out vec4 outputColor;

void main() {
	float heightFactor = gl_FragCoord.y / windowSize.y;
	outputColor = mix(vec4(1.0, 1.0, 1.0, 1.0), vec4(0.2, 0.2, 0.2, 0.2), heightFactor);
}