﻿#pragma once

#include "Game/GameInfoHelper.h"

#include <QObject>
#include <QDateTime>
#include <QJsonObject>

class JsonFileAnalysis;

class GameInfoHelper::GameInfoFileReadAndWrite : public QObject
{
    Q_OBJECT
public:
    GameInfoFileReadAndWrite(const QString filePath, GameInfoHelper& helper);

    void updateGameInfo();
    void readGameInfoFile();
    void creatGameInfoFile();
    void writeGameInstallPathInfo(const QString& gameName, const QString& gameInstallPath);

    QString fileVersion() const;
    QDateTime fileChangeTime();

private:
    QString getGameInfoFilePath();
    QJsonObject getGameInfoObjcet(const QString& gameName);
    QSet<QString> getProcessNamesFromJsonArray(QJsonObject obj);
    void write(QByteArray fileData);

private:
    GameInfoHelper& gameInfoHelper;

    JsonFileAnalysis*   m_jsonAnalysis = nullptr;
    QString         m_fileVersion;
    QJsonObject     m_fileJsonObjcet;
    QDateTime       m_fileChangeTime;
};

inline QString GameInfoHelper::GameInfoFileReadAndWrite::fileVersion() const { return m_fileVersion; }

inline QDateTime GameInfoHelper::GameInfoFileReadAndWrite::fileChangeTime() { return m_fileChangeTime; }

