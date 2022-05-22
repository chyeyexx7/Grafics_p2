#version 330

in vec3 v_texcoord;
out vec4 colorOut;

uniform samplerCube texMap;

void main()
{
    colorOut = vec4(texture(texMap, v_texcoord.xyz).rgb, 1.0f);
}

