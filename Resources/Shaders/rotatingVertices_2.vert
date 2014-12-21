#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fColor;

uniform float time;
uniform float duration;

#define PI 3.14159265358979323

void main() {
	float angle = 2.0 * PI / duration;
	float currentFrame = mod( time, duration );
	vec2 offset;
	offset.x = cos( currentFrame * angle ) * 0.5;
	offset.y = sin( currentFrame * angle ) * 0.5;
	
	gl_Position = vec4( position.x + offset.x, position.y + offset.y, position.z, 1.0 );
	fColor = color;
}
