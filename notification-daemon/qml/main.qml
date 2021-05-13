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

    function getIndex(display) {
        for (const index in notificationModel) {
            if (notificationModel[index] == display) {
                return index
            }
        }
    }

    NotificationManager {
        id: notificationManager

        onNewNotification: {
            var component = Qt.createComponent("NotificationDisplay.qml")
            var display = component.createObject(
                root,
                {
                    notification
                }
            )
            
            notificationModel.append(display)
            
            display.position.x = notificationManager.availableWidth - display.width - Meui.Units.largeSpacing - 2
            display.position.y = notificationManager.availableHeight - (display.height + Meui.Units.largeSpacing) * notificationModel.count
            display.adjustCorrectLocation()

            display.closed.connect(() => {
                notificationManager.qmlCloseNotification(notification)
                notificationModel.remove(getIndex(display))
                display.destroy()
            })
        }
    }

    ObjectModel { id: notificationModel }
}
