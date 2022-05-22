#include <cub.h>

Cub::Cub(): Mesh(8.0)
{
    qDebug() <<"Estic en el constructor del cub\n";
}

// Constructora amb tots els parametres
Cub::Cub(float p): Mesh(8.0)
{
    qDebug() <<"Estic en el constructor parametritzat del cub\n";
    a = an;
    h = al;
    p = profu;
    xorig = x0;
    yorig = y0;
    zorig = z0;
}

// Destructora
Cub::~Cub()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void Cub::quad( int a, int b, int c, int d )
{
    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}


// Realitzacio de la geometria del cub en una genList o en el vertex array, segons el que visualitzem

void Cub::make()
{
     qDebug() <<"Estic en el make del cub\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
     Index = 0;
     for(unsigned int i=0; i<cares.size(); i++){
         for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
             points[Index] = vertexsTextura[cares[i].idxVertices[j]];
             Index++;
         }
     }
    initTextura();

}

void Cub::initTextura()
 {
     qDebug() << "Initializing textures...\n";

     QImage img[6];

     for(GLuint i=0; i<faces.size(); i++) {
        img[i] = QImage(´faces[i]).convertToFormat(QImage::Format_RGBA8888);
     }
     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);

     texture = QOpenGLTexture(QOpenGLTexutre::TargetCubeMap);
     if(!texture->isCreated()) texture->create();

     glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureId());

     texture->setFormat(QOpenGLTexture::RGBAFormat);
     texture->setSize(img[0].width(), img[0].height(), img[0].depth());
     texture->generateMipMaps();
     texture->allocateStorage();

     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[0].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[1].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[2].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[3].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[4].constBits(), 0);
     texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGBA,
                      QOpenGLTexture::UInt8, (const void*)img[5].constBits(), 0);

     texture->setWrapMpde(QOPenGLTexture::ClampToEdge);
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);

     glGenerationMipMap(GL_TEXTURE_CUBE_MAP);

 }

// Carrega a la GPU del cub

void Cub::toGPU(QGLShaderProgram *program){
    qDebug() << "Passo el Cub a la GPU.....\n";

    // S'activa la textura i es passa a la GPU
    texture->bind(0);
    program->setUniformValue("texMap", 0);

    // Creació d'un vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Transferència dels punts, colors i coordenades de textura al vertex buffer object
    glBufferData( GL_ARRAY_BUFFER, sizeof(points)*Index,
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points)*Index, points );


    // set up vertex arrays

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);


    glEnable( GL_DEPTH_TEST );
}


void Cub::draw()
{
    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthFunc(GL_EQUAL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);

    glDisable(GL_TEXTURE_CUBE_MAP)
}

void Cub::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );


}
