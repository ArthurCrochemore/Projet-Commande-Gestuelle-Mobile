#include "./actionprocessor.h"

ActionProcessor::ActionProcessor(uint8_t actionType) {
    this->actionType = actionType;
    this->image = QImage(WIDTH, HEIGHT, QImage::Format_Grayscale8); // TODO : revoir si c'est utile
    this->pixelValues = picture_vector(HEIGHT, picture_vector1D(WIDTH));
}

/**
 * Fonction principale faisant le lien entre le traitement de l'image et l'exécution de l'action
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : void
 */
void ActionProcessor::process(const QString &imagePath) {
    auto pre = std::chrono::high_resolution_clock::now();

    QImageToVectorAdapter::vectorize(imagePath, this->image, this->pixelValues);

    uint8_t predicted = ServiceIdentifyAction::identify(this->pixelValues, this->actionType);

    ExecuteActionCommand::execute(predicted, this->actionType);

    auto post = std::chrono::high_resolution_clock::now();
    qDebug() << "Action réalisée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";

}
