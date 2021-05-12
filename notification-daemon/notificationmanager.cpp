/*
 * Copyright (C) 2021 CyberOS Team.
 *
 * Author:     omame <me@omame.tech>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "notificationmanager.h"
#include "notificationadaptor.h"

NotificationManager::NotificationManager(QObject* parent)
    : QObject(parent),
    m_lastID(0)
{
    new NotificationAdaptor(this);

    // connect to D-Bus and register as an object
    QDBusConnection::sessionBus().registerService(QStringLiteral("org.freedesktop.Notifications"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/org/freedesktop/Notifications"), this);
}

void NotificationManager::CloseNotification(uint id) {
    emit NotificationClosed(id, 3);
}

QStringList NotificationManager::GetCapabilities() {
    return QStringList("body");
}

QString NotificationManager::GetServerInformation(QString &vendor, QString &version, QString &spec_version) {
    vendor = QString("CyberOS");
    version = QString("rolling");
    spec_version = QString("1.2");
    return QString("Cyber Notification Daemon");
}

uint NotificationManager::Notify(
    const QString &app_name,
    uint replaces_id,
    const QString &app_icon,
    const QString &summary,
    const QString &body,
    const QStringList &actions,
    const QVariantMap &hints,
    int expire_timeout
) {
    int returnID = m_lastID;
    m_lastID++;

    Notification* notification = new Notification(nullptr);
    notification->setAppTitle(app_name);
    notification->setSummary(summary);
    notification->setBody(body);

    for (auto key : hints.keys()) {
        if (key == QString("desktop-entry")) {
            notification->setDesktopFile(hints.value(key).toString());
        }
    }

    emit newNotification(notification);

    return returnID;
}
