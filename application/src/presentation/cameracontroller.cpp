#include "cameracontroller.h"

CameraController::CameraController(QObject *parent): QObject(parent) {}

/**
 * Fonction responsable de la prise de photo et de l'ammorcement du traitement de l'image
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : void
 */
void CameraController::takePicture(const QString &imagePath) {
    // Code to take a picture
    qDebug() << "Image sauvegardée à:" << imagePath;

    auto actionType = IdentifyActionFactory::VOLUME; // TODO : choix depuis l'UI

    ActionProcessor actionProcessor(actionType);

    try {
        actionProcessor.process(imagePath);
    } catch (const std::exception &e) {
        QString errorMsg = QString("Erreur lors du traitement de l'image : %1").arg(e.what());
        qDebug() << errorMsg;
        emit errorOccurred(errorMsg);
    }
}
