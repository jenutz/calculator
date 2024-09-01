import QtQuick
import QtQuick.Controls

Button {
    Themes{id:themes}
    implicitWidth: 60
    implicitHeight: 60
    icon.width: 60 
    icon.height: 60 
    background: Rectangle {
        radius: 100
        width: 60
        height: 60
        color: down ? themes.theme_1_add_2 : themes.theme_1_2
    }
}

