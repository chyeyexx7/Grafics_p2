#version 330


in vec4 position;
out vec4 colorOut;

uniform mat4 model_view;
uniform mat4 projection;
float depthFactor;
void main()
{

    float factorDepth = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far)
            / (gl_DepthRange.far - gl_DepthRange.near);

    float clipDepth = factorDepth / gl_FragCoord.w;
    colorOut = vec4((clipDepth * 0.5) + 0.5);
}

