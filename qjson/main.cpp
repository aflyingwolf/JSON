#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

/**
  qt5内置了对json解析的库
  QJsonDocument
  QJsonObject
  QJsonArray
  QJsonValue
  QJsonParseError
*/

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

    {
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(readFile("../test-json/test1.json"), &error);
        if(error.error == QJsonParseError::NoError && jsonDoc.isNull() == false)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject obj = jsonDoc.object();
                qDebug() << "name:\t" << obj.value("name").toString();
                qDebug() << "sex:\t" << obj.value("sex").toString();
            }
            qDebug() << "\n";
        }
    }

    {
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(readFile("../test-json/test2.json"), &error);
        if(error.error == QJsonParseError::NoError && jsonDoc.isNull() == false)
        {
            QJsonValue val = jsonDoc.object().value("info");
            if(val.isObject())
            {
                QJsonObject subObj = val.toObject();
                qDebug() << "name:\t" << subObj.value("name").toString();
                qDebug() << "sex:\t" << subObj.value("sex").toString();
                qDebug() << "age:\t" << subObj.value("age").toInt();
                qDebug() << "height:\t" << subObj.value("height").toDouble();
            }
            qDebug() << "\n";
        }
    }

    {
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(readFile("../test-json/test3.json"), &error);
        if(error.error == QJsonParseError::NoError && jsonDoc.isNull() == false)
        {
            QJsonValue val = jsonDoc.object().value("class");
            if(val.isArray())
            {
                QJsonArray ary = val.toArray();
                for(int i = 0, sz = ary.size(); i != sz; ++i)
                {
                    QJsonObject subObj = ary[i].toObject();
                    qDebug() << "name:\t" << subObj.value("name").toString();
                    qDebug() << "sex:\t" << subObj.value("sex").toString();
                }
            }
            qDebug() << "\n";
        }
    }

    {
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(readFile("../test-json/test4.json"), &error);
        if(error.error == QJsonParseError::NoError && jsonDoc.isNull() == false)
        {
            QJsonObject obj = jsonDoc.object();
            QJsonValue val = obj.value("info");
            if(val.isObject())
            {
                QJsonObject subObj = val.toObject();
                qDebug() << "name:\t" << subObj.value("name").toString();
                qDebug() << "sex:\t" << subObj.value("sex").toString();
                qDebug() << "age:\t" << subObj.value("age").toInt();
                qDebug() << "height:\t" << subObj.value("height").toDouble();
            }

            val = obj.value("class");
            if(val.isArray())
            {
                QJsonArray ary = val.toArray();
                for(int i = 0, sz = ary.size(); i != sz; ++i)
                {
                    QJsonObject subObj = ary[i].toObject();
                    qDebug() << "name:\t" << subObj.value("name").toString();
                    qDebug() << "sex:\t" << subObj.value("sex").toString();
                }
            }
            qDebug() << "\n";
        }
    }

    return a.exec();
}
