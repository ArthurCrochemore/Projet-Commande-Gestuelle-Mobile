#include "tst_cameracontroller.h"
#include <QSignalSpy>
#include <QTemporaryFile>

void TestCameraController::processValidTest() {
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    uint8_t actionType = IdentifyActionFactory::VOLUME;

    CameraController cameraController;

    QSignalSpy errorSpy(&cameraController, &CameraController::errorOccurred);

    cameraController.takePicture(imagePath);
    
    QVERIFY(errorSpy.isEmpty());
}

void TestCameraController::processInvalidImageTest() {
    QString invalidPath = "fake_path.jpg"; // volontairement invalide
    uint8_t actionType = IdentifyActionFactory::VOLUME;
    ActionProcessor actionProcessor(actionType);

    CameraController cameraController;

    QSignalSpy errorSpy(&cameraController, &CameraController::errorOccurred);

    cameraController.takePicture(invalidPath);

    QVERIFY(!errorSpy.isEmpty());
}





