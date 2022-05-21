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


void Builder::newDataScene()
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del fitxer .json de tipus REALDATA
    // El nom del fitxer s'obtindrà amb un QFileDialog
    // Utilitza la teva SceneFactoryData per a llegir el fitxer
    // i crear l'escena corresponent.
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

    }

     emit newScene(scene);
}

