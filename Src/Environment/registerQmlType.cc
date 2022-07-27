#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include "Environment/DefineQmlRegisterType.h"
#include "Game/GameManager.h"
#include "Game/GameWithUdp.h"
#include "Data/TelemetryDataTableModel.h"

namespace Environment {

void registerQmlType(QQmlApplicationEngine &engine)
{

#define REG_MODULE_NAME
#define REG_NAMESPACE
    REG_SINGLETON(GameManager);
    REG_UNCREATABLE(Game);
    REG_UNCREATABLE(GameWithUdp);
    REG_CREATABLE(TelemetryDataTableModel);
#undef REG_NAMESPACE

}


} // namespace Environment
