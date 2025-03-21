#include "cameracontroller.h"

CameraController::CameraController(QObject *parent): QObject(parent) {

}

void CameraController::takePicture(const QString &imagePath) {
    // Code to take a picture
    qDebug() << "Image sauvegardée à:" << imagePath;

    ActionProcessor actionProcessor(IdentifyActionFactory::createAction(IdentifyActionFactory::VOLUME));
    actionProcessor.process(imagePath);
}
