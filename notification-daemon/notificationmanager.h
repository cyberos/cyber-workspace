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

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <qqml.h>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QDBusConnection>
#include "notification.h"

class NotificationManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit NotificationManager(QObject* parent = nullptr);

public slots:
    void CloseNotification(uint id);
    QStringList GetCapabilities();
    QString GetServerInformation(QString &vendor, QString &version, QString &spec_version);
    uint Notify(
        const QString &app_name,
        uint replaces_id,
        const QString &app_icon,
        const QString &summary,
        const QString &body,
        const QStringList &actions,
        const QVariantMap &hints,
        int expire_timeout
    );

signals:
    // DBus signals
    void NotificationClosed(uint id, uint reason);
    void ActionInvoked(uint id, const QString& action_key);

    // QML signals
    void newNotification(Notification* notification);

private:
    uint m_lastID;
};

#endif // NOTIFICATIONMANAGER_H
