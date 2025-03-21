import QtQuick 2.3
import QtQuick.Window 2.2
import QtMultimedia 5.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Window {
    visible: true
    //width: Screen.width
    //height: Screen.height
    width: Screen.height/2
    height: Screen.width/2

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage
        //imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
        flash.mode: Camera.FlashOn

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposureNightPortrait
        }


        imageCapture {
            onImageCaptured: {
                //photoPreview.source = preview  // Show the preview in an Image

            }
            onImageSaved: {
                var urlPhoto

                urlPhoto=camera.imageCapture.capturedImagePath
                txtCamera.text=urlPhoto
                imagePhoto.source="file://"+urlPhoto
                imagePhoto.update()

                cameraController.takePicture(urlPhoto);
            }
        }
        //videoRecorder.resolution: "640x480"
        //viewfinder.resolution: "640x480"
    }

    VideoOutput {
        anchors.fill: parent
        source: camera
        focus : visible // to receive focus and capture key events when visible
        autoOrientation: true
        fillMode: Image.Stretch
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "lightsteelblue"
            Text {
                id: txtCamera
                anchors.fill: parent
            }
        }
        Button {
            id: btnPhoto
            text: "Photo"
            /*onClicked: {
                imagePhoto.source=""
                camera.imageCapture.captureToLocation("/tmp/xxx.jpg")
            }*/
            onClicked: camera.imageCapture.capture()
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Image {
            id: imagePhoto
            Layout.minimumWidth: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 300
            Layout.maximumHeight: 300
            cache: false
            fillMode: Image.PreserveAspectCrop
            //source: "file:///tmp/xxx.jpg"
        }
    }
    Component.onCompleted: txtCamera.text=QtMultimedia.defaultCamera.displayName
}
