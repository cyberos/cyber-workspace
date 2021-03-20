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
    if (m_summary == nullptr) return QString("");
    return *m_summary;
}

QString Notification::getBody()
{
    if (m_body == nullptr) return QString("");
    return *m_body;
}

QString Notification::getAppTitle()
{
    if (m_appTitle == nullptr) return QString("");
    return *m_appTitle;
}

QString Notification::getDesktopFile()
{
    if (m_desktopFile == nullptr) return QString("");
    return *m_desktopFile;
}

QString Notification::getIconPath()
{
    // TODO: if (m_iconPath == nullptr && m_desktopFile != nullptr),
    //       determine icon path by desktop file
    if (m_iconPath == nullptr && m_desktopFile != nullptr) {
        return QString("Placeholder");
    }
    if (m_iconPath == nullptr) return QString("");
    return *m_iconPath;
}

void Notification::setSummary(QString summary)
{
    m_summary = &summary;
    emit summaryChanged();
}

void Notification::setBody(QString body)
{
    m_body = &body;
    emit bodyChanged();
}

void Notification::setAppTitle(QString appTitle)
{
    m_appTitle = &appTitle;
    emit appTitleChanged();
}

void Notification::setDesktopFile(QString desktopFile)
{
    m_desktopFile = &desktopFile;
}

void Notification::setIconPath(QString iconPath)
{
    m_iconPath = &iconPath;
    emit iconPathChanged();
}
