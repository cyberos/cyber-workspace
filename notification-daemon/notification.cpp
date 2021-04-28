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

#include "notification.h"

Notification::Notification(QObject *parent)
    : QObject(parent)
{

}

QString Notification::getSummary()
{
    return m_summary;
}

QString Notification::getBody()
{
    return m_body;
}

QString Notification::getAppTitle()
{
    return m_appTitle;
}

QString Notification::getDesktopFile()
{
    return m_desktopFile;
}

QString Notification::getIconPath()
{
    if (m_iconPath.isEmpty() && !m_desktopFile.isEmpty()) {
        QString desktopFilePath = QString(ApplicationsDir) + QString("/") + m_desktopFile + ".desktop"; // FIXME: could this be done better?
        QFile file;
        file.setFileName(desktopFilePath);
        if (file.exists()) {
            DesktopProperties properties = DesktopProperties(desktopFilePath, "Desktop Entry");
            return QString("image://icontheme/") + properties.value("Icon", QVariant("application-x-desktop")).toString();
        }
    }
    if (m_iconPath.isEmpty()) {
        return QString("image://icontheme/application-x-desktop");
    }
    return QString("file://") + m_iconPath;
}

void Notification::setSummary(QString summary)
{
    m_summary = summary;
    emit summaryChanged();
}

void Notification::setBody(QString body)
{
    m_body = body;
    emit bodyChanged();
}

void Notification::setAppTitle(QString appTitle)
{
    m_appTitle = appTitle;
    emit appTitleChanged();
}

void Notification::setDesktopFile(QString desktopFile)
{
    m_desktopFile = desktopFile;
}

void Notification::setIconPath(QString iconPath)
{
    m_iconPath = iconPath;
    emit iconPathChanged();
}
