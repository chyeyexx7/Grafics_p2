#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 model_view;
uniform mat4 projection;

//Struct material
struct mtr{
    vec3 Kd;
    vec3 Ka;
    vec3 Ks;
    float shininess;
    float opacity;
};

uniform mtr material;

out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    color = vec4(material.Ka.x,material.Ka.y,material.Ka.z,1);
}
