#include <QTest>
#include "../../src/application/actionprocessor.h"

class TestActionProcessor: public QObject {
    Q_OBJECT

private slots:
    void processCorrectTest();
    void processWrongPathTest();
    void processWrongActionTest();
};
