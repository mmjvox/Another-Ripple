#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../AnotherRipple/SimpleRipple.h"
#include "../AnotherRipple/ShapedRipple.h"
#include "../AnotherRipple/IconRipple.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<SimpleRipple>("AnotherRipple", 1, 0, "SimpleRipple");
    qmlRegisterType<ShapedRipple>("AnotherRipple", 1, 0, "ShapedRipple");
    qmlRegisterType<IconRipple>("AnotherRipple", 1, 0, "IconRipple");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
