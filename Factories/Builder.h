#ifndef BUILDER_H
#define BUILDER_H

#include <QtWidgets>
#include <Rendering/GLWidget.h>

class Builder : public QObject {
        Q_OBJECT

    shared_ptr<Scene> scene;
    GLWidget *glWidget;

public:
    Builder(GLWidget *glWid);

public slots:
    void newObjFromFile();
    void newVirtualScene();
    void newDataScene();

signals:
    void newObj(shared_ptr<Mesh> o);
    void newScene(shared_ptr<Scene> sc);
};

#endif // BUILDER_H
