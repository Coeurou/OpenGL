#version 410 core

in vec3 fColor;
out vec4 outputColor;

uniform int windowHeight;
uniform float time;
uniform float lerpDuration;

void main() {
	float lerpFactor = sin( mod( time, 360.0 ) / 2.0 );
	float heightFactor = gl_FragCoord.y / windowHeight;
	vec4 firstColor = vec4( fColor, 1.0 ) * heightFactor;
	vec4 secondColor = vec4( 0.7, 0.53, 0.1, 1.0 );

	outputColor = mix( firstColor, secondColor, lerpFactor );
}