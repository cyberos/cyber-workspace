#include "desktopview.h"

#include <QGuiApplication>
#include <QScreen>

#include <KWindowSystem>

DesktopView::DesktopView(QQuickView *parent)
    : QQuickView(parent)
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);
    KWindowSystem::setType(winId(), NET::Desktop);
    KWindowSystem::setState(winId(), NET::KeepBelow);

    setScreen(qGuiApp->primaryScreen());
    setGeometry(screen()->geometry());
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QStringLiteral("qrc:/Desktop.qml"));
}
