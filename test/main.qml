import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12

import AnotherRipple 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: "My Ripple"

    SimpleRipple{
        anchors.fill: parent;
        color: "#d4ff47"
    }



    Button {
        id: button
        width: 100
        height: 60
        anchors.centerIn: parent;
        text: "Button"
        anchors.verticalCenterOffset: -151
        anchors.horizontalCenterOffset: 0

        background: Rectangle{
            color: "#ebebeb"
        }

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
        IconRipple {
            color: "#50ffa070"
            anchors.fill: parent
            acceptEvent: true
            clipRadius: parent.radius
        }
        clip: true
    }


}
