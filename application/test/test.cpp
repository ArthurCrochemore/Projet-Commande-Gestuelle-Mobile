#include <QTest>

#include "integration/tst_actionprocessor.h"
#include "end_to_end/tst_cameracontroller.h"
#include "unit/tst_classifier.h"
#include "unit/tst_executeactioncommand.h"
#include "unit/tst_imageadapter.h"
#include "unit/tst_photoprocessor.h"
#include "unit/tst_preprocessingdecorator.h"
#include "unit/tst_serviceidentify.h"

int main(int argc, char *argv[]) {
    int status = 0;

    status |= QTest::qExec(new TestActionProcessor, argc, argv);
    status |= QTest::qExec(new TestCameraController, argc, argv);
    status |= QTest::qExec(new TestClassifier, argc, argv);
    status |= QTest::qExec(new TestExecuteActionCommand, argc, argv);
    status |= QTest::qExec(new TestImageAdapter, argc, argv);
    status |= QTest::qExec(new TestPhotoProcessor, argc, argv);
    status |= QTest::qExec(new TestPreprocessingDecorator, argc, argv);
    status |= QTest::qExec(new TestServiceIdentify, argc, argv);

    return status;
}
