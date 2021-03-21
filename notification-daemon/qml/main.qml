import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml.Models 2.12
import MeuiKit 1.0 as Meui
import org.cyber.NotificationDaemon 1.0

Meui.Window {
    width: 500
    height: 500
    visible: true

    NotificationManager {
        id: notificationManager

        function notifToString(notification) {
            return `${notification.appTitle} | ${notification.summary}: ${notification.body}`
        }

        onNewNotification: {
            notificationModel.append(notification)
            for (let i = 0; i < notificationModel.count; i++) {
                console.log(notifToString(notificationModel.get(i)))
            }
        }
    }

    ObjectModel { id: notificationModel }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Meui.Units.largeSpacing

        Label {
            text: "Notification testing"
        }

        ListView {
            id: notificationListView
            model: notificationModel.count
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: ListView.Vertical
            clip: true

            delegate: Item {
                width: notificationListView.width
                height: _layout.implicitHeight

                ColumnLayout {
                    id: _layout
                    anchors.fill: parent

                    Label {
                        id: _notifAppIconLabel
                        text: "App icon:"
                    }

                    Image {
                        id: _notifAppIcon
                        source: notificationModel.get(index).iconPath
                        width: 128
                        height: 128
                        sourceSize: Qt.size(128, 128)
                    }

                    Label {
                        id: _notifAppName
                        text: "App title: " + notificationModel.get(index).appTitle
                    }

                    Label {
                        id: _notifSummary
                        text: "Summary: " + notificationModel.get(index).summary
                    }

                    Label {
                        id: _notifBody
                        text: "Body: " + notificationModel.get(index).body
                    }

                    Item {
                        height: Meui.Units.largeSpacing
                    }
                }
            }
        }
    }
}
