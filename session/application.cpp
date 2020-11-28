#include "application.h"
#include "sessionadaptor.h"

#include <QDBusConnection>
#include <QStandardPaths>
#include <QSettings>
#include <QProcess>
#include <QDebug>
#include <QDir>

Application::Application(int &argc, char **argv)
    : QCoreApplication(argc, argv)
    , m_processManager(new ProcessManager)
{
    // connect to D-Bus and register as an object:
    QDBusConnection::sessionBus().registerService(QStringLiteral("org.cyber.Session"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/Session"), this);

    new SessionAdaptor(this);

    createConfigDirectory();
    initEnvironments();
    initLanguage();
    initScreenScaleFactors();

    m_processManager->start();
}

void Application::initEnvironments()
{
    qputenv("XDG_CURRENT_DESKTOP", "Cyber");
    qputenv("XDG_CONFIG_HOME", QString("%1/.config").arg(QDir::homePath()).toLocal8Bit());
    qputenv("XDG_CACHE_HOME", QString("%1/.cache").arg(QDir::homePath()).toLocal8Bit());
    qputenv("XDG_DESKTOP_DIR", QString("%1/Desktop").arg(QDir::homePath()).toLocal8Bit());
    qputenv("QT_PLATFORM_PLUGIN", "cyber");
    qputenv("QT_QPA_PLATFORMTHEME", "cyber");
    qputenv("QT_QUICK_CONTROLS_STYLE", "meui-style");
}

void Application::initLanguage()
{
    // en_US
    QString str = "en_US.UTF-8";

    const auto lcValues = {
        "LANG", "LC_NUMERIC", "LC_TIME", "LC_MONETARY", "LC_MEASUREMENT", "LC_COLLATE", "LC_CTYPE"
    };

    for (auto lc : lcValues) {
        const QString value = str;
        if (!value.isEmpty()) {
            qputenv(lc, value.toUtf8());
        }
    }

    const QString value = "en_US";
    if (!value.isEmpty()) {
        qputenv("LANGUAGE", value.toUtf8());
    }
}

void Application::initScreenScaleFactors()
{
    QSettings settings(QSettings::UserScope, "cyberos", "theme");
    qreal scaleFactor = settings.value("PixelRatio", 1.0).toReal();

    qputenv("QT_SCREEN_SCALE_FACTORS", QByteArray::number(scaleFactor));
    qputenv("QT_SCALE_FACTOR", QByteArray::number(scaleFactor));
    qputenv("GDK_SCALE", QByteArray::number(scaleFactor, 'g', 0));
    qputenv("GDK_DPI_SCALE", QByteArray::number(1.0 / scaleFactor, 'g', 3));
}

void Application::syncDBusEnvironment()
{
    int exitCode = -1;
    // At this point all environment variables are set, let's send it to the DBus session server to update the activation environment
    if (!QStandardPaths::findExecutable(QStringLiteral("dbus-update-activation-environment")).isEmpty()) {
        exitCode = runSync(QStringLiteral("dbus-update-activation-environment"), { QStringLiteral("--systemd"), QStringLiteral("--all") });
    }

    if (exitCode != 0) {
        qDebug() << "Could not sync environment to dbus.";
    }
}

void Application::createConfigDirectory()
{
    const QString configDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);

    if (!QDir().mkpath(configDir))
        qDebug() << "Could not create config directory XDG_CONFIG_HOME: " << configDir;
}

int Application::runSync(const QString &program, const QStringList &args, const QStringList &env)
{
    QProcess p;

    if (!env.isEmpty())
        p.setEnvironment(QProcess::systemEnvironment() << env);

    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.start(program, args);
    p.waitForFinished(-1);

    if (p.exitCode()) {
        qWarning() << program << args << "exited with code" << p.exitCode();
    }

    return p.exitCode();
}
