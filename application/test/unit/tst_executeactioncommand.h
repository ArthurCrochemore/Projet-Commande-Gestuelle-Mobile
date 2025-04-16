#include <QTest>
#include "../../src/application/executeactioncommand.h"

class TestExecuteActionCommand: public QObject {
    Q_OBJECT

private slots:
    // Tests unitiaires pour les actions sur le volume
    void executeActionCommandVolumeUpTest();
    void executeActionCommandVolumeDownTest();
    void executeActionCommandVolumeNothingTest();
    void executeActionCommandVolumeErrorTest();

    // Tests unitiaires pour les actions sur la luminosité
    void executeActionCommandBrightnessUpTest();
    void executeActionCommandBrightnessDownTest();
    void executeActionCommandBrightnessNothingTest();
    void executeActionCommandBrightnessErrorTest();
};
