#include "Utils/JsonFileAnalysis.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

JsonFileAnalysis::JsonFileAnalysis(QString filePath, QObject *parent)
    :   QObject{parent},
        m_filePath{filePath}
{
    analyze();
}

void JsonFileAnalysis::analyze()
{
    QFile file(m_filePath);
    if(file.open(QIODevice::ReadOnly)) {
        m_fileData = file.readAll();
        file.close();
    }
    else
        qWarning() << QString("[JsonFileAnalysis::analyze()]： 文件%1无法打开！%2").arg(filePath(), file.errorString());
}

QJsonArray JsonFileAnalysis::toJsonArray()
{
    QJsonArray arr;
    QJsonParseError err;
    auto jsonDoc = QJsonDocument::fromJson(m_fileData, &err);
    if(err.error == QJsonParseError::NoError)
        arr = jsonDoc.array();
    else
        qWarning() << QString("[JsonFileAnalysis::toJsonArray()]: 文件%1不是Json格式！%2").arg(filePath(), err.errorString());
    return arr;
}

QJsonObject JsonFileAnalysis::toJsonObjcet()
{
    QJsonObject obj;
    QJsonParseError err;
    auto jsonDoc = QJsonDocument::fromJson(m_fileData, &err);
    if(err.error == QJsonParseError::NoError)
        obj = jsonDoc.object();
    else
        qWarning() << QString("[JsonFileAnalysis::toJsonObjcet()]: 文件%1不是Json格式！%2").arg(filePath(), err.errorString());
    return obj;

}
