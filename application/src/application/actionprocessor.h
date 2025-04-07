#include <chrono>
#include <QString>
#include <QImage>

#include <QDebug> // TODO : retirer

#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

#include "./executeactioncommand.h"
#include "../learning/classifier.h"
#include "../learning/imageadapter.h"

class ActionProcessor {
private:
    uint8_t actionType;
    QImage image;
    picture_vector pixelValues;
    picture_vector1D pixelRow;

public:
    explicit ActionProcessor(const uint8_t actionType);
    void process(const QString &imagePath);
};

#endif // ACTIONPROCESSOR_H
