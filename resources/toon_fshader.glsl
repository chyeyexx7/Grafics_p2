#version 330

in vec4 normal;
in vec4 position;

out vec4 colorOut;

//Struct luces
struct lightsGpu
{
    int lightType_gpu;
    vec3 lightIS_gpu;
    vec3 lightID_gpu;
    vec3 lightIA_gpu;
    vec3 coeficients_gpu;
    vec4 lightPosition_gpu;
    vec4 lightDirection_gpu;
};

uniform lightsGpu lights[1];

//Posición del observador
uniform vec4 obs;

void main()
{
    float intensity, silhouette;
    vec4 color;

    // Calculamos la intensidad del toon entre 4 intervalos
    intensity = dot(lights[0].lightDirection_gpu, normal);
    if (intensity > 0.95)
        color = vec4(1.0, 0.5, 0.5, 1.0);
    else if (intensity > 0.5)
        color = vec4(0.6, 0.3, 0.3, 1.0);
    else if (intensity > 0.25)
        color = vec4(0.4, 0.2, 0.2, 1.0);
    else
        color = vec4(0.2, 0.1 ,0.1, 1.0);

    // Calculamos la silueta con la fórmula cos(alfa), donde alfa es el producto escalar entre normal y vector visión.
    // Si alfa = 0 tenemos un borde.
    silhouette = dot(normal, normalize(obs - position));
    if (silhouette < 0.1)
        color *= silhouette;

    colorOut = color;
}

