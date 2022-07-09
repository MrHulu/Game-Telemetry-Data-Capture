#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace Environment {
//extern void registerQmlType(QQmlApplicationEngine &engine);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //Environment::registerQmlType(engine);

    const QUrl url(QStringLiteral("qrc:/Gui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
