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

    Image {
        id: wallpaper
        anchors.fill: parent
        source: "file://" + settings.wallpaper
        fillMode: Image.PreserveAspectCrop
        clip: true
    }
}
