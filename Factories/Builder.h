#ifndef BUILDER_H
#define BUILDER_H

#include <QtWidgets>
#include <Rendering/GLWidget.h>
#include <Modelling/Materials/Material.h>
#include <DataSettings/InfoMapping.h>

class Builder : public QObject {
        Q_OBJECT

    shared_ptr<Scene> scene;
    shared_ptr<InfoMapping> mapping;
    GLWidget *glWidget;

public:
    Builder(GLWidget *glWid);
    shared_ptr<Material> mapeigMaterial(shared_ptr<PropertyInfo> propinfo, ColorMapStatic::ColorMapType tCM, double valorMonReal);
    void buildRealScene();


public slots:
    void newObjFromFile();
    void newVirtualScene();
    void newDataScene();


signals:
    void newObj(shared_ptr<Mesh> o);
    void newScene(shared_ptr<Scene> sc);
};

#endif // BUILDER_H
