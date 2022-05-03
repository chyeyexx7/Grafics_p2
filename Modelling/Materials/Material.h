#pragma once

#include <QGLShaderProgram>
#include <memory>

using namespace std;
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();

    void toGPU(shared_ptr<QGLShaderProgram> program);

};

