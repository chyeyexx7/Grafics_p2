#pragma once

#include <QGLShaderProgram>
#include <memory>
#include <library/vec.h>

using namespace std;
using namespace Common;

// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    vec3 light;
    void toGPU(shared_ptr<QGLShaderProgram> program);

};

