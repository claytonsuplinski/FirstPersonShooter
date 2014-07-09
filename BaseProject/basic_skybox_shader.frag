/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

in vec3 Position;
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform ivec2 size;

vec4 color = texture(picture, tc);
float factor = 1.0f;

vec3 ads(){
return LightIntensity * ( Ka * vec3(color) );
}

void main(){

	if(size.x > 0.5 || size.y > 0.5){
		color = vec4(ads(), 1.0f);
	}

	float dist1 = abs( Position.z );
	float fogFactor = (20.0f - dist1) /
	(20.0f - 5.0f);
	fogFactor = clamp( fogFactor, 0.0, 0.5 );
	//Fog
	if(size.y == 1){
		FragColor = vec4(mix( vec3(0.1f, 0.1f, 0.1f), vec3(color), fogFactor ), 1.0);
	}
	else if(size.y == 2){
		FragColor = vec4(mix( vec3(0.0f, 0.05f, 0.0f), vec3(color), fogFactor ), 1.0);
	}
	else if(size.y == 3){
		FragColor = vec4(mix( vec3(0.3f, 0.3f, 0.1f), vec3(color), fogFactor ), 1.0);
	}
	else if(size.y == 4){
		FragColor = vec4(mix( vec3(0.2f, 0.0f, 0.0f), vec3(color), fogFactor ), 1.0);
	}
	else if(size.y == 5){
		FragColor = vec4(mix( vec3(0.0f, 0.0f, 0.05f), vec3(color), fogFactor ), 1.0);
	}
	else{
		FragColor = color;
	}
}

