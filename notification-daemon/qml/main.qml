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
            // FIXME: some notifications don't appear on screen at all and they can't be closed,
            //        they will probably eat up memory if we can't fix this

            var component = Qt.createComponent("NotificationDisplay.qml")
            var display = component.createObject(
                root,
                {
                    notification
                }
            )
            // FIXME: will break on multi-monitor setups!
            
            notificationModel.append(display)
        }
    }

    ObjectModel { id: notificationModel }
}
