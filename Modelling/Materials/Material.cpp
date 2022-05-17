#include "Modelling/Materials/Material.h"
/*Desarrollado por Endimbeer Enrique Nuñez Matos */

Material::Material() {
     Ka = vec3(1, 0,0);
     Ks = vec3(0, 0, 0);
     Kd = vec3(0, 0, 0);
     shininess = 10.0;
     opacity = 0;
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
    struct gl_material mt;

    mt.kd = program->uniformLocation("material.Kd");
    mt.ks = program->uniformLocation("material.Ka");
    mt.ka = program->uniformLocation("material.Ks");
    mt.shine = program->uniformLocation("material.shininess");
    mt.opac = program->uniformLocation("material.opacity");


    glUniform3fv(mt.kd, 1, Kd);
    glUniform3fv(mt.ka, 1, Kd);
    glUniform3fv(mt.ks, 1, Ks);
    glUniform1f(mt.shine, shininess);
    glUniform1f(mt.opac, opacity);

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

