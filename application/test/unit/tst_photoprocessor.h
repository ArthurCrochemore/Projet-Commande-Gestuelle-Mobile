#include <QTest>
#include <QDebug>
#include "../../src/application/photoprocessor.h"

class TestPhotoProcessor: public QObject {
    Q_OBJECT

private:
    picture_vector data;

private slots:
    void processTest();
};

