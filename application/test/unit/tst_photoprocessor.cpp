#include "tst_photoprocessor.h"

void TestPhotoProcessor::processTest() {
    PhotoProcessor processor;
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    auto result = processor.process(imagePath);
    
    QVERIFY(!result.empty());

    QCOMPARE(result[0].size(), WIDTH);
    QCOMPARE(result.size(), HEIGHT);
}

