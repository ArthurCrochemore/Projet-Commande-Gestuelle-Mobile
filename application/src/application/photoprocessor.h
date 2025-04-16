#include <QFile>
#include <QImage>

#ifndef PHOTOPROCESSOR_H
#define PHOTOPROCESSOR_H

#include "../learning/imageadapter.h"

class PhotoProcessor {
public:
    picture_vector process(const QString &imagePath);
};

#endif // PHOTOPROCESSOR_H
