#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fColor;

uniform vec2 offset;

void main() {
	gl_Position = vec4( position.x + offset.x, position.y + offset.y, position.z, 1.0 );
	fColor = color;
}
