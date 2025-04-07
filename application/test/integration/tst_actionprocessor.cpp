#include "tst_actionprocessor.h"
#include <QSignalSpy>
#include <QTemporaryFile>

void TestActionProcessor::processTest() {
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    uint8_t actionType = IdentifyActionFactory::VOLUME;
    ActionProcessor actionProcessor(actionType);

    actionProcessor.process(imagePath);

    // TODO : assert qqch
}




