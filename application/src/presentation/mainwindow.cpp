#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cameracontroller.h"
#include <QQmlContext>

class MainWindow {
    public:
        static int run(int argc, char *argv[])
        {
            QGuiApplication app(argc, argv);
            
            QQmlApplicationEngine engine;

            CameraController objCameraController;
            engine.rootContext()->setContextProperty("cameraController", &objCameraController);

            engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

            return app.exec();
        }
};
