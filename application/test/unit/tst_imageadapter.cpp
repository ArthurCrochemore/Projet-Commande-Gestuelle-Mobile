#include "tst_imageadapter.h"

void TestImageAdapter::initTestCase() {
    QImage image(WIDTH, HEIGHT, QImage::Format_Grayscale8);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            image.setPixel(x, y, qRgb(0, 0, 0)); // Set all pixels to black
        }
    }
    this->image = image;
}

void TestImageAdapter::vectorizeTest() {
    QImageToVectorAdapter adapter;
    picture_vector vectorizedImage = adapter.vectorize(image);

    // Check if the vectorized image has the correct dimensions
    QCOMPARE(vectorizedImage.size(), HEIGHT);
    for (const auto& row : vectorizedImage) {
        QCOMPARE(row.size(), WIDTH);
    }

    // Check if the pixel values are correctly set to 0 (black)TT
    for (const auto& row : vectorizedImage) {
        for (const auto& pixelValue : row) {
            QCOMPARE(pixelValue, 0.0f); // Assuming normalization results in 0.0 for black pixels
        }
    }
}



