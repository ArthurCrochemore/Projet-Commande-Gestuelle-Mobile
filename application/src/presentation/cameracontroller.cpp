#include "cameracontroller.h"

CameraController::CameraController(QObject *parent): QObject(parent) {

}

void CameraController::takePicture(const QString &imagePath) {
    // Code to take a picture
    qDebug() << "Image sauvegardée à:" << imagePath;

    auto actionType = IdentifyActionFactory::VOLUME; // TODO : choix depuis l'UI

    ActionProcessor actionProcessor(actionType);
    actionProcessor.process(imagePath);
}
