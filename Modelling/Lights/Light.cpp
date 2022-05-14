#include "Modelling/Lights/Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    // TO DO: A canviar a la fase 1 de la practica 2
    typeLight = t;
    lightIS = vec3(0.4,0.4,0.4);
    lightID = vec3(0.8,0.8,0.8);
    lightIA = vec3(0.3,0.3,0.3);
    lightPosition = vec4(8,10,7,9);
    lightDirection = vec4(0.9,0.9,0.9,0.9);
}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   return lightID;
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    this->lightID = i;
}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return lightPosition;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->lightPosition = v;
}

/**
 * @brief Light::getLightDirection
 */
vec4 Light::getLightDirection() {
    return lightDirection;
}

/**
 * @brief Light::setLightDirection
 * @param dir
 */
void Light::setLightDirection(vec4 dir) {
    this->lightDirection = dir;
}

/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return lightIA;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->lightIA = value;
}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return lightIS;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->lightIS = value;
}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return coeficients;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->coeficients = value;
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    return typeLight;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    typeLight = value;
}

// TO DO: Enviar dades llum a la GPU.
// Aquest métode el crida lightsToGPU de scene.cpp
void Light::LightsToGPU(QGLShaderProgram *program, int i) {

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

    gl_IdLightsVec[i].type = program->uniformLocation(QString("lights[%1].lightType_gpu").arg(i));
    gl_IdLightsVec[i].lightIS = program->uniformLocation(QString("lights[%1].lightIS_gpu").arg(i));
    gl_IdLightsVec[i].lightID = program->uniformLocation(QString("lights[%1].lightID_gpu").arg(i));
    gl_IdLightsVec[i].lightIA = program->uniformLocation(QString("lights[%1].lightIA_gpu").arg(i));
    gl_IdLightsVec[i].coeficients_gpu = program->uniformLocation(QString("lights[%1].coeficients_gpu").arg(i));
    gl_IdLightsVec[i].lightPosition = program->uniformLocation(QString("lights[%1].lightPosition_gpu").arg(i));
    gl_IdLightsVec[i].lightDirection = program->uniformLocation(QString("lights[%1].lightDirectiong_pu").arg(i));

    glUniform1i(gl_IdLightsVec[i].type, this->typeLight);
    glUniform3fv(gl_IdLightsVec[i].lightIS, 1, this->lightIS);
    glUniform3fv(gl_IdLightsVec[i].lightID, 1, this->lightID);
    glUniform3fv(gl_IdLightsVec[i].lightIA, 1, this->lightIA);
    glUniform3fv(gl_IdLightsVec[i].coeficients_gpu, 1, this->coeficients);
    glUniform4fv(gl_IdLightsVec[i].lightPosition, 1, this->lightPosition);
    glUniform4fv(gl_IdLightsVec[i].lightDirection, 1, this->lightDirection);
}
