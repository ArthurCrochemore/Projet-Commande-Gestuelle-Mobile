#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QDebug>
#include "../application/actionprocessor.h"

class CameraController: public QObject {
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = nullptr);

signals:

public slots:
    static void takePicture(const QString &imagePath);
};

#endif // CAMERACONTROLLER_H
