#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include "parser.h"

using namespace QJson;

QByteArray readFile(const QString &filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        return QByteArray();
    }

    return file.readAll();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Parser parser;
    bool ok;
    QVariant result = parser.parse(readFile("../test-json/test1.json"), &ok);
    if(ok)
    {
        QMap<QString, QVariant> tmp = result.toMap();
        qDebug() << "name:\t" << tmp["name"].toString();
        qDebug() << "sex:\t" << tmp["sex"].toString();
    }
    qDebug() << "*********************************";

    result = parser.parse(readFile("../test-json/test2.json"), &ok);
    if(ok)
    {
        QMap<QString, QVariant> tmp = result.toMap();
        tmp = tmp["info"].toMap();
        qDebug() << "name:\t" << tmp["name"].toString();
        qDebug() << "sex:\t" << tmp["sex"].toString();
        qDebug() << "age:\t" << tmp["age"].toInt();
        qDebug() << "height:\t" << tmp["height"].toDouble();
    }
    qDebug() << "*********************************";

    result = parser.parse(readFile("../test-json/test3.json"), &ok);
    if(ok)
    {
        QMap<QString, QVariant> tmp = result.toMap();
        QList<QVariant> lst = tmp["class"].toList();
        foreach(QVariant var, lst)
        {
            tmp = var.toMap();
            qDebug() << "name:\t" << tmp["name"].toString();
            qDebug() << "sex:\t" << tmp["sex"].toString();
        }
    }
    qDebug() << "*********************************";

    result = parser.parse(readFile("../test-json/test4.json"), &ok);
    if(ok)
    {
        QMap<QString, QVariant> tmp = result.toMap();
        QList<QVariant> lst = tmp["class"].toList();
        foreach(QVariant var, lst)
        {
            QMap<QString, QVariant> tmp = var.toMap();
            qDebug() << "name:\t" << tmp["name"].toString();
            qDebug() << "sex:\t" << tmp["sex"].toString();
        }

        tmp = tmp["info"].toMap();
        qDebug() << "name:\t" << tmp["name"].toString();
        qDebug() << "sex:\t" << tmp["sex"].toString();
        qDebug() << "age:\t" << tmp["age"].toInt();
    }
    qDebug() << "*********************************";

    return a.exec();
}
