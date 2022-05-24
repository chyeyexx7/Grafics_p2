
#include "PropertyInfo.h"

PropertyInfo::PropertyInfo()
{
}


//! [0]
void PropertyInfo::read(const QJsonObject &json)
{

    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString().toUpper();
    }
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        QString objStr = json["objFileName"].toString();
        gyzmo = objStr;
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
            material = make_shared<Material>();
            material->read(auxMat);
        }
    }
    if (json.contains("colorMap") && json["colorMap"].isString()) {
        QString objStr = json["colorMap"].toString().toUpper();
        //colorMapType = ColorMapStatic::getColorMapType(objStr);
    }

}
//! [0]
