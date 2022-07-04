#include <QString>
#include <QDir>

#include <Windows.h>
#include <Knownfolders.h>
#include <Shlobj.h>

namespace Environment {

static QString DirName = "JokerProgmmer";
static QString AppInfoDirName = "Racing Telemetry Tool";

static QString getKnownFolderPath(REFKNOWNFOLDERID dir)
{
    PWSTR pszPath = 0;
    HRESULT result = SHGetKnownFolderPath(dir, 0, NULL, &pszPath);
    QString path;
    if (result == S_OK)
    {
        path = QString::fromWCharArray(pszPath);
    }
    else {
        qCritical("%s", qUtf8Printable(QString("获取文档目录失败")));
    }
    CoTaskMemFree(pszPath);
    return path;
}

QString documentsPath() { return getKnownFolderPath(FOLDERID_Documents); }

QString localAppDataPath() { return getKnownFolderPath(FOLDERID_LocalAppData); }

QString applicationInfoPath()
{
    QDir dir(QString("%1/%2/%3").arg(documentsPath().arg(DirName).arg(AppInfoDirName)));
    if(!dir.exists())
        dir.mkpath(dir.path());
    return dir.path();
}


} // namespace Environment
