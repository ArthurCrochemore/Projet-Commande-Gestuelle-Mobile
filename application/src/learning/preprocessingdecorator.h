#include <vector>

#ifndef PREPROCESSINGDECORATOR_H
#define PREPROCESSINGDECORATOR_H

class IPreprocessingDecorator {
    public:
    virtual void process(std::vector<double>& data) = 0;
    virtual ~IPreprocessingDecorator() = default;
};

class NormalizationPreprocessor : public IPreprocessingDecorator {
public:
    void process(std::vector<double>& data) override;
};
    
#endif // PREPROCESSINGDECORATOR_H