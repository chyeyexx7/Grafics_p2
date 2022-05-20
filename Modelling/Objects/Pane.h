#pragma once

#include <library/Common.h>
#include <QGLShaderProgram>

#include <stdio.h>

const int NumVertices = 6;

typedef vec4  point4;

class Plane
{
public:
    Plane();
    Plane(int an, int al, int profu, GLfloat x0, GLfloat y0, GLfloat z0);
    ~Plane();
    void make();
    void toGPU(QGLShaderProgram *program);
    void draw();
    void aplicaTG(mat4 m);

private:

    void quad( int a, int b, int c, int d );

    int a; // amplada
    int h; // alcada
    int p; // profunditat
    GLdouble xorig, yorig, zorig;

    point4 vertices[8]; // 8 vertexs del cub

    int Index;
    point4 points[NumVertices]; // 6 punts
};

