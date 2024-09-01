import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import org.calc.backend 1.0

Rectangle{
    Fonts{id : fonts}
    Themes{id : theme}
    id:sercet
    anchors.fill: parent
    color: theme.theme_1_1
    Button{
        text: "Назад"
        font: fonts.button
        Rectangle{
            color:theme.theme_1_5
            radius : 30
            anchors.fill: parent
        }
        onClicked: loader.source = "MainWindow.qml" 
    }

    Text {
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        text: "Секретное меню"
        font: fonts.body_1
        color: "white"
    }
}




