#include "tst_photoprocessor.h"

void TestPhotoProcessor::processValidTest() {
    PhotoProcessor processor;
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg";
    auto result = processor.process(imagePath);
    
    QVERIFY(!result.empty());

    QCOMPARE(result[0].size(), WIDTH);
    QCOMPARE(result.size(), HEIGHT);
}


void TestPhotoProcessor::processWrongPathTest() {
    PhotoProcessor processor;
    QString invalidPath = "fake_path.jpg"; // volontairement invalide

    QVERIFY_EXCEPTION_THROWN(processor.process(invalidPath), std::runtime_error);

}
