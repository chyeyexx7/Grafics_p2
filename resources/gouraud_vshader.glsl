#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

struct lightsGpu
{
    int lightType_gpu;
    vec3 lightIS_gpu;
    vec3 lightID_gpu;
    vec3 lightIA_gpu;
    vec3 coeficients_gpu;
    vec4 lightPosition_gpu;
    vec4 lightDirectiong_pu;
};

uniform lightsGpu lights[2];
uniform vec3 ambientGlobalLight;
uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    color = vec4(lights[0].lightIA_gpu, 1.0);
}
