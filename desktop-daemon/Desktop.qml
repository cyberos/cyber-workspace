import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import org.cyber.Desktop 1.0
import MeuiKit 1.0 as Meui

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
        sourceSize: Qt.size(width, height)
        fillMode: Image.PreserveAspectCrop
        clip: true
        cache: false

        ColorOverlay {
            id: dimsWallpaper
            anchors.fill: wallpaper
            source: wallpaper
            color: "#000000"
            opacity: 0.4
            visible: Meui.Theme.darkMode && settings.dimsWallpaper
        }
    }
}
