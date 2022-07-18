#pragma once


//注册QML类型的模板

#define REG_CREATABLE(ClassName) \
qmlRegisterType<REG_NAMESPACE::ClassName>("TelemetryDataCapture" REG_MODULE_NAME, 1, 0, #ClassName)

#define REG_UNCREATABLE(ClassName) \
    qmlRegisterUncreatableType<REG_NAMESPACE::ClassName>("TelemetryDataCapture" REG_MODULE_NAME, 1, 0, #ClassName, REG_MODULE_NAME"."#ClassName" cannot be created in QML.")

#define REG_SINGLETON(ClassName) \
    qmlRegisterSingletonType<REG_NAMESPACE::ClassName>("TelemetryDataCapture" REG_MODULE_NAME, 1, 0, #ClassName, [](QQmlEngine *engine, QJSEngine *) -> QObject* { \
            auto instance = &REG_NAMESPACE::ClassName::instance(); \
            engine->setObjectOwnership(instance, QQmlEngine::ObjectOwnership::CppOwnership); \
            return instance; \
    })

#define REG_SINGLETONPOINTER(ClassName) \
    qmlRegisterSingletonType<REG_NAMESPACE::ClassName>("TelemetryDataCapture" REG_MODULE_NAME, 1, 0, #ClassName, [](QQmlEngine *engine, QJSEngine *) -> QObject* { \
            auto instance = REG_NAMESPACE::ClassName::instance(); \
            engine->setObjectOwnership(instance, QQmlEngine::ObjectOwnership::CppOwnership); \
            return instance; \
    })

