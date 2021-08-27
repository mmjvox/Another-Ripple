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
        x: 226
        y: 298
        width: 200;
        height: 80;
        radius: 5;
        clip: true;

        SimpleRipple{
            anchors.fill: parent;
            color: "#50ffa070"
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
        x: 226
        y: 98
        width: 200;
        height: 80;
        radius: 5;
        clip: true;

        SimpleRipple{
            anchors.fill: parent;
            color: "#50ffa070"
            acceptEvent: true;
        }
    }


}
