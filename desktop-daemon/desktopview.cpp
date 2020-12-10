#include "desktopview.h"

#include <QGuiApplication>
#include <QScreen>

#include <KWindowSystem>

DesktopView::DesktopView(QQuickView *parent)
    : QQuickView(parent)
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);
    setTitle(tr("Desktop"));

    KWindowSystem::setType(winId(), NET::Desktop);
    KWindowSystem::setState(winId(), NET::KeepBelow);

    setScreen(qGuiApp->primaryScreen());
    screenGeometryChanged();
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QStringLiteral("qrc:/Desktop.qml"));

    connect(qGuiApp->primaryScreen(), &QScreen::geometryChanged,
            this, &DesktopView::screenGeometryChanged, Qt::UniqueConnection);
}

void DesktopView::screenGeometryChanged()
{
    const QRect screenGeometry = qGuiApp->primaryScreen()->geometry();
    setGeometry(screenGeometry);
}
