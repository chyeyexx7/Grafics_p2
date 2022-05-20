#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 normals;


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
uniform lightsGpu lights[1];

uniform vec3 ambientGlobalLight;
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


    //Test para comprobar que las luces se envían correctamente al shader
    //color = vec4(lights[0].lightID_gpu, 1.0);

    //Test para comprobar que las normales se envían correctamente al shader
    color = (vec4(1,1,1,0)+normals)/2.0;

}
