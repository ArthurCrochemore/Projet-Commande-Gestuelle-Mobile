#ifndef EXECUTE_ACTION_COMMAND_H
#define EXECUTE_ACTION_COMMAND_H

#include "../learning/classifier.h"
#include "../learning/classifier.h"

class ExecuteActionCommandVolume {
    public:
    static constexpr void execute(const uint8_t predicted);
};

class ExecuteActionCommandBrightness {
    public:
    static constexpr void execute(const uint8_t predicted);
};

class ExecuteActionCommand {
    public:
    static void execute(const uint8_t predicted, const uint8_t actionType);
};

#endif // EXECUTE_ACTION_COMMAND_H
