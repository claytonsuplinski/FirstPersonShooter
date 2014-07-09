/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

in vec3 Position;
in vec3 Normal;
const vec4 LightPosition = vec4(0.0, 0.0, 10.0, 0.0);
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Kd = vec3(0.6, 0.6, 0.6); // Diffuse reflectivity
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
const vec3 Ks = vec3(0.75, 0.75, 0.75); // Specular reflectivity
const float Shininess = 6.f; // Specular shininess factor
layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform ivec2 size;

vec4 color = texture(picture, tc);

vec3 ads()
{
vec3 n = normalize( Normal );
vec3 s = normalize( vec3(LightPosition) - Position );
vec3 v = normalize(vec3(-Position));
vec3 r = reflect( -s, n );

return LightIntensity *
( Ka * vec3(color) +
Kd * vec3(color) * max( dot(s, n), 0.0 ));
}

void main()
{
	vec3 finalColor = ads();

	float dist1 = abs( Position.z );
	float fogFactor = (500.0f - dist1) /
	(500.0f - 0.5f);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );

	vec3 fogColor = vec3(0.1f, 0.1f, 0.1f);
	if(size.y == 1){
		fogColor = vec3(0.1f, 0.1f, 0.1f);
	}
	else if(size.y == 2){
		fogColor = vec3(0.0f, 0.05f, 0.0f);
	}
	else if(size.y == 3){
		fogColor = vec3(0.3f, 0.3f, 0.1f);
	}
	else if(size.y == 4){
		fogColor = vec3(0.2f, 0.0f, 0.0f);
	}
	else if(size.y == 5){
		fogColor = vec3(0.0f, 0.0f, 0.05f);
	}

	finalColor = vec3(mix( fogColor, finalColor, fogFactor ));

	FragColor = vec4(finalColor, color.a);
}

