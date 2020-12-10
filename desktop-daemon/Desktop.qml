import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import org.cyber.Desktop 1.0

Item {
    visible: true
    id: root

    Settings {
        id: settings
    }

    // if the wallpaper file is not found
    // the background color is displayed
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#247FBC"
        visible: !wallpaper.visible
    }

    Image {
        id: wallpaper
        anchors.fill: parent
        source: "file://" + settings.wallpaper
        fillMode: Image.PreserveAspectCrop
        visible: status == Image.Ready
        clip: true
    }
}
