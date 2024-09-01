#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>

#include "Calculator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Calculator *backend = new Calculator; 
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<Calculator>("org.calc.backend", 1, 0, "Backend",
            [&](QQmlEngine *, QJSEngine *) -> QObject * {
            return backend;
            });

    const QUrl url(QStringLiteral("qrc:/Main.qml"));

    QObject::connect(
            &engine, 
            &QQmlApplicationEngine::objectCreated,
            &app, 
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
                    }, 
            Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}

