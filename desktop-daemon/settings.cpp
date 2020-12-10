#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject(parent)
    , m_interface("org.cyber.Settings",
                  "/Theme", "org.cyber.Theme",
                  QDBusConnection::sessionBus(), this)
{
    if (m_interface.isValid()) {
        connect(&m_interface, SIGNAL(wallpaperChanged(QString)), this, SLOT(onWallpaperChanged(QString)));

        m_wallpaper = m_interface.property("wallpaper").toString();
        emit wallpaperChanged();
    }
}

QString Settings::wallpaper() const
{
    return m_wallpaper;
}

void Settings::onWallpaperChanged(QString path)
{
    if (path != m_wallpaper) {
        m_wallpaper = path;
        emit wallpaperChanged();
    }
}

