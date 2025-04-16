#include "tst_actionprocessor.h"
#include <QSignalSpy>
#include <QTemporaryFile>

void TestActionProcessor::processCorrectTest() {
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    uint8_t actionType = IServiceIdentifyAction::VOLUME;
    ActionProcessor actionProcessor(actionType);

    int r = actionProcessor.process(imagePath);

    QCOMPARE(r, 0);
}


void TestActionProcessor::processWrongPathTest() {
    QString invalidPath = "fake_path.jpg"; // volontairement invalide
    uint8_t actionType = IServiceIdentifyAction::VOLUME;
    ActionProcessor actionProcessor(actionType);

    QVERIFY_EXCEPTION_THROWN(actionProcessor.process(invalidPath), std::runtime_error);
}


void TestActionProcessor::processWrongActionTest() {
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    uint8_t actionType = 12; // volontairement invalide

    QVERIFY_EXCEPTION_THROWN(ActionProcessor actionProcessor(actionType), std::invalid_argument);
}


