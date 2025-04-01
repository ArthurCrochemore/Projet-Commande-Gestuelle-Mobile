#include <vector>
#include <chrono>
#include <QString>

#include <QDebug> // TODO : retirer

#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

#include "./executeactioncommand.h"
#include "./photoprocessor.h"
#include "./serviceidentify.h"
#include "../learning/imageadapter.h"

class ActionProcessor {
private:
    PhotoProcessor photoprocessor;
    IServiceIdentifyAction* serviceIdentification;
    IExecuteActionCommand* action;

public:
    ActionProcessor(uint8_t actionType);

    void process(const QString &imagePath);
};

#endif // ACTIONPROCESSOR_H
