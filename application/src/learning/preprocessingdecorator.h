#include <algorithm>

#ifndef PREPROCESSINGDECORATOR_H
#define PREPROCESSINGDECORATOR_H

#include "imageadapter.h"

class IPreprocessingDecorator {
    public:
    virtual void process(picture_vector& data) = 0;
    virtual ~IPreprocessingDecorator() = default;
};

class NormalizationPreprocessor : public IPreprocessingDecorator {
public:
    void process(picture_vector& data) override;
};
    
#endif // PREPROCESSINGDECORATOR_H
