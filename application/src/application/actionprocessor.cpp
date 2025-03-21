#include "./actionprocessor.h"

ActionProcessor::ActionProcessor(IServiceIdentifyAction* action) : action(action) {}

void ActionProcessor::process(const QString &imagePath) {
    std::vector<double> image = photoprocessor.process(imagePath);

    // if (action->identify(image)) {
    //     executeAction();
    // }

    // TODO : Implémenter correctement
}
