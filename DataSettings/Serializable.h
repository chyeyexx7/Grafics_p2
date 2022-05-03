#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

class Serializable
{
public:

    enum SaveFormat {
        Json, Binary
    };

    virtual void read (const QJsonObject &json) = 0;
    virtual void write (QJsonObject &json) const = 0;
    virtual void print (int indentation) const = 0;
};

#endif // SERIALIZABLE_H
