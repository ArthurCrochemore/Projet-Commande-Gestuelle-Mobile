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

    auto pre = std::chrono::high_resolution_clock::now();

    picture_vector image = photoprocessor.process(imagePath);

    auto predicted = serviceIdentification->identify(image);

    action->execute(predicted);

    auto post = std::chrono::high_resolution_clock::now();
    qDebug() << "Action réalisée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";

}
