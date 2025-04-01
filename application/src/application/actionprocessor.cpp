#include "./actionprocessor.h"

ActionProcessor::ActionProcessor(uint8_t actionType) {
    serviceIdentification = IdentifyActionFactory::createIdentifyAction(actionType);
    action = ExecuteActionCommandFactory::createAction(actionType);
}

/**
 * Fonction principale faisant le lien entre le traitement de l'image et l'exécution de l'action
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : void
 */
void ActionProcessor::process(const QString &imagePath) {

    qDebug() << "Start ActionProcessor";
    auto pre = std::chrono::high_resolution_clock::now();

    qDebug() << "Vectorisation process ...";
    std::vector<std::vector<greyscale_value>> image = photoprocessor.process(imagePath);

    qDebug() << "Prediction process ...";
    auto predicted = serviceIdentification->identify(image);

    qDebug() << "Action process ...";
    action->execute(predicted);

    auto post = std::chrono::high_resolution_clock::now();
    qDebug() << "Action réalisée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";

}
