#include "./executeactioncommand.h"

ExecuteActionCommand::ExecuteActionCommand(IServiceIdentifyAction* action, QImage img) : action(action), image(img) {}

void ExecuteActionCommand::execute() {
    if (action->identify(image)) {
        // TODO : Implémentation de la logique liée au traitement de l'action
    }
}
