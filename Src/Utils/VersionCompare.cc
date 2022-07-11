#include <QString>
#include <QRegularExpression>
#include <QDebug>

namespace Utils {



int versionCompare(const QString &lhs, const QString &rhs)
{
    QRegularExpression rx {
        R"(^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)(?:-((?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\.(?:0|[1-9]\d*|\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\+([0-9a-zA-Z-]+(?:\.[0-9a-zA-Z-]+)*))?$)"
    };
    auto lhsMatch = rx.match(lhs);
    auto rhsMatch = rx.match(rhs);
    if (!lhsMatch.hasMatch() && !rhsMatch.hasMatch()) {
        qCritical() << QString("无法比较版本lhs(%1)和rhs(%2)").arg(lhs).arg(rhs);
        return 0;
    }
    else if(!lhsMatch.hasMatch() && rhsMatch.hasMatch()) {
        qWarning()<<QString("lhs版本(%1)不正确").arg(lhs);
        return -1;
    }
    else if(lhsMatch.hasMatch() && !rhsMatch.hasMatch()) {
        qWarning()<<QString("rhs版本(%1)不正确").arg(rhs);
        return 1;
    }
    else {
        for (auto i = 1; i < 4; i++) {
            auto cmp = lhsMatch.captured(i).toULongLong() <=> rhsMatch.captured(i).toULongLong();
            if (cmp != 0)  {
                qDebug()<<QString("lhs(%1) %2 rhs(%3) ").arg(lhs).arg((cmp < 0) ? "<" : ">").arg(rhs);
                return cmp < 0 ? -1 : 1;
            }
        }
        return 0;
    }
}



}//Utils
