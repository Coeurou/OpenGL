#version 410 core

layout (position = 0) in vec3 position;

void main() {
	gl_Position = vec4(position, 1.0);
}

