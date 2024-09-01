import QtQuick
import QtQuick.Controls
import org.calc.backend 1.0

Button {
    Themes{id:themes}
    Fonts{id:fonts}
    id: control
    implicitWidth: 60
    implicitHeight: 60
    onClicked: Backend.pushSimple(control.text)

    contentItem: Text{
        text: control.text
        font: fonts.button 
        color: down ? "white" : themes.theme_1_1 
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    background: Rectangle {
        radius: 100
        width: 60
        height: 60
        color: down ? themes.theme_1_3 : themes.theme_1_4
    }
}

