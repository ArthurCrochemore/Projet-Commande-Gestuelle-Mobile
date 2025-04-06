#ifndef EXECUTE_ACTION_COMMAND_H
#define EXECUTE_ACTION_COMMAND_H

#include "./serviceidentify.h"
#include "../learning/classifier.h"

class ExecuteActionCommandVolume {
    public:
    static void execute(uint8_t predicted);
};

class ExecuteActionCommandBrightness {
    public:
    static void execute(uint8_t predicted);
};

class ExecuteActionCommand {
    public:
    static void execute(uint8_t predicted, uint8_t actionType);
};

#endif // EXECUTE_ACTION_COMMAND_H
