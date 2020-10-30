#include <QGuiApplication>
#include <PolkitQt1/Subject>
#include "polkitagentlistener.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    PolKitAgentListener listener;
    PolkitQt1::UnixSessionSubject session(getpid());

    if (!listener.registerListener(session, QStringLiteral("/org/cyberos/PolicyKit1/AuthenticationAgent")))
        return -1;

    return app.exec();
}
