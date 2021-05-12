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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <qqml.h>
#include <QFile>
#include "desktopproperties.h"

// FIXME: Use QStandardPaths::ApplicationsLocation.
#define ApplicationsDir "/usr/share/applications"

class Notification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString summary READ getSummary NOTIFY summaryChanged)
    Q_PROPERTY(QString body READ getBody NOTIFY bodyChanged)
    Q_PROPERTY(QString appTitle READ getAppTitle NOTIFY appTitleChanged)
    Q_PROPERTY(QString iconPath READ getIconPath NOTIFY iconPathChanged)
    QML_ELEMENT

public:
    explicit Notification(QObject* parent = nullptr);

    QString getSummary();
    QString getBody();
    QString getAppTitle();
    QString getDesktopFile();
    QString getIconPath();

    // These are meant to be called only by DBus hooks in notificationmanager.cpp,
    // don't use them in other places!
    void setSummary(QString summary);
    void setBody(QString body);
    void setAppTitle(QString appTitle);
    void setDesktopFile(QString desktopFile);
    void setIconPath(QString iconPath);

private:
    QString m_summary;
    QString m_body;
    QString m_appTitle;
    QString m_desktopFile;
    QString m_iconPath;

signals:
    void summaryChanged();
    void bodyChanged();
    void appTitleChanged();
    void iconPathChanged();
};

#endif // NOTIFICATION_H
