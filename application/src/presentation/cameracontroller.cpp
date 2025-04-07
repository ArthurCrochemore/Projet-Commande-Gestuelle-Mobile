#include "cameracontroller.h"

CameraController::CameraController(QObject *parent,
                                    const uint8_t actionType // TODO : choix depuis l'UI
                                   ): QObject(parent) {
    actionProcessor = new ActionProcessor(actionType);
}

CameraController::~CameraController() {
    delete actionProcessor;
}

/**
 * Fonction responsable de la prise de photo et de l'ammorcement du traitement de l'image
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : void
 */
void CameraController::takePicture(const QString &imagePath) {
    // Code to take a picture
    this->actionProcessor->process(imagePath);
}
