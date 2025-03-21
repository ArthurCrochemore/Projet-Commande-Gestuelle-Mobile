#include <vector>

class IPreprocessingDecorator {
    public:
    virtual void process(std::vector<double>& data) = 0;
    virtual ~IPreprocessingDecorator() = default;
};

class NormalizationPreprocessor : public IPreprocessingDecorator {
    public:
        void process(std::vector<double>& data) override {
            // Implémentation de la normalisation
        }
    };
    