#include "tst_executeactioncommand.h"

void TestExecuteActionCommand::executeActionCommandVolumeUpTest() {
    // TODO : Implémenter le test pour l'augmentation du volume
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandVolumeDownTest() {
    // TODO : Implémenter le test pour la diminution du volume
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandVolumeNothingTest() {
    // TODO : Implémenter le test pour l'inaction
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandVolumeErrorTest() {
    ExecuteActionCommandVolume* executeActionCommand = new ExecuteActionCommandVolume();
    QVERIFY_EXCEPTION_THROWN(executeActionCommand->execute(3), std::invalid_argument);
}

void TestExecuteActionCommand::executeActionCommandBrightnessUpTest() {
    // TODO : Implémenter le test pour l'augmentation de la luminosité
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandBrightnessDownTest() {
    // TODO : Implémenter le test pour la diminution de la luminosité
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandBrightnessNothingTest() {
    // TODO : Implémenter le test pour l'inaction de la luminosité
    QVERIFY(true); // Remplacer par la logique de test réelle
}
void TestExecuteActionCommand::executeActionCommandBrightnessErrorTest() {
    ExecuteActionCommandBrightness* executeActionCommand = new ExecuteActionCommandBrightness();
    QVERIFY_EXCEPTION_THROWN(executeActionCommand->execute(3), std::invalid_argument);
}



