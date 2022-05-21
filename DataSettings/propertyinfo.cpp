
#include "PropertyInfo.h"

PropertyInfo::PropertyInfo()
{
}

#include <iostream>
//! [0]
void PropertyInfo::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString().toUpper();
    }
    if (json.contains("gyzmo") && json["gyzmo"].isString()) {
        QString objStr = json["gyzmo"].toString().toUpper();
        //gyzmo = ObjectFactory::getInstance().getObjectType(objStr);
    }
    if (json.contains("minValue") && json["minValue"].isDouble()) {
        minValue = json["minValue"].toDouble();
    }
    if (json.contains("maxValue") && json["maxValue"].isDouble()) {
        maxValue = json["maxValue"].toDouble();
    }
    if (json.contains("material") && json["material"].isObject()) {
        QJsonObject auxMat = json["material"].toObject();
        if (auxMat.contains("type") && auxMat["type"].isString()) {
            QString tipus = auxMat["type"].toString().toUpper();
            //MaterialFactory::MATERIAL_TYPES t = MaterialFactory::getInstance().getMaterialType(tipus);
            //material = MaterialFactory::getInstance().createMaterial(t);
            //material->read(auxMat);
        }
    }
    if (json.contains("colorMap") && json["colorMap"].isString()) {
        QString objStr = json["colorMap"].toString().toUpper();
        //colorMapType = ColorMapStatic::getColorMapType(objStr);
    }

}
//! [0]
