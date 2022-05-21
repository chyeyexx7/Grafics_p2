#version 330

layout (location = 0) in vec4 vPosition;


uniform mat4 model_view;
uniform mat4 projection;

out vec4 position;

void main()
{
    gl_Position = projection*model_view*vPosition;
    position = gl_Position;
}
