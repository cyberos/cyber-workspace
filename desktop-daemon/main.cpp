#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QLocale>
#include <QTranslator>

#include "desktopview.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    // Translations
    QLocale locale;
    QString qmFilePath = QString("%1/%2.qm").arg("/usr/share/cyber-desktop-daemon/translations/").arg(locale.name());
    if (QFile::exists(qmFilePath)) {
        QTranslator *translator = new QTranslator(QApplication::instance());
        if (translator->load(qmFilePath)) {
            QApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }

    qmlRegisterType<Settings>("org.cyber.Desktop", 1, 0, "Settings");

    DesktopView view;
    view.show();

    return app.exec();
}
