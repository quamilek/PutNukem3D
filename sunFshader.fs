#version 330 core

in vec3 interpolatedColor;
in vec4 world_position;




out vec3 color;



void main()
{



	color.r = interpolatedColor.r;
	color.g = interpolatedColor.g;
	color.b = interpolatedColor.b;



}

