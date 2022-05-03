#include "Modelling/Lights/Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    // TO DO: A canviar a la fase 1 de la practica 2

}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   return(vec3(1.0, 1.0, 1.0));
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    // TO DO: A canviar a la fase 1 de la practica 2

}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return(vec4(0.0, 0.0, 0.0, 0.0));
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    // TO DO: A canviar a la fase 1 de la practica 2
}


/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return(vec3(1.0, 1.0, 1.0));
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2

}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return(vec3(1.0, 1.0, 1.0));
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       return(vec3(1.0, 1.0, 1.0));
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    return Puntual;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
}
