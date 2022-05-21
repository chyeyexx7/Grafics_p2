#include "Modelling/Materials/Material.h"
/*Desarrollado por Endimbeer Enrique Nuñez Matos */

Material::Material() {
     this->Ka = vec3(0.2,0.2,0.2);
     this->Ks = vec3(1.,1.,1.);
     this->Kd = vec3(0.8,0.5,0.5);
     this->shininess = 20.0;
     this->opacity = 0;
}

Material::~Material(){

}

Material::Material(vec3 a, vec3 d, vec3 s, float shin) {
    //Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    shininess = shin;
}

Material::Material(vec3 a, vec3 d, vec3 s, float shin, float opac) {
    //Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    shininess = shin;
    opacity = opac;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){

    struct {
        GLuint kd;
        GLuint ks;
        GLuint ka;
        GLuint shine;
        GLuint opac;
    }gl_material;

    gl_material.kd = program->uniformLocation("material.Kd");
    gl_material.ks = program->uniformLocation("material.Ka");
    gl_material.ka = program->uniformLocation("material.Ks");
    gl_material.shine = program->uniformLocation("material.shininess");
    gl_material.opac = program->uniformLocation("material.opacity");

    glUniform3fv(gl_material.kd, 1, Kd);
    glUniform3fv(gl_material.ks, 1, Ka);
    glUniform3fv(gl_material.ka, 1, Ks);
    glUniform1f(gl_material.shine, shininess);
    glUniform1f(gl_material.opac, opacity);

}



void Material::read (const QJsonObject &json)
{
    if (json.contains("ka") && json["ka"].isArray()) {
        QJsonArray auxVec = json["ka"].toArray();
        Ka[0] = auxVec[0].toDouble();
        Ka[1] = auxVec[1].toDouble();
        Ka[2] = auxVec[2].toDouble();
    }
    if (json.contains("kd") && json["kd"].isArray()) {
        QJsonArray auxVec = json["kd"].toArray();
        Kd[0] = auxVec[0].toDouble();
        Kd[1] = auxVec[1].toDouble();
        Kd[2] = auxVec[2].toDouble();
    }
    if (json.contains("ks") && json["ks"].isArray()) {
        QJsonArray auxVec = json["ks"].toArray();
        Ks[0] = auxVec[0].toDouble();
        Ks[1] = auxVec[1].toDouble();
        Ks[2] = auxVec[2].toDouble();
    }
    if (json.contains("shininess") && json["shininess"].isDouble())
        shininess = json["shininess"].toDouble();
    if (json.contains("opacity") && json["opacity"].isDouble())
        opacity = json["opacity"].toDouble();

}


//! [1]
void Material::write(QJsonObject &json) const
{
    QJsonArray auxArray;
    auxArray.append(Ka[0]);auxArray.append(Ka[1]);auxArray.append(Ka[2]);
    json["ka"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(Kd[0]);auxArray2.append(Kd[1]);auxArray2.append(Kd[2]);
    json["kd"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(Ks[0]);auxArray3.append(Ks[1]);auxArray3.append(Ks[2]);
    json["ks"] = auxArray3;
    json["opacity"] = opacity;
    json["shininess"] = shininess;
}

//! [1]

void Material::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Ka:\t" << Ka[0] << ", "<< Ka[1] << ", "<< Ka[2] << "\n";
    QTextStream(stdout) << indent << "Kd:\t" << Kd[0] << ", "<< Kd[1] << ", "<< Kd[2] << "\n";
    QTextStream(stdout) << indent << "Ks:\t" << Ks[0] << ", "<< Ks[1] << ", "<< Ks[2] << "\n";
    QTextStream(stdout) << indent << "shininess:\t" << shininess<< "\n";
    QTextStream(stdout) << indent << "opacity:\t" << opacity<< "\n";
}



