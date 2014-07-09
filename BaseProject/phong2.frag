/*
Name: Clayton Suplinski
Project: First-Person Shooter

A phong shader that changes the object's color according to a time variable
*/

#version 400
in vec3 color;
in vec3 Position;
in vec3 Normal;
const vec4 LightPosition = vec4(500.0, 100.0, 500.0, 1.0);
const vec3 LightIntensity = vec3(0.85, 0.85, 0.85);
const vec3 Kd = vec3(0.1, 0.1, 0.1); // Diffuse reflectivity
const vec3 Ka = vec3(0.85, 0.85, 0.85); // Ambient reflectivity
const vec3 Ks = vec3(0.75, 0.75, 0.75); // Specular reflectivity
const float Shininess = 6.0f; // Specular shininess factor
uniform float time;

layout( location = 0 ) out vec4 FragColor;

vec3 ads( )
{
vec3 n = normalize( Normal );
vec3 s = normalize( vec3(LightPosition) - Position );
vec3 v = normalize(vec3(-Position));
vec3 r = reflect( -s, n );
return
LightIntensity *
( Ka * color +
Kd * color * max( dot(s, n), 0.0 ) +
Ks * color * pow( max( dot(r,v), 0.0 ), Shininess ) );
}

void main() {
float dist = abs( Position.z );
float fogFactor = (60.0f - dist) /
(60.0f - 35.0f);
fogFactor = clamp( fogFactor, 0.0, 1.0 );
int factor = int(time);
vec3 finalColor = ads();
//Change the colors based on time
if(factor%6 == 0){finalColor.x = 3* finalColor.x;finalColor.y = 1* finalColor.y;finalColor.z = 0.25* finalColor.z;}
else if(factor%6 == 1){finalColor.y = 1* finalColor.y;finalColor.x = 0.25* finalColor.x;finalColor.z = 3* finalColor.z;}
else if(factor%6 == 2){finalColor.z = 0.25* finalColor.z;finalColor.x = 3* finalColor.x;finalColor.y = 1* finalColor.y;}
else if(factor%6 == 3){finalColor.x = 6* finalColor.x;finalColor.y = 0.25* finalColor.y;finalColor.z = 0.25* finalColor.z;}
else if(factor%6 == 4){finalColor.y = 0.25* finalColor.y;finalColor.x = 6* finalColor.x;finalColor.z = 0.25* finalColor.z;}
else if(factor%6 == 5){finalColor.z = 0.25* finalColor.z;finalColor.x = 0.25* finalColor.x;finalColor.y = 6* finalColor.y;}
FragColor = vec4(finalColor, 1.0);
}