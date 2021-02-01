#include "settings.h"

#include <QDBusServiceWatcher>
#include <QProcess>

Settings::Settings(QObject *parent)
    : QObject(parent)
    , m_interface("org.cyber.Settings",
                  "/Theme", "org.cyber.Theme",
                  QDBusConnection::sessionBus(), this)
{
    QDBusServiceWatcher *watcher = new QDBusServiceWatcher(this);
    watcher->setConnection(QDBusConnection::sessionBus());
    watcher->addWatchedService("org.cyber.Settings");
    connect(watcher, &QDBusServiceWatcher::serviceRegistered, this, &Settings::init);

    init();
}

QString Settings::wallpaper() const
{
    return m_wallpaper;
}

bool Settings::dimsWallpaper() const
{
    return m_interface.property("darkModeDimsWallpaer").toBool();
}

void Settings::launch(const QString &command, const QStringList &args)
{
    QProcess process;
    process.setProgram(command);
    process.setArguments(args);
    process.startDetached();
}

void Settings::init()
{
    if (m_interface.isValid()) {
        connect(&m_interface, SIGNAL(wallpaperChanged(QString)), this, SLOT(onWallpaperChanged(QString)));
        connect(&m_interface, SIGNAL(darkModeDimsWallpaerChanged()), this, SIGNAL(dimsWallpaperChanged()));

        m_wallpaper = m_interface.property("wallpaper").toString();
        emit wallpaperChanged();
    }
}

void Settings::onWallpaperChanged(QString path)
{
    if (path != m_wallpaper) {
        m_wallpaper = path;
        emit wallpaperChanged();
    }
}
