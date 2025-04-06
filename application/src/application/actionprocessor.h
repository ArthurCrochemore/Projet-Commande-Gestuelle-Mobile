#include <chrono>
#include <QString>
#include <QImage>

#include <QDebug> // TODO : retirer

#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

#include "./executeactioncommand.h"
#include "./serviceidentify.h"
#include "../learning/imageadapter.h"

class ActionProcessor {
private:
    uint8_t actionType;
    QImage image;
    picture_vector pixelValues;

public:
    ActionProcessor(uint8_t actionType);
    void process(const QString &imagePath);
};

#endif // ACTIONPROCESSOR_H
