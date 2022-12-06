#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat3 transform;
uniform mat3 view;
out vec2 pos;

void main()
{
    pos = aPos.xy + 0.5;
    gl_Position = vec4((view * transform * vec3(aPos, 1.0f)).xy, 0.0, 1.0);
    //gl_Position = vec4(aPos, 0.0, 1.0);
}
