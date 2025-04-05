#include "./photoprocessor.h"

/**
 * Fonction responsable du traitement de l'image
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : image vectorisée
 */
picture_vector PhotoProcessor::process(const QString &imagePath) {
    QImage image = QImage(imagePath);

    return QImageToVectorAdapter().vectorize(image);
}
