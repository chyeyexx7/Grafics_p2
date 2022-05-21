#include "InfoMapping.h"

//! [0]
void InfoMapping::read(const QJsonObject &json)
{
    if (json.contains("Real") && json["Real"].isObject()) {
        QJsonObject jobject = json["Real"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Rxmin = objectsArray[0].toDouble();
            Rzmin = objectsArray[1].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Rxmax = objectsArray[0].toDouble();
            Rzmax = objectsArray[1].toDouble();
         }
    }
    if (json.contains("Virtual") && json["Virtual"].isObject()) {
        QJsonObject jobject = json["Virtual"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Vxmin = objectsArray[0].toDouble();
            Vymin = objectsArray[1].toDouble();
            Vzmin = objectsArray[2].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Vxmax = objectsArray[0].toDouble();
            Vymax = objectsArray[1].toDouble();
            Vzmax = objectsArray[2].toDouble();
         }
    }
    if (json.contains("properties") && json["properties"].isArray()) {
        QJsonArray propsArray = json["properties"].toArray();

        for (int propIndex = 0; propIndex < propsArray.size(); propIndex++) {
            QJsonObject propObject = propsArray[propIndex].toObject();
            shared_ptr<PropertyInfo> p = make_shared<PropertyInfo>();
            p->read(propObject);
            vector<vec3> values;
            if (propObject.contains("data") && propObject["data"].isArray()) {
                QJsonArray dataArray = propObject["data"].toArray();
                for (int dataIndex = 0; dataIndex < dataArray.size(); dataIndex++) {
                    QJsonArray value = dataArray[dataIndex].toArray();
                    vec3 sample;
                    sample[0] = value[0].toDouble();
                    sample[1] = value[1].toDouble();
                    sample[2] = value[2].toDouble();
                    values.push_back(sample);
                }
            }
            props.push_back(make_pair(p, values));
        }
    }

}
//! [0]
