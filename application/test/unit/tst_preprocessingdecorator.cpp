#include "tst_preprocessingdecorator.h"

void TestPreprocessingDecorator::initTestCase() {
    picture_vector data = {
        {0, 100, 255}, {255, 100, 0}
    };
    this->data = data;
}

void TestPreprocessingDecorator::processTest() {
    picture_vector dataCpy = this->data;
    NormalizationPreprocessor().process(dataCpy);
    for (int i = 0; i < data.size(); ++i) {
        QCOMPARE(dataCpy[i].at(0), this->data[i].at(0)/255.0f);
        QCOMPARE(dataCpy[i].at(1), this->data[i].at(1)/255.0f);
        QCOMPARE(dataCpy[i].at(2), this->data[i].at(2)/255.0f);
    }
}



