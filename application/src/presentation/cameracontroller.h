#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include "../application/actionprocessor.h"

class CameraController: public QObject {
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = nullptr, uint8_t actionType = ServiceIdentifyAction::VOLUME);
    ~CameraController();
private:
    ActionProcessor *actionProcessor = nullptr; // TODO : à supprimer ?
signals:

public slots:
    void takePicture(const QString &imagePath);
};

#endif // CAMERACONTROLLER_H
