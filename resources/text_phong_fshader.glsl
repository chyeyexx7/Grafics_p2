#version 330

in vec4 normal;
in vec4 position;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;

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

//Global light
uniform vec3 ambientGlobalLight;

//Struct material
struct mtr{
    vec3 Kd;
    vec3 Ka;
    vec3 Ks;
    float shininess;
    float opacity;
};
uniform mtr material;

//Posición del observador
uniform vec4 obs;

void main()
{
    vec3 Itotal = ambientGlobalLight * material.Ka;
    vec3 idkd;
    vec3 isks;
    vec3 iaka;

    //N es la normal al punto normalizada
    vec4 N = normal;
    //V es el vector normalizado entre el observador y el punto
    vec4 V = normalize(obs - position);
    //L es el vector normalizado entre la luz y el punto
    //Su calculo varia segun el tipo de luz
    vec4 L;
    //H se calcula a partir de N,L y V
    vec4 H;

    vec4 direction;
    float a, b, c, distance, attenuation;

    //Vamos a ir calculando phong para cada luz segun su tipo {Puntual, Direccional, Spot}
    for(int i=0; i<lights.length(); i++){
        //Luz puntual
        if(lights[i].lightType_gpu == 0){
            L = normalize(lights[i].lightPosition_gpu - position);
            //Calculamos el valor de la distancia
            distance = length(L);
            //Nos guardamos cada uno de los coeficientes a,b,c
            a = lights[i].coeficients_gpu.x;
            b = lights[i].coeficients_gpu.y;
            c = lights[i].coeficients_gpu.z;
            //Calculo de la atenuación
            attenuation = a*distance*distance + b*distance + c;
        }

        //Luz direccional (no tenemos posición, solo dirección)
        else if(lights[i].lightType_gpu == 1){
            L = normalize(-lights[i].lightDirection_gpu);
            attenuation = 1.0;
        }
        H = normalize(L+V);
        idkd = lights[i].lightID_gpu * (texture(texMap, v_texcoord).rgb)  * max(dot(N,L), 0.0);
        isks = lights[i].lightIS_gpu * material.Ks * pow(max(dot(N,H), 0.0), material.shininess);
        iaka = lights[i].lightIA_gpu * material.Ka;
        //Para hacer pruebas con los ejemplos del campus hemos quitado la atenuación de la fórmula de phong
        //Itotal += ((idkd + isks)/attenuation) + iaka;
        Itotal += ((idkd + isks)/attenuation) + iaka;
    }
    //El color de salida será el calculado con la fórmula de phong

    colorOut =  vec4(Itotal, 1.0);
}

