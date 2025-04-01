#include "./photoprocessor.h"

/**
 * Fonction responsable du traitement de l'image
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : image vectorisée
 */
std::vector<std::vector<greyscale_value>> PhotoProcessor::process(const QString &imagePath) {
    QImage image = QImage(imagePath);

    return QImageToVectorAdapter().vectorize(image);
}
