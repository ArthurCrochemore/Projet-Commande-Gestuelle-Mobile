#include "./actionprocessor.h"

ActionProcessor::ActionProcessor(uint8_t actionType) {
    auto& provider = IdentifyActionProvider::instance();

    try {
        serviceIdentification = provider.createIdentifyAction(actionType);
        action = std::unique_ptr<IExecuteActionCommand>(ExecuteActionCommandFactory::createAction(actionType)); // Conversion explicite en std::unique_ptr
    } catch (const std::invalid_argument &e) {
        qDebug() << "Erreur : " << e.what();
        throw e;
    }
}

/**
 * Fonction principale faisant le lien entre le traitement de l'image et l'exécution de l'action
 * 
 * @param imagePath : chemin de l'image à traiter
 * @return : int
 */
int ActionProcessor::process(const QString &imagePath) {
    try {
        auto pre = std::chrono::high_resolution_clock::now();

        picture_vector image = photoprocessor.process(imagePath);

        auto predicted = serviceIdentification->identify(image);

        action->execute(predicted);

        auto post = std::chrono::high_resolution_clock::now();
        qDebug() << "Action réalisée en " << QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count()) << " ms";
        return 0; // Success
    } catch (const std::runtime_error &e) {
        qDebug() << "Erreur : " << e.what();
        throw e;
        return 1; // Failure
    } catch (const std::exception &e) {
        qDebug() << "Erreur inattendue : " << e.what();
        throw e;
        return 1; // Failure
    }
}
