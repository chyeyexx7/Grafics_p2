#include "Plane.h"

Plane::Plane()
{
    qDebug() << "Estic en el constructor del Plane\n";
    // Plane centrat al 0,0,0 amb dimensió 1 a totes les seves arestes
    xorig = -0.5; yorig = -0.50; zorig = -0.5;
    a = 1.0;
    h = 1.0;
    p = 1.0;

    // Vertices of a unit Planee centered at origin, sides aligned with axes
    vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );
}

// Constructora amb tots els parametres
Plane::Plane(int an, int al, int profu, const GLfloat x0, GLfloat y0, GLfloat z0)
{
    qDebug() << "Estic en el constructor parametritzat del Plane\n";
    a = an;
    h = al;
    p = profu;
    xorig = x0;
    yorig = y0;
    zorig = z0;
}

// Destructora
Plane::~Plane()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void Plane::quad( int a, int b, int c, int d )
{
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[b]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[a]; Index++;
    points[Index] = vertices[c]; Index++;
    points[Index] = vertices[d]; Index++;
}


// Realitzacio de la geometria del Plane en el vertex array
void Plane::make()
{
    qDebug() << "Estic en el make del Plane\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    quad( 1, 0, 3, 2 );
}

// Carrega del Plane a la GPU
void Plane::toGPU(shared_ptr<QGLShaderProgram> program){

    qDebug() << "Passo les dades del Plane a la GPU\n";

    // Creació d'un vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Creacio i inicialitzacio d'un buffer object

    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points),
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
   // glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );


    // set up vertex arrays

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// Pintat dels arrays definits del Plane: activació del pipeline de GL
void Plane::draw()
{
   glDrawArrays( GL_TRIANGLES, 0, NumVertices );
}

void Plane::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Plane::read (const QJsonObject &json)
{
    /*if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        minpoint[0] = auxVec[0].toDouble();
        minpoint[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        maxpoint[0] = auxVec[0].toDouble();
        maxpoint[1] = auxVec[1].toDouble();
    }
    if (json.contains("point") && json["point"].isArray()) {
        QJsonArray auxVec = json["point"].toArray();
        point[0] = auxVec[0].toDouble();
        point[1] = auxVec[1].toDouble();
        point[2] = auxVec[2].toDouble();
    }
    if (json.contains("normal") && json["normal"].isArray()) {
        QJsonArray auxVec = json["normal"].toArray();
        normal[0] = auxVec[0].toDouble();
        normal[1] = auxVec[1].toDouble();
        normal[2] = auxVec[2].toDouble();
    }*/

}


void Plane::setMaterial(shared_ptr<Material> m){
    this->material = m;
}
