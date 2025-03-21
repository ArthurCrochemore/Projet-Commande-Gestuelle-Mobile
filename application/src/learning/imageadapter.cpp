#include <vector>

class IImageAdapter {
    public:
    virtual std::vector<double> vectorize(QImage image) = 0;
};

class QImageToVectorAdapter : IImageAdapter {
    public:
    std::vector<double> vectorize(QImage image) override {
        // TODO: Implémentation de la vectorisation
    }
};