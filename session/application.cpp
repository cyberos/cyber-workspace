#include "application.h"
#include "sessionadaptor.h"

#include <QDBusConnection>
#include <QStandardPaths>
#include <QSettings>
#include <QProcess>
#include <QDebug>
#include <QDir>

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
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
    syncDBusEnvironment();

    m_processManager->start();
}

void Application::initEnvironments()
{
    // Set defaults
    if (qEnvironmentVariableIsEmpty("XDG_DATA_HOME"))
        qputenv("XDG_DATA_HOME", QDir::home().absoluteFilePath(QStringLiteral(".local/share")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_DESKTOP_DIR"))
        qputenv("XDG_DESKTOP_DIR", QDir::home().absoluteFilePath(QStringLiteral("/Desktop")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_CONFIG_HOME"))
        qputenv("XDG_CONFIG_HOME", QDir::home().absoluteFilePath(QStringLiteral(".config")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_CACHE_HOME"))
        qputenv("XDG_CACHE_HOME", QDir::home().absoluteFilePath(QStringLiteral(".cache")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_DATA_DIRS"))
        qputenv("XDG_DATA_DIRS", "/usr/local/share/:/usr/share/");
    if (qEnvironmentVariableIsEmpty("XDG_CONFIG_DIRS"))
        qputenv("XDG_CONFIG_DIRS", "/etc/xdg");

    // Environment
    qputenv("DESKTOP_SESSION", "Cyber");
    qputenv("XDG_CURRENT_DESKTOP", "Cyber");
    qputenv("XDG_SESSION_DESKTOP", "Cyber");

    // Set environment for the programs we will launch from here
// #if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
//     qputenv("QT_QPA_PLATFORM", "wayland;xcb");
// #else
//     qputenv("QT_QPA_PLATFORM", "wayland");
// #endif

    qputenv("QT_QPA_PLATFORMTHEME", "cyber");
    qputenv("QT_PLATFORM_PLUGIN", "cyber");

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
