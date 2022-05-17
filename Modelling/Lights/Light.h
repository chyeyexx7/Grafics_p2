#pragma once

#include <QObject>
#include <vector>
#include <memory>

#include <library/Common.h>
using namespace Common;

#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <library/vec.h>
#include <QJsonArray>
#include <QJsonObject>

using namespace std;
#define MAX 6
// Tipus de Lights
enum LightType {Puntual, Direccional, Spot};

// Classe que representa els atributs d'una Light
// TO DO: A la fase 1 has d'incloure els atributs necessaris per codificar una llum

class Light {
    public:
        Light(LightType l);
        Light(LightType l, vec3 lightIS, vec3 lightID, vec3 lightIA, vec4 lightPosition, vec4 lightDirection, vec3 coeficients);

        void LightsToGPU(QGLShaderProgram *program, int i);

        vec4 getLightPosition();
        void setLightPosition(vec4 v);

        vec3 getIa() const;
        void setIa(const vec3 &value);

        vec3 getId();
        void setId(vec3 i);

        vec3 getIs() const;
        void setIs(const vec3 &value);

        vec3 getCoeficients() const;
        void setCoeficients(const vec3 &value);

        LightType getTipusLight() const;
        void setTipusLight(const LightType &value);

        vec4 getLightDirection();
        void setLightDirection(vec4 lightDirection);

        LightType typeLight;
        vec3 lightIS;
        vec3 lightID;
        vec3 lightIA;
        vec3 coeficients;
        vec4 lightPosition;
        vec4 lightDirection;

        struct lightsid
        {
            GLuint type;
            GLuint lightIS;
            GLuint lightID;
            GLuint lightIA;
            GLuint coeficients_gpu;
            GLuint lightPosition;
            GLuint lightDirection;
        };
        lightsid gl_IdLightsVec[MAX];
};

