#version 330


layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 position;
out vec2 v_texcoord;


void main()
{
  gl_Position = projection*model_view*vPosition;
  position = vPosition;
  v_texcoord = normalize(position.xyz);
}
