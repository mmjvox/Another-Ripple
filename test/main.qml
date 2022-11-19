import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12

import AnotherRipple 1.0

Window {
    width: 840
    height: 480
    visible: true
    title: "My Ripple"

//    SimpleRipple{
//        anchors.fill: parent;
//        color: "#d4ff47"
//    }

    SimpleRipple {
        color: "#50ffa070"
        anchors.fill: parent
    }


    Button {
        x: 270
        y: 60
        width: 96
        height: 60
        text: "Button"

        background: Rectangle{
            color: "#ebebeb"
        }

        SimpleRipple{
            anchors.fill: parent;
            color: "#7988eb"
        }
    }


    Rectangle {
        x: 374
        y: 60
        width: 96
        height: 60
        color: "#ebebeb"


        SimpleRipple{
            anchors.fill: parent;
            color: "#7988eb"
        }
    }




    DropShadow {
        anchors.fill: itemRect
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 17
        color: "#50000000"
        source: itemRect
    }

    Rectangle{
        id:itemRect
        x: 51
        y: 159
        width: 200;
        height: 80;
        radius: 50;
        clip: true;

        SimpleRipple{
            anchors.fill: parent;
//            color: "#ffa070"
            color: "#50ffa070"
            acceptEvent: true
            xClipRadius:parent.radius-10;
            yClipRadius:parent.radius;
        }
    }

    DropShadow {
        anchors.fill: itemRect2
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 17
        color: "#50000000"
        source: itemRect2
    }

    Rectangle{
        id:itemRect2
        x: 51
        y: 59
        width: 200;
        height: 80;
        radius: 5;
        clip: true;

        SimpleRipple{
            anchors.fill: parent;
            color: "#50ffa070"
            acceptEvent: true;
            clipRadius:parent.radius;
        }
    }

    DropShadow {
        anchors.fill: itemRect3
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 17
        color: "#50000000"
        source: itemRect3
    }

    Rectangle {
        id: itemRect3
        x: 51
        y: 265
        width: 200
        height: 80
        radius: 5
        ShapedRipple {
            color: "#50ffa070"
            anchors.fill: parent
            acceptEvent: true
            clipRadius: parent.radius
        }
        clip: true
    }

    DropShadow {
        anchors.fill: itemRect4
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 17
        color: "#50000000"
        source: itemRect4
    }

    Rectangle {
        id: itemRect4
        x: 51
        y: 365
        width: 200
        height: 80
        radius: 5

        Text {
            text: qsTr("text")
            anchors.centerIn: parent;
        }

        IconRipple {
            color: "#d4ff47"//"#50ffa070"
            anchors.fill: parent
            acceptEvent: true
            clipRadius: parent.radius
            imageSource: "/home/mmjvox/Documents/start.png";
        }
        clip: true
    }

    DropShadow {
        anchors.fill: itemRect5
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 17
        color: "#50000000"
        source: itemRect5
    }
    Rectangle {
        id: itemRect5
        x: 270
        y: 159
        width: 200
        height: 80
        radius: 5

        Text {
            text: qsTr("text")
            anchors.centerIn: parent;
        }

        ImageRipple {
            color: "#d4ff47"//"#50ffa070"
            anchors.fill: parent
            acceptEvent: true
            clipRadius: parent.radius
            imageSource: "/home/mmjvox/Documents/2.jpg";
        }
        clip: true
    }

    Rectangle {
        x: 270
        y: 259
        width: 200
        height: 80
        radius: 5
        border.width: 1

        IconRipple {
            color: "#50ffa070"
            anchors.fill: parent
            clipRadius: parent.radius
            acceptEvent: true;
            imageSource: "/home/mmjvox/Documents/start.png";
            bounce: IconRipple.ClockWise;
        }
    }

    Rectangle {
        x: 270
        y: 359
        width: 200
        height: 80
        radius: 5
        border.width: 1

        IconRipple {
            color: "#50ffa070"
            anchors.fill: parent
            clipRadius: parent.radius
            acceptEvent: true;
            imageSource: "/home/mmjvox/Documents/start.png";
            bounce: IconRipple.Counter_ClockWise;
        }
    }


}
