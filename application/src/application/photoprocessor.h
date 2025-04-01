#include <QImage>

#ifndef PHOTOPROCESSOR_H
#define PHOTOPROCESSOR_H

#include "../learning/imageadapter.h"

class PhotoProcessor {
public:
    std::vector<std::vector<greyscale_value>> process(const QString &imagePath);
};

#endif // PHOTOPROCESSOR_H
