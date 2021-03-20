#include "application.h"
#include "sessionadaptor.h"

#include <QDBusConnection>
#include <QDebug>

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_lastID(0)
{
    new SessionAdaptor(this);

    // connect to D-Bus and register as an object
    QDBusConnection::sessionBus().registerService(QStringLiteral("org.freedesktop.Notifications"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/org/freedesktop/Notifications"), this);
}

void Application::CloseNotification(uint id) {
    emit NotificationClosed(id, 3);
}

QStringList Application::GetCapabilities() {
    return QStringList("body");
}

QString Application::GetServerInformation(QString &vendor, QString &version, QString &spec_version) {
    vendor = QString("CyberOS");
    version = QString("rolling");
    spec_version = QString("1.2");
    return QString("Cyber Notification Daemon");
}

uint Application::Notify(
    const QString &app_name,
    uint replaces_id,
    const QString &app_icon,
    const QString &summary,
    const QString &body,
    const QStringList &actions,
    const QVariantMap &hints,
    int expire_timeout
) {
    qDebug() << app_name << replaces_id << app_icon << summary << body << actions << hints << expire_timeout;
    
    int returnID = m_lastID;
    m_lastID++;

    return returnID;
}
