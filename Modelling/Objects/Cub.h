#ifndef CUB_H
#define CUB_H
#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <stdio.h>


const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;

class Cub: public Mesh
{
  public:



      Cub();
      Cub(float p);
      ~Cub();
      void make();
      void toGPU(QGLShaderProgram *program);
      void draw();
      void aplicaTG(mat4 m);

  private:

      void quad( int a, int b, int c, int d );
      void initTextura();

      int a; // amplada
      int h; // alcada
      int p; // profunditat
      GLdouble xorig, yorig, zorig;

      point4 vertices[8]; // 8 vertexs del cub

      int Index;
      point4 points[NumVertices]; // 36 punts: cub triangulat
      color4 colors[NumVertices]; // colors en aquests punts
      vec2 vertexsTextura[NumVertices]; // coordenades de textura associades a cada vertex

      QOpenGLTexture *texture;

      GLuint buffer;
};

#endif // CUB_H
