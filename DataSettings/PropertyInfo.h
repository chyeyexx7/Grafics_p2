#pragma once


// #include "glm/glm.hpp"
#include "Modelling/Objects/Plane.h"
#include "Modelling/Materials/Material.h"
// #include "Factories/ObjectFactory.h"
// #include "Factories/MaterialFactory.h"
#include "Modelling/Materials/ColorMapStatic.h"

using namespace std;

class PropertyInfo
{
public:
    PropertyInfo();
    ~PropertyInfo() {};
    void read(const QJsonObject &json);

    vec3 getPuntBase(shared_ptr<Plane> base, vec2 puntReal);

    QString name;
    QString gyzmo;
    float minValue;
    float maxValue;
    shared_ptr<Material> material;
    ColorMapStatic::ColorMapType colorMapType;
};
