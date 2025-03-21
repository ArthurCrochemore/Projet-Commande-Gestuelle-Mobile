QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/application/actionfactory.cpp \
        src/application/actions.cpp \
        src/application/actionvolume.cpp \
        src/application/command.cpp \
        src/application/maincontroller.cpp \
        src/application/photoprocessor.cpp \
        src/ia/classifier.cpp \
        src/ia/imagevectorizeradaptater.cpp \
        src/ia/predictionobserver.cpp \
        src/ia/preprocessingdecorator.cpp \
        src/ia/vectorizationstrategy.cpp \
        src/model/databasemanager.cpp \
        src/model/modelmanager.cpp \
        src/model/modeltrainer.cpp \
        src/presentation/cameracontroller.cpp \
        src/presentation/mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    main.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

FORMS +=
