#include "desktopview.h"

#include <QGuiApplication>
#include <QScreen>

#include <KWindowSystem>

DesktopView::DesktopView(QQuickView *parent, QScreen *screen)
    : QQuickView(parent), 
    m_screen(screen)
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);
    setTitle(tr("Desktop"));

    KWindowSystem::setType(winId(), NET::Desktop);
    KWindowSystem::setState(winId(), NET::KeepBelow);

    setScreen(screen);
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QStringLiteral("qrc:/Desktop.qml"));
    screenGeometryChanged();

    connect(screen, &QScreen::virtualGeometryChanged, this, &DesktopView::screenGeometryChanged);
    connect(screen, &QScreen::geometryChanged, this, &DesktopView::screenGeometryChanged);
}

void DesktopView::screenGeometryChanged()
{
    setGeometry(m_screen->geometry());
}
