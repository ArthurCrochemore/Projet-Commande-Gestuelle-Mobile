#include <chrono>
#include <QString>
#include <memory>

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
    std::unique_ptr<IServiceIdentifyAction> serviceIdentification; // Utilisation d'un std::unique_ptr
    std::unique_ptr<IExecuteActionCommand> action;

public:
    ActionProcessor(uint8_t actionType);

    int process(const QString &imagePath);
};

#endif // ACTIONPROCESSOR_H
