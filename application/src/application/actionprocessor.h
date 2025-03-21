#include <vector>
#include <QString>
#include "./photoprocessor.h"
#include "./serviceidentify.h"

#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

class ActionProcessor {
private:
    PhotoProcessor photoprocessor;
    IServiceIdentifyAction* action;

public:
    ActionProcessor(IServiceIdentifyAction* action);

    void process(const QString &imagePath);
};

#endif // ACTIONPROCESSOR_H
