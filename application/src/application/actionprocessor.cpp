#include <./photoprocessor.cpp>
#include <./serviceidentify.cpp>
#include <../presentation/cameracontroller.cpp>

class ActionProcessor {
private:
    PhotoProcessor capturer;
    IServiceIdentifyAction* action;

public:
    ActionProcessor(IServiceIdentifyAction* action) : action(action) {}

    void process() {
        // TODO : Implémentation de la logique de traitement de l'action
    }
};
