#ifndef CUB_H
#define CUB_H

#include "Modelling/Objects/Mesh.h"

typedef vec4  color4;
typedef vec4  point4;

class Cub: public Mesh
{
  public:
      Cub();
      Cub(float p);
      ~Cub();
      void toGPU(shared_ptr<QGLShaderProgram> pr);
      void draw();
      void initTextura();

  private:
      vector<QImage> faces;
      void initVertex();
      void make();
};

#endif // CUB_H
