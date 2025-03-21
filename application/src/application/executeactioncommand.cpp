#include "./serviceidentify.cpp"

class ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

class ExecuteActionCommand : public ICommand {
private:
    IServiceIdentifyAction* action;
    QImage image;
public:
    ExecuteActionCommand(IServiceIdentifyAction* action, QImage img) : action(action), image(img) {}
    void execute() override {
        if (action->identify(image)) {
            // TODO : Implémentation de la logique liée au traitement de l'action
        }
    }
};