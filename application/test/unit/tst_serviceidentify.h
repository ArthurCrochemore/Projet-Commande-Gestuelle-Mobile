#include <QTest>
#include <QDebug>
#include "../../src/application/serviceidentify.h"
#include "../../src/learning/classifier.h"
#include "../../src/learning/imageadapter.h"

class TestServiceIdentify: public QObject {
    Q_OBJECT
private:
    picture_vector features; // Initialize with test data
private slots:
    void initTestCase();
    void identifyActionVolumeTest();
    void identifyActionBrightnessTest();
    void identifyActionFactoryTest();
};

