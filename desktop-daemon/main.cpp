#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QLocale>
#include <QTranslator>
#include <QList>

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
        QTranslator *translator = new QTranslator(app.instance());
        if (translator->load(qmFilePath)) {
            QGuiApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }

    qmlRegisterType<Settings>("org.cyber.Desktop", 1, 0, "Settings");

    
    QList<DesktopView*> desktopViews;
    for (int i = 0; i < app.screens().length(); i++) {
        desktopViews.append(new DesktopView(nullptr, app.screens()[i]));
    }

    for (int i = 0; i < desktopViews.length(); i++) {
        desktopViews[i]->show();
    }

    return app.exec();
}
