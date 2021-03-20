#include "notification.h"

Notification::Notification(QObject *parent)
    : QObject(parent)
{

}

QString* Notification::getSummary()
{
    return m_summary;
}

QString* Notification::getBody()
{
    return m_body;
}

QString* Notification::getAppTitle()
{
    return m_appTitle;
}

QString* Notification::getDesktopFile()
{
    return m_desktopFile;
}

QString* Notification::getIconPath()
{
    return m_iconPath;
}

void Notification::setSummary(QString* summary)
{
    if (summary == m_summary) {
        return;
    }
    m_summary = summary;
    emit summaryChanged();
}

void Notification::setBody(QString* body)
{
    if (body == m_body) {
        return;
    }
    m_body = body;
    emit bodyChanged();
}

void Notification::setAppTitle(QString* appTitle)
{
    if (appTitle == m_appTitle) {
        return;
    }
    m_appTitle = appTitle;
    emit appTitleChanged();
}

void Notification::setDesktopFile(QString* desktopFile)
{
    if (desktopFile == m_desktopFile) {
        return;
    }
    m_desktopFile = desktopFile;
}

void Notification::setIconPath(QString* iconPath)
{
    if (iconPath == m_iconPath) {
        return;
    }
    m_iconPath = iconPath;
    emit iconPathChanged();
}
