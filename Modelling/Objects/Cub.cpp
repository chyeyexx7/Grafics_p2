#include "Modelling/Objects/Cub.h"

Cub::Cub(): Cub(10.0)
{
    qDebug() <<"Estic en el constructor del cub\n";
}

// Constructora amb tots els parametres, un cub té 36 punts
Cub::Cub(float p): Mesh(36)
{
    qDebug() <<"Estic en el constructor parametritzat del cub\n";

    /**
        Definimos las coordenadas de los 8 vértices del cubo usando p como punto 0,0,0 del escenario
        n sentido reloj, empezando desde (-x,-y,z), parte de arriba primero
                 _________
              v1/        /|v2
               /|       / |
            v5/--------/v6|
              | |______|__|
              |/ v0    | /v3
              |________|/
             v4        v7

      **/
    vertexs.push_back(point4(-p/2, -p/2,  p/2, 1.0));   // v0
    vertexs.push_back(point4(-p/2,  p/2,  p/2, 1.0));   // v1
    vertexs.push_back(point4( p/2,  p/2,  p/2, 1.0));   // v2
    vertexs.push_back(point4( p/2, -p/2,  p/2, 1.0));   // v3

    vertexs.push_back(point4(-p/2, -p/2, -p/2, 1.0));   // v4
    vertexs.push_back(point4(-p/2,  p/2, -p/2, 1.0));   // v5
    vertexs.push_back(point4( p/2,  p/2, -p/2, 1.0));   // v6
    vertexs.push_back(point4( p/2, -p/2, -p/2, 1.0));   // v7

    initVertex();
    make();
}

// Destructora
Cub::~Cub()
{
}


// Realitzacio de la geometria del cub en una genList o en el vertex array, segons el que visualitzem

void Cub::make()
{
     Index = 0;
     qDebug() << cares[0].idxVertices[2];
     for(unsigned int i=0; i<cares.size(); i++){
         for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
             points[Index] = vertexs[cares[i].idxVertices[j]];
             Index++;
         }
     }
}

void Cub::initTextura()
 {
     qDebug() << "Initializing textures...\n";

     QImage img[6];

     for(GLuint i=0; i<faces.size(); i++) {
        img[i] = QImage(faces[i]).convertToFormat(QImage::Format_RGBA8888);
     }
     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);

     texture = make_shared<QOpenGLTexture>(QOpenGLTexture::TargetCubeMap);
     qDebug() <<"texture id: ";
     qDebug() << texture->textureId();
     if(!texture->isCreated()) texture->create();

     glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureId());

     texture->setFormat(QOpenGLTexture::RGBAFormat);
     texture->setSize(img[0].width(), img[0].height(), img[0].depth());
     texture->generateMipMaps();
     texture->allocateStorage();

     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[0].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[1].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[2].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[3].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[4].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[5].constBits(), 0);

     texture->setWrapMode(QOpenGLTexture::ClampToEdge);
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);

     glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

 }

// Carrega a la GPU del cub

void Cub::toGPU(shared_ptr<QGLShaderProgram> pr){
    qDebug() << "Passo el Cub a la GPU.....\n";
    program = pr;

    // S'activa la textura i es passa a la GPU
    texture->bind(texture->textureId());
    program->setUniformValue("texEnvironment", texture->textureId());

    // Creació d'un vertex array object
    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Transferència dels punts, colors i coordenades de textura al vertex buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index,
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, points );


    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glEnable(GL_TEXTURE_CUBE_MAP);
}


void Cub::draw()
{
    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, Index);
    glDepthFunc(GL_LESS);

    glDisableVertexAttribArray(0);

    glDisable(GL_TEXTURE_CUBE_MAP);
}

void Cub::initVertex() {

    // Bottom
    Cara *bottom1 = new Cara(4, 0, 7, -1);
    Cara *bottom2 = new Cara(7, 0, 3, -1);

    //Front
    Cara *front1 = new Cara(0, 1, 3, -1);
    Cara *front2 = new Cara(3, 1, 2, -1);

    // Top
    Cara *top1 = new Cara(1, 5, 2, -1);
    Cara *top2 = new Cara(2, 5, 6, -1);

    // Right
    Cara *right1 = new Cara(3, 2, 7, -1);
    Cara *right2 = new Cara(7, 2, 6, -1);

    // Left
    Cara *left1 = new Cara(4, 5, 0, -1);
    Cara *left2 = new Cara(0, 5, 1, -1);

    // Back
    Cara *back1 = new Cara(7, 6, 4, -1);
    Cara *back2 = new Cara(4, 6, 5, -1);

    cares.push_back(*bottom1);
    cares.push_back(*bottom2);
    cares.push_back(*front1);
    cares.push_back(*front2);
    cares.push_back(*top1);
    cares.push_back(*top2);
    cares.push_back(*right1);
    cares.push_back(*right2);
    cares.push_back(*left1);
    cares.push_back(*left2);
    cares.push_back(*back1);
    cares.push_back(*back2);

    faces.push_back(QImage("://resources/textures/yokohama/posx.jpg"));
    faces.push_back(QImage("://resources/textures/yokohama/negx.jpg"));
    faces.push_back(QImage("://resources/textures/yokohama/negy.jpg"));
    faces.push_back(QImage("://resources/textures/yokohama/posy.jpg"));
    faces.push_back(QImage("://resources/textures/yokohama/posz.jpg"));
    faces.push_back(QImage("://resources/textures/yokohama/negz.jpg"));
}

