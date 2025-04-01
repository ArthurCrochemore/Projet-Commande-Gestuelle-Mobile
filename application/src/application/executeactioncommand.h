#include <QDebug> // TODO : Remove this include ?

#ifndef EXECUTE_ACTION_COMMAND_H
#define EXECUTE_ACTION_COMMAND_H

#include "./serviceidentify.h"
#include "../learning/classifier.h"

class IExecuteActionCommand {
    public:
    virtual ~IExecuteActionCommand() = default;
    virtual void execute(uint8_t predicted) const = 0;
};

class ExecuteActionCommandVolume : public IExecuteActionCommand {
    public:
    void execute(uint8_t predicted) const override;
};

class ExecuteActionCommandBrightness : public IExecuteActionCommand {
    public:
    void execute(uint8_t predicted) const override;
};

class ExecuteActionCommandFactory {
    public:
    static IExecuteActionCommand* createAction(uint8_t actionType);
};

#endif // EXECUTE_ACTION_COMMAND_H