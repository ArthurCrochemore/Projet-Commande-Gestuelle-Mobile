#include "serviceidentify.h"
#include <QImage>

#ifndef EXECUTEACTIONCOMMAND_H
#define EXECUTEACTIONCOMMAND_H

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
    ExecuteActionCommand(IServiceIdentifyAction* action, QImage img);
    void execute() override;
};

#endif // EXECUTEACTIONCOMMAND_H
