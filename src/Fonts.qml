import QtQuick
Item{
    id: fonts
    property font body_1: Qt.font({
        family: "Open Sans",
        weight: Font.DemiBold,
        pixelSize: 50,
        lineHeight: 60,
        letterSpacing: 0.5
    })

    property font body_2: Qt.font({
        family: "Open Sans",
        weight: Font.DemiBold,
        pixelSize: 20,
        lineHeight:  30,
        letterSpacing: 0.5
    })

    property font button: Qt.font({
        family: "Open Sans",
        weight: Font.DemiBold,
        pixelSize: 24,
        lineHeight:  30,
        letterSpacing: 1 
    })
}
