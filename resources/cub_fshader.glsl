#version 330

IN vec2 v_texcoord;
OUT vec4 colorOut;

uniform samplerCube texMap;

void main()
{
    colorOut = vec4(texture(texMap, v_texcoord.xyz).rgb, 1.0f);
}

