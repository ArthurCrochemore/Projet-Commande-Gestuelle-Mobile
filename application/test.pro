# QMAKE_CC = "C:/Program Files/squishcoco/coveragescanner_x64.exe"
# QMAKE_CXX = "C:/Program Files/squishcoco/coveragescanner_x64.exe"
# QMAKE_LINK = "C:/Program Files/squishcoco/coveragescanner_x64.exe"
# QMAKE_LINK_SHLIB = "C:/Program Files/squishcoco/coveragescanner_x64.exe"

# QMAKE_CXXFLAGS += --cs-on --cs-args="--cs-make=g++ --cs-c++ --cs-c++11"
# QMAKE_CFLAGS += --cs-on --cs-args="--cs-make=g++ --cs-c++ --cs-c++11"


CONFIG += c++17 \
          testcase \
          no_testcase_installs \
          moc \
          coverage

QT += quick \
      qml \
      core \
      testlib \
      gui \
      multimedia \
      multimediawidgets

MOC_DIR = moc

# QMAKE_CXX = coveragescanner_x64.exe

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../learning/cnn_backward.cpp \
    ../learning/cnn_forward.cpp \
    ../learning/cnn_model.cpp \
    src/application/actionprocessor.cpp \
    src/application/executeactioncommand.cpp \
    src/application/photoprocessor.cpp \
    src/application/serviceidentify.cpp \
    src/learning/classifier.cpp \
    src/learning/imageadapter.cpp \
    src/learning/preprocessingdecorator.cpp \
    src/model/databasemanager.cpp \
    src/presentation/cameracontroller.cpp \
    src/presentation/mainwindow.cpp \
    test/test.cpp \
    test/integration/tst_actionprocessor.cpp \
    test/end_to_end/tst_cameracontroller.cpp \
    test/unit/tst_classifier.cpp \
    test/unit/tst_executeactioncommand.cpp \
    test/unit/tst_imageadapter.cpp \
    test/unit/tst_photoprocessor.cpp \
    test/unit/tst_preprocessingdecorator.cpp \
    test/unit/tst_serviceidentify.cpp

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
    ../learning/cnn_backward.h \
    ../learning/cnn_forward.h \
    ../learning/cnn_model.h \
    ../learning/cnn_structures.h \
    src/application/actionprocessor.h \
    src/application/executeactioncommand.h \
    src/application/photoprocessor.h \
    src/application/serviceidentify.h \
    src/learning/classifier.h \
    src/learning/imageadapter.h \
    src/learning/preprocessingdecorator.h \
    src/presentation/cameracontroller.h \
    test/integration/tst_actionprocessor.h \
    test/end_to_end/tst_cameracontroller.h \
    test/unit/tst_classifier.h \
    test/unit/tst_executeactioncommand.h \
    test/unit/tst_imageadapter.h \
    test/unit/tst_photoprocessor.h \
    test/unit/tst_preprocessingdecorator.h \
    test/unit/tst_serviceidentify.h
