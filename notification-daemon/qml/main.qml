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
        for (var i = 0; i < notificationModel.count; i++) {
            if (notificationModel.get(i) == display) {
                return i
            }
        }
        return -1
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
                var index = getIndex(display)
                if (index == -1) {
                    console.error("index is -1; aborting")
                    return
                }
                notificationModel.remove(index)
                display.destroy()
                notificationManager.qmlCloseNotification(notification)
            })
        }
    }

    ObjectModel { id: notificationModel }
}
