#include <QImage>
#include "../learning/imageadapter.h"

#ifndef PHOTOPROCESSOR_H
#define PHOTOPROCESSOR_H

class PhotoProcessor {
public:
    std::vector<double> process(const QString &imagePath);
};

#endif // PHOTOPROCESSOR_H