#include <QTest>
#include <QDebug>
#include "../../src/learning/imageadapter.h"

class TestImageAdapter: public QObject {
    Q_OBJECT

private:
    QImage image;

private slots:
    void initTestCase();
    void vectorizeTest();
};

