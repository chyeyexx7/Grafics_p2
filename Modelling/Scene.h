#pragma once

#include <QObject>
#include <vector>
#include <memory>

#include <library/Common.h>
using namespace Common;

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include <library/vec.h>
#include <library/Common.h>


#include <Modelling/Objects/Mesh.h>
#include <Modelling/Objects/Cub.h>
#include <Modelling/Objects/Plane.h>
#include <Modelling/Lights/Light.h>
#include <Rendering/Camera.h>

#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <library/vec.h>
#include <QJsonArray>
#include <QJsonObject>

using namespace std;

// Scene: contains all objects, lights to visualize the scene
// the viewer is placed in the z+ axis

class Scene {

public:

    vector<shared_ptr<Mesh>> objects;
    vector<shared_ptr<Light>> lights;
    shared_ptr<Plane> base;
    shared_ptr<Cub> cub; // cube Map
    bool CUBEMAP = false;

    vec3 lightAmbientGlobal;
    shared_ptr<Camera> camera;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    Scene();
    ~Scene();

    void   addObject(shared_ptr<Mesh> obj);
    void   addObject(shared_ptr<Plane> obj);
    void   addLight(shared_ptr<Light> l);
    shared_ptr<Light> getLightActual();
    void   setLightActual(shared_ptr<Light> l);

    void setCamera(shared_ptr<Camera> c);

    void toGPU(shared_ptr<QGLShaderProgram> p);
    void draw();

    void lightsToGPU(shared_ptr<QGLShaderProgram> program);
    void setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program);

    void calculCapsaMinCont3DEscena();
    void update(int nframe);

};

