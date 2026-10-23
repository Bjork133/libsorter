#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "bridge/LibCoreBridge.hpp"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("LibSorter");
    app.setOrganizationName("libcore");

    // Регистрируем мост в QML
    qmlRegisterType<LibCoreBridge>("LibSorter", 1, 0, "LibCoreBridge");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/LibSorter/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject* obj, const QUrl& objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
