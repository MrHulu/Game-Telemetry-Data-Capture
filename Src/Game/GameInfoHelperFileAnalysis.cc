#include "Game/GameInfoHelperFileAnalysis.h"
#include "Utils/JsonFileAnalysis.h"
#include "Game/Game.h"
#include "Game/GameWithUdp.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

namespace Environment {
    extern QString applicationInfoPath();
}// Envirnment

GameInfoHelper::GameInfoFileReadAndWrite::GameInfoFileReadAndWrite(const QString filePath, GameInfoHelper& helper)
    :   QObject{&helper},
        gameInfoHelper{helper},
        m_jsonAnalysis{new JsonFileAnalysis(filePath, this)}
{
    m_fileJsonObjcet = m_jsonAnalysis->toJsonObjcet();
    m_fileVersion = m_fileJsonObjcet.value("version").toString();
    m_fileChangeTime = QDateTime::fromString(m_fileJsonObjcet.value("changeTime").toString(), "yyyy-MM-dd hh:mm:ss");
}

void GameInfoHelper::GameInfoFileReadAndWrite::updateGameInfo()
{
    auto& games = gameInfoHelper.m_games;
    for(auto iter = games.begin(); iter != games.end(); iter++) {
        auto game = iter.value();
        auto obj = getGameInfoObjcet(game->name());

        auto installPath = obj.contains("installPath") ? obj.value("installPath").toString("") : "";
        game->setInstallPath(installPath);

        auto processNames = getProcessNamesFromJsonArray(obj);
        if(!processNames.isEmpty()) game->setProcessNames(processNames);

        if(game->captureMethod() == Game::NetWorkUDP || game->captureMethod() == Game::UDPAndSM) {
            if(obj.contains("UDP")) {
                auto udpObj = obj.value("UDP").toObject();
                auto gameWithUdp = static_cast<GameWithUdp*>(game);

                auto port = udpObj.contains("port") ? udpObj.value("port").toInt(0) : 0;
                if(port != 0) gameWithUdp->setReadPort(port);
                auto ipAddress = udpObj.contains("ipAddress") ? udpObj.value("ipAddress").toString("") : "";
                if(!ipAddress.isEmpty()) gameWithUdp->setReadAddress(ipAddress);

                auto sendPort = udpObj.contains("sendPort") ? udpObj.value("sendPort").toInt(0) : 0;
                if(sendPort != 0) gameWithUdp->setWritePort(sendPort);
                auto sendIpAddress = udpObj.contains("sendIpAddress") ? udpObj.value("sendIpAddress").toString("") : "";
                if(!sendIpAddress.isEmpty()) gameWithUdp->setWriteAddress(sendIpAddress);
            }
        }
    }
}

void GameInfoHelper::GameInfoFileReadAndWrite::readGameInfoFile()
{
    m_jsonAnalysis->analyze();
    m_fileJsonObjcet = m_jsonAnalysis->toJsonObjcet();
}

void GameInfoHelper::GameInfoFileReadAndWrite::creatGameInfoFile()
{
    write(m_jsonAnalysis->toByteArray());
}

void GameInfoHelper::GameInfoFileReadAndWrite::writeGameInstallPathInfo(const QString &gameName, const QString &gameInstallPath)
{
    //m_fileJsonObjcet.contains()
    if(m_fileJsonObjcet.contains(gameName)) {
        auto obj = m_fileJsonObjcet[gameName].toObject();
        obj["installPath"] = gameInstallPath;
        m_fileJsonObjcet[gameName] = obj;
        write(QJsonDocument::fromVariant(m_fileJsonObjcet.toVariantMap()).toJson());
    }
}

QString GameInfoHelper::GameInfoFileReadAndWrite::getGameInfoFilePath()
{
    return m_jsonAnalysis->filePath();
}

QJsonObject GameInfoHelper::GameInfoFileReadAndWrite::getGameInfoObjcet(const QString &gameName)
{
    if(m_fileJsonObjcet.contains(gameName))
      return m_fileJsonObjcet.value(gameName).toObject();
    return QJsonObject();
}

QSet<QString> GameInfoHelper::GameInfoFileReadAndWrite::getProcessNamesFromJsonArray(QJsonObject obj)
{
    QSet<QString> set;
    if(obj.contains("processName")) {
        auto arr = obj.value("processName").toArray();
        auto list = arr.toVariantList();
        for(auto i = 0; i<list.size(); i++) {
            auto name = list.at(i).toString();
            set.insert(name);
        }
    }
    return set;
}

void GameInfoHelper::GameInfoFileReadAndWrite::write(QByteArray fileData)
{
    auto path = QString("%1/%2").arg(Environment::applicationInfoPath(), gameInfoHelper.GameInfoJsonFileName);

    //qDebug().noquote().nospace() << "write: "<<QString::fromUtf8(fileData);
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(fileData);
        file.close();
    }
    readGameInfoFile();
}
