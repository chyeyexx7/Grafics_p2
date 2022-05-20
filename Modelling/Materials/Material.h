#pragma once

#include <QObject>
#include <vector>
#include <memory>

#include <library/Common.h>
using namespace Common;

#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <library/vec.h>
#include <QJsonArray>
#include <QJsonObject>



using namespace std;

// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    Material(vec3 a, vec3 d, vec3 s, float shininess);
    Material(vec3 a, vec3 d, vec3 s, float shininess, float opacity);
    ~Material();

    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float shininess;
    float opacity; // opacity es la fraccio de 0..1 (0 és totalment transparent, 1 és totalment opac)
    void toGPU(shared_ptr<QGLShaderProgram> program);

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;



};

