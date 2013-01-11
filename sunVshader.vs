#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;


uniform mat4 VP;
uniform mat4 M;


out vec3 interpolatedColor;
out vec4 world_position;

void main()
{
    mat4 MVP = VP*M;

    vec4 v = vec4(vertexPosition_modelspace,1);
    world_position = MVP*v;


    gl_Position = MVP * v;


    interpolatedColor.r = 0.8;
    interpolatedColor.g = 0.8;
    interpolatedColor.b = 0.8;


}

