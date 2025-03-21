QT += quick \
      qml \
      core \
      gui \
      multimedia \
      multimediawidgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/application/actionprocessor.cpp \
        src/application/executeactioncommand.cpp \
        src/application/photoprocessor.cpp \
        src/application/serviceidentify.cpp \
        src/learning/classifier.cpp \
        src/learning/imageadapter.cpp \
        src/learning/preprocessingdecorator.cpp \
        src/model/databasemanager.cpp \
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
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

FORMS +=

HEADERS += \
    src/application/actionprocessor.h \
    src/application/executeactioncommand.h \
    src/application/photoprocessor.h \
    src/application/serviceidentify.h \
    src/learning/classifier.h \
    src/learning/imageadapter.h \
    src/learning/preprocessingdecorator.h \
    src/presentation/cameracontroller.h
