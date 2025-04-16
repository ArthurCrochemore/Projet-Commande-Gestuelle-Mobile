#include "tst_serviceidentify.h"

void TestServiceIdentify::initTestCase() {
    picture_vector features = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    this->features = features; // Initialize with test data
}

void TestServiceIdentify::identifyActionVolumeTest() {
    ServiceIdentifyActionVolume action;
    uint8_t result = action.identify(features);
    QCOMPARE(result, VolumeClassifier::UP); // Replace with expected value
}

void TestServiceIdentify::identifyActionBrightnessTest() {
    ServiceIdentifyActionBrightness action;
    uint8_t result = action.identify(features);
    QCOMPARE(result, BrightnessClassifier::UP); // Replace with expected value
}

void TestServiceIdentify::identifyActionFactoryTest() {
    auto& provider = IdentifyActionProvider::instance();

    auto action = provider.createIdentifyAction(IServiceIdentifyAction::VOLUME);
    QVERIFY(action != nullptr);
    QVERIFY(dynamic_cast<ServiceIdentifyActionVolume*>(action.get()) != nullptr); // Check if the action is of the correct type

    action = provider.createIdentifyAction(IServiceIdentifyAction::BRIGHTNESS);
    QVERIFY(action != nullptr);
    QVERIFY(dynamic_cast<ServiceIdentifyActionBrightness*>(action.get()) != nullptr); // Check if the action is of the correct type
}
