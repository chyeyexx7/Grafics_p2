#include "Factories/Builder.h"

Builder::Builder(GLWidget *glWid)
{
    glWidget = glWid;
    scene = glWidget->getScene();
}

void Builder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            // OJO! El primer paràmetre de la constructora de l'Object és el número de punts del model.
            // Si l'objecte té més punts en el .bj, cal canviar aquest valor
            auto obj = make_shared<Mesh>(1000000, fileName);
            scene->addObject(obj);
            scene->camera->actualitzaCamera(scene->capsaMinima);
            emit newObj(obj);
    }
}

void Builder::newVirtualScene() {
    // TO DO Fase 1: creació de la nova escena Virtual a partir d'un fitxer
    // de a partir d'un fitxer .json de tipus VIRTUAL.
    // El nom del fitxer es llegirà usant una finestra de diàleg
    // QFileDialog
    // Nomes es llegiran fitxers .json que continguin objectes tipus BoundaryObject.
    // Usa la teva SceneFactoryVirtual
    // per a construir l'escena tal i com feies a la practica 1
    QString fileName = QFileDialog::getOpenFileName();
    // Comprovem si el fitxer d'escena virtual existeix
    if (!fileName.isNull()){
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)){
            qDebug() << "File open error";
        }
        else {
            qDebug() << "File open !";
        }

        QByteArray saveData = file.readAll();
        QJsonParseError error;
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));

        if (loadDoc.isNull()){
            qWarning("Parse error in json virtual scene file.");
        }
        else{
            QJsonObject json = loadDoc.object();
            if (json.contains("objects") && json["objects"].isArray()) {
                QJsonArray objectsArray = json["objects"].toArray();

                for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex ++){
                    QJsonObject objectObject = objectsArray[objectIndex].toObject();

                    // Comprovem si l'objecte del fitxer es tipus mesh
                    if (objectObject.contains("type") && objectObject["type"].isString()
                            && objectObject["type"] == "MESH"){

                        // Busquem el fitxer de l'objecte mesh
                        if (objectObject.contains("objFileName") && objectObject["objFileName"].isString()){

                            QString filename = objectObject["objFileName"].toString();

                            // Afegim a la llista d'objectes la nova mesh
                            auto obj = make_shared<Mesh>(1000000, filename);
                            // Afegim el material al objecte
                            if (objectObject.contains("material") && objectObject["material"].isObject()) {
                                QJsonObject auxMat = objectObject["material"].toObject();
                                auto mat = make_shared<Material>();
                                mat->read(auxMat);
                                obj->setMaterial(mat);
                            }
                            scene->addObject(obj);
                        }
                    }
                }
            }
        }
    }
    emit newScene(scene);
}


#include <iostream>
void Builder::newDataScene()
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del fitxer .json de tipus REALDATA
    // El nom del fitxer s'obtindrà amb un QFileDialog
    // Utilitza la teva SceneFactoryData per a llegir el fitxer
    // i crear l'escena corresponent.
    QString fileName = QFileDialog::getOpenFileName();
    // Comprovem si el fitxer d'escena virtual existeix
    if (!fileName.isNull()) {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "File open error";
        }
        else {
            qDebug() << "File open !";
        }

        QByteArray saveData = file.readAll();
        QJsonParseError error;
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));

        if (loadDoc.isNull()){
            qWarning("Parse error in json virtual scene file.");
        } else{
            QJsonObject json = loadDoc.object();

            if (json.contains("base") && json["base"].isObject()) {
                QJsonObject jbase = json["base"].toObject();
                //shared_ptr<Plane> o = make_shared<Plane>();
                //shared_ptr<Material> material = make_shared<Material>();
                //o->make();
                //o->setMaterial(material);
                //o->read(jbase);
                //scene->addObject(o);
                //scene->base = o;
            }

            mapping = make_shared<InfoMapping>();
            mapping->read(json);
            buildRealScene();

         }
    }
    emit newScene(scene);
}


void Builder::buildRealScene() {

    float maxX = mapping->Vxmax;
    float maxY = mapping->Vzmax;
    float maxS = 0.5*mapping->Vymax;
    float minX = mapping->Vxmin;
    float minY = mapping->Vzmin;
    float minS = 0.1f;

    float baseX = mapping->Rxmin;
    float baseY = mapping->Rzmin;
    float rangeX = mapping->Rxmax - baseX;
    float rangeY = mapping->Rzmax - baseY;

    for (unsigned int i=0; i<mapping->props.size(); i++) {
        // A props[i].first es te la informació de la propietat per fer el mapping de cada valor
         shared_ptr<PropertyInfo> propinfo = mapping->props[i].first;
         // Per cada valor, es dona d'alta un objecte a l'escena
         for (unsigned int j=0; j<mapping->props[i].second.size(); j++) {
             // TO DO Fase 2:
             // col.locació de l'objecte base de l'escena
             //
             // Col.locació de l'objecte o gizmo del valor de la dada al Mon Virtual
             //  TODO Fase 2: Cal calcular l'escalat del gizmo segons el valor llegit
             //QString s = "ObjectFactory::getInstance().getNameType(propinfo->gyzmo);"
             shared_ptr<Mesh> o = make_shared<Mesh>(1000000, propinfo->gyzmo);
             //shared_ptr<Mesh> o = make_shared<Mesh>(s, mapping->props[i].second[j][2]);

             o->setMaterial(mapeigMaterial(propinfo, propinfo->colorMapType,
                                           mapping->props[i].second[j][2]));

             //TRANSLATE
             float rX = ((mapping->props[i].second[j][0] - baseX) / rangeX) * (maxX - minX) + minX;
             float rY = ((mapping->props[i].second[j][1] - baseY) / rangeY) * (maxY - minY) + minY;

             //vec3 trans(rX, 0, -rY);

             //o->aplicaTG(make_shared<TranslateTG>(trans));

             //SCALE
             float realValue = mapping->props[i].second[j][2];
             float value = ((realValue - propinfo->minValue) / (propinfo->maxValue - propinfo->minValue)*(maxS-minS)) + minS;
             //o->aplicaTG(make_shared<ScaleTG>(value));

             // Afegir objecte a l'escena
             scene->addObject(o);
         }
    }
}

shared_ptr<Material> Builder::mapeigMaterial(shared_ptr<PropertyInfo> propinfo, ColorMapStatic::ColorMapType tCM, double valorMonReal) {

    // TO DO Fase 2: Cal mapejar el color difus al color de la paleta o ColorMap segons el valorMonReal i
    // els valors minims i maxims de les propietats
    // Tens els valors minims i maxim de cada propietat a l'estructura de setup d'aquesta classe

    auto cm = make_shared<ColorMapStatic>(tCM);
    int idx = (int)(255.0*(valorMonReal-propinfo->minValue)/(propinfo->maxValue-propinfo->minValue));

    shared_ptr<Material> mat = make_shared<Material>(propinfo->material->Ka,
                                                     vec3(0.8,0.5,0.5),
                                                     propinfo->material->Ks,
                                                     propinfo->material->shininess,
                                                     propinfo->material->opacity);
    return mat;
}

