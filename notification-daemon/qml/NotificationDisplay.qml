import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import org.cyber.NotificationDaemon 1.0
import MeuiKit 1.0 as Meui
import QtGraphicalEffects 1.15

NotificationBase {
	id: root
	width: 500
	height: _layout.implicitHeight + Meui.Units.largeSpacing * 4
	visible: true

	property point position: Qt.point(Screen.width, Screen.height)
	required property Notification notification

	onWidthChanged: adjustCorrectLocation()
	onHeightChanged: adjustCorrectLocation()
	onPositionChanged: adjustCorrectLocation()
	Component.onCompleted: adjustCorrectLocation()

	signal closed()
	
	color: "transparent"

	function adjustCorrectLocation() {
		var posX = root.position.x
		var posY = root.position.y

		// left
		if (posX < 0)
			posX = Meui.Units.largeSpacing
		
		// top
		if (posY < 0)
			posY = Meui.Units.largeSpacing
		
		// right
		if (posX + root.width > Screen.width)
			posX = Screen.width - root.width - Meui.Units.largeSpacing - 2

		// bottom
		if (posY + root.height > Screen.height)
			posY = Screen.height - root.height - Meui.Units.largeSpacing

		root.x = posX
		root.y = posY
	}

	Meui.RoundedRect {
		id: _background
		anchors.fill: parent
		radius: Meui.Theme.bigRadius
		color: Meui.Theme.backgroundColor
		opacity: 0.5
	}

	Meui.WindowShadow {
		view: root
		geometry: Qt.rect(root.x, root.y, root.width, root.height)
		radius: _background.radius
	}

	ColumnLayout {
		anchors.margins: Meui.Units.largeSpacing * 2
		anchors.fill: parent
		spacing: Meui.Units.largeSpacing
		id: _layout

		RowLayout {
			Layout.fillWidth: true
			height: 64

			Image {
				id: _notifAppIcon
				source: notification.iconPath
				width: 64
				height: 64
				sourceSize: Qt.size(64, 64)
			}

			ColumnLayout {
				Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
				Layout.fillWidth: true

				Label {
					Layout.fillWidth: true
					text: notification.appTitle
					elide: Text.ElideRight
					clip: true
				}

				Label {
					Layout.fillWidth: true
					text: notification.summary
					elide: Text.ElideRight
					font.pointSize: 12
					clip: true
				}
			}

			Item {
				Layout.fillWidth: true
			}

			Button {
				text: "Close"
				onClicked: {
					root.closed()
					root.visible = false
				}
			}
		}

		Label {
			Layout.fillWidth: true

			text: notification.body
			elide: Text.ElideRight
			clip: true
		}
	}
}
