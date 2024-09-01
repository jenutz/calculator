import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow{
    id: root
    width: 360 
    height: 640 
    visible:true
    Loader {
        id: loader
       source: "MainWindow.qml"
    }
}
