import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import org.cyber.NotificationDaemon 1.0
import MeuiKit 1.0 as Meui
import QtGraphicalEffects 1.15

NotificationBase {
	id: control
	width: 500
	height: _layout.implicitHeight + Meui.Units.largeSpacing * 4
	visible: true

	property point position: Qt.point(Screen.width, Screen.height)
	required property Notification notification

	onWidthChanged: adjustCorrectLocation()
    onHeightChanged: adjustCorrectLocation()
    onPositionChanged: adjustCorrectLocation()
	Component.onCompleted: adjustCorrectLocation()
	
	color: "transparent"

	function adjustCorrectLocation() {
		var posX = control.position.x
		var posY = control.position.y

		// left
		if (posX < 0)
			posX = Meui.Units.largeSpacing
		
		// top
		if (posY < 0)
			posY = Meui.Units.largeSpacing
		
		// right
        if (posX + control.width > Screen.width)
            posX = Screen.width - control.width - Meui.Units.largeSpacing - 2

        // bottom
        if (posY + control.height > Screen.height)
            posY = Screen.height - control.height - Meui.Units.largeSpacing

        control.x = posX
        control.y = posY
	}

	Meui.RoundedRect {
		id: _background
		anchors.fill: parent
		radius: Meui.Theme.bigRadius
		color: Meui.Theme.backgroundColor
		opacity: 0.5
	}

	Meui.WindowShadow {
		view: control
		geometry: Qt.rect(control.x, control.y, control.width, control.height)
		radius: _background.radius
	}

	ColumnLayout {
		anchors.margins: Meui.Units.largeSpacing * 2
		anchors.fill: parent
		spacing: Meui.Units.largeSpacing
		id: _layout

		RowLayout {
			Layout.fillWidth: true

			Image {
				id: _notifAppIcon
				source: notification.iconPath
				width: 64
				height: 64
				sourceSize: Qt.size(64, 64)
			}

			ColumnLayout {
				Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

				Label {
					text: notification.appTitle
				}

				Label {
					text: notification.summary
					font.pointSize: 12
				}
			}
		}

		Label {
			text: notification.body
		}
	}
}
