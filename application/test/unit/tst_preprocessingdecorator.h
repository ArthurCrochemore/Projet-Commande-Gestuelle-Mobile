#include <QTest>
#include <QDebug>
#include "../../src/learning/preprocessingdecorator.h"

class TestPreprocessingDecorator: public QObject {
    Q_OBJECT
private:
    picture_vector data;

private slots:
    void initTestCase();
    void processTest();
};

