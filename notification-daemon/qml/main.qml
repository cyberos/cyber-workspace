import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12
import QtQml.Models 2.12
import MeuiKit 1.0 as Meui
import org.cyber.NotificationDaemon 1.0

Item {
    id: root
    visible: false

    NotificationManager {
        id: notificationManager

        onNewNotification: {
            var component = Qt.createComponent("NotificationDisplay.qml")
            var display = component.createObject(
                root,
                {
                    x: Screen.width,
                    y: Screen.height,
                    notification
                }
            )
            notificationModel.append(display)
        }
    }

    ObjectModel { id: notificationModel }
}
