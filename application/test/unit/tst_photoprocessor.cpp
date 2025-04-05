#include "tst_photoprocessor.h"

void TestPhotoProcessor::processTest() {
    PhotoProcessor processor;
    QString imagePath = "../../../learning/database/volume/up0_volume.jpg"; // Replace with a valid image path
    auto result = processor.process(imagePath);
    
    // Check if the result is not empty
    QVERIFY(!result.empty());

    // Check if the first row has the expected number of columns (assuming a fixed size for the test)
    QCOMPARE(result[0].size(), WIDTH); // Replace 10 with the expected number of columns
    QCOMPARE(result.size(), HEIGHT); // Replace 10 with the expected number of columns
}

