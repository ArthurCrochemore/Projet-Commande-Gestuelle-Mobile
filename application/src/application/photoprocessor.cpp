#include "../learning/imageadapter.cpp"

/*
 * Classe de traitement de photo
 */
class PhotoProcessor {
    public:
    std::vector<double> process(QImage imagePath) {
        return QImageToVectorAdapter::vectorize(imagePath);
    }
};