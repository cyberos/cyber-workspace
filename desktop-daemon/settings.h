#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDBusInterface>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString wallpaper READ wallpaper NOTIFY wallpaperChanged)

public:
    explicit Settings(QObject *parent = nullptr);

    QString wallpaper() const;

signals:
    void wallpaperChanged();

private slots:
    void onWallpaperChanged(QString);

private:
    QDBusInterface m_interface;
    QString m_wallpaper;
};

#endif // SETTINGS_H
