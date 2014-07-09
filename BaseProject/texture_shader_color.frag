/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Texture shader - Used almost everywhere in 
the project for applying images to shapes. Also
changes to correspond with the time of day and 
environment.
*/
#version 400

in vec4 color2;
in vec3 Position;
in vec3 Normal;
const vec4 LightPosition = vec4(0.0, 0.0, 0.0, 0.0);
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Kd = vec3(0.6, 0.6, 0.6); // Diffuse reflectivity
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
const vec3 Ks = vec3(0.75, 0.75, 0.75); // Specular reflectivity
const float Shininess = 6.0f; // Specular shininess factor
layout (location = 0) out vec4 FragColor;

in vec2 tc;
uniform sampler2D picture;
uniform ivec2 size;
uniform float time;

vec4 color = texture(picture, tc);
vec3 setting = vec3(0.0, 0.0, 0.0);
float factor = 1.0f;

const float blurSizeH = 1.0 / 300.0;
const float blurSizeV = 1.0 / 200.0;

vec3 ads()
{
vec3 n = normalize( Normal );
vec3 s = normalize( vec3(LightPosition) - Position );
vec3 v = normalize(vec3(-Position));
vec3 r = reflect( -s, n );
//Underwater setting
if(size.y == 1){
	setting = vec3(0.0, 0.05, 0.35);
	factor = 0.45;
}
//Night
if(size.x == 1){
float dx = Position.x - 0.5;
float dy = Position.y - 0.5;
float dist = sqrt(dx * dx + dy * dy);
vec3 color2 =
mix( vec3(color.x, color.y, color.z), vec3(0.0,0.0,0.0),
smoothstep( 0.2, 4.0, dist )
);
return 
LightIntensity * factor *
( Ka * color2 +
Kd * color2 * max( dot(s, n), 0.0 ));
}
//Twilight
else if(size.x == 2){ 
	return setting + vec3(0.35, 0.15, 0.0) +
	LightIntensity * factor *
	( Ka * 0.35 * vec3(color) +
	Kd * 0.35 * vec3(color) * max( dot(s, n), 0.0 ));
}
//Normal
return setting +
LightIntensity * factor *
( Ka * vec3(color) +
Kd * vec3(color) * max( dot(s, n), 0.0 ));
}

void main()
{
//Add a little blurring (too costly)
	/*vec4 sum = vec4( 0.0 );
    for (int x = -2; x <= 2; x++)
        for (int y = -2; y <= 2; y++)
            sum += texture(
                picture,
                vec2( tc.x + x * blurSizeH, tc.y + y * blurSizeV )
            )/ 81.0;
			
			FragColor = 0.5 * sum + 0.5 * vec4(ads(), 1.0f);
			*/

	float dist1 = abs( Position.z );
	float fogFactor = (200.0f - dist1) /
	(200.0f - 0.5f);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );

	float fogFactorLight = (400.0f - dist1)/(400.0f - 0.5f);
	fogFactorLight = clamp( fogFactorLight, 0.0, 1.0 );

	float factor = time - 10*int(time/10);
	vec3 finalColor = 1*ads()+0.25*color2.xyz;
	if(finalColor.x < 0.8 && finalColor.y < 0.8 && finalColor.z < 0.8){
		finalColor = vec3(mix( vec3(0.1f, 0.1f, 0.1f), finalColor, fogFactor ));
	}
	else{
		finalColor = vec3(mix( vec3(0.1f, 0.1f, 0.1f), finalColor,  fogFactorLight ));
	}
	
	//Change the colors based on time
	FragColor = vec4(finalColor, color2.a);
}

