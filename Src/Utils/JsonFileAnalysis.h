#pragma once

#include <QObject>

class QJsonObject;
class QJsonArray;

class JsonFileAnalysis : public QObject
{
public:
    JsonFileAnalysis(QString filePath, QObject* parent = nullptr);

    void analyze();
    QString filePath() const;
    QByteArray toByteArray();
    QJsonArray toJsonArray();
    QJsonObject toJsonObjcet();

private:
    QString     m_filePath;
    QByteArray  m_fileData;
};

inline QString JsonFileAnalysis::filePath() const { return m_filePath; }

inline QByteArray JsonFileAnalysis::toByteArray() { return m_fileData; }

