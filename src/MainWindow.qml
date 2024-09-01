import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import org.calc.backend 1.0

Rectangle{
    Fonts{id : fonts}
    Themes{id : themes}

    id: mainWindow
    width: 360
    height: 640
    color: themes.theme_1_1
    property bool secret : false
    property string secretContext : ""

    Image {
        source: "qrc:///icons/30/statusbar.svg"
    }

    // back_calculation
    Rectangle{
        width: 360
        height: 156 
        y: 24
        color: themes.theme_1_3
        bottomLeftRadius: 30
        bottomRightRadius: 30
    }

    // calculation_line
    Text{
        width: 280
        height: 30
        y: 68
        x: 39
        text: Backend.calculation
        font: fonts.body_2
        color: "#FFFFFF"
        padding:0
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
    }

    // result
    Text{
        id: res
        width: 281
        height: 60
        x: 39
        y: 106
        text: Backend.result
        font: fonts.body_1
        color: "#FFFFFF"
        padding:0
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
    }

    // button_action
    GridLayout{
        columns: 1
        width: 312
        height: 396
        y: 204
        x: 24

        RowLayout{
            spacing: 24
            ActionButton {
                icon.source: "qrc://icons/30/bkt.svg"
                onClicked: Backend.brackets()
            }
            ActionButton {
                icon.source: "qrc://icons/30/plus_minus.svg"
                onClicked: Backend.plusMinus()
            }
            ActionButton {
                icon.source: "qrc://icons/30/percent.svg"
                onClicked: Backend.percent()
            }
            ActionButton {
                icon.source: "qrc://icons/30/division.svg"
                onClicked: Backend.division()
            }
        }
        RowLayout{
            spacing: 24
            SimpleButton {text: "7"}
            SimpleButton {text: "8"}
            SimpleButton {text: "9"}
            ActionButton {
                icon.source: "qrc://icons/30/multiplication.svg"
                onClicked: Backend.multiplication()
            }
        }
        RowLayout{
            spacing: 24
            SimpleButton {text: "4"}
            SimpleButton {text: "5"}
            SimpleButton {text: "6"}
            ActionButton {
                icon.source: "qrc://icons/30/minus.svg"
                onClicked: Backend.minus()
            }
        }
        RowLayout{
            spacing: 24
            SimpleButton {text: "1"}
            SimpleButton {text: "2"}
            SimpleButton {
                text: "3"
                onClicked: {
                    if (secret){
                        var val = Backend.calculation
                        val.replace(secretContext, "")
                        if (val.endsWith("123")){
                            loader.source = "SecretWindow.qml"
                        }
                    }
                }
            }
            ActionButton {
                icon.source: "qrc://icons/30/plus.svg"
                onClicked: Backend.plus()
            }

        }
        RowLayout{
            spacing: 24
            Button {
                text: "C"
                id: cancel_bt
                onClicked: Backend.cancel()
                implicitWidth: 60
                implicitHeight: 60
                contentItem: Text{
                    text: cancel_bt.text
                    font: fonts.button 
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                background: Rectangle {
                    radius: 100
                    width: 60
                    height: 60
                    color: cancel_bt.down ? themes.theme_1_5_30 : themes.theme_1_5
                }
            }

            SimpleButton {text: "0"}
            SimpleButton {
                text: "."
            }
            ActionButton {
                id: equalBt
                icon.source: "qrc://icons/30/equal.svg"
                property string context: ""

                onClicked: Backend.equal()

                onPressedChanged: {
                    if (pressed) {
                        timer.running = true;
                    } else {
                        timer.running = false;
                    }
                }
                Timer {
                    id: timer
                    interval: 4000 //ms 
                    repeat: false
                    running: false

                    onTriggered: 
                    {
                        secret = true
                        secretContext = Backend.calculation
                        timer2.start();
                    }
                }
                Timer {
                    id: timer2
                    interval: 5000 //ms 
                    repeat: false
                    running: false

                    onTriggered: 
                    {
                        secret = false
                    }
                }
            }
        }
    }
}



