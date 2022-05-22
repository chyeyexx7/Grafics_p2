#pragma once

#include <library/Common.h>
#include <QGLShaderProgram>
#include <Modelling/Materials/Material.h>

#include <stdio.h>

typedef vec4  point4;
const int NumVertices = 6;

class Plane
{
public:
    Plane();
    Plane(int an, int al, int profu, GLfloat x0, GLfloat y0, GLfloat z0);
    ~Plane();
    void make();
    void toGPU(shared_ptr<QGLShaderProgram> program);
    void draw();
    void aplicaTG(mat4 m);
    void setMaterial(shared_ptr<Material> m);
    void read(const QJsonObject &o);
private:

    void quad( int a, int b, int c, int d );

    int a; // amplada
    int h; // alcada
    int p; // profunditat
    GLdouble xorig, yorig, zorig;

    point4 vertices[4]; // 4 vertexs del pla
    shared_ptr<Material> material;

    int Index;
    point4 points[NumVertices]; // 6 punts

    GLuint buffer;
};

