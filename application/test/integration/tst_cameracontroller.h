#include <QTest>
#include "../../src/presentation/cameracontroller.h"

class TestCameraController: public QObject {
    Q_OBJECT

private slots:
    void processValidTest();
    void processInvalidImageTest();
};

