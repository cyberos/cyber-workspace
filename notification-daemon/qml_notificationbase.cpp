#include "qml_notificationbase.h"
#include <KWindowSystem>
#include <KWindowEffects>

static QRegion cornerMask(const QRect &rect, const int r)
{
    QRegion region;
    // middle and borders
    region += rect.adjusted(r, 0, -r, 0);
    region += rect.adjusted(0, r, 0, -r);

    // top left
    QRect corner(rect.topLeft(), QSize(r * 2, r * 2));
    region += QRegion(corner, QRegion::Ellipse);

    // top right
    corner.moveTopRight(rect.topRight());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom left
    corner.moveBottomLeft(rect.bottomLeft());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom right
    corner.moveBottomRight(rect.bottomRight());
    region += QRegion(corner, QRegion::Ellipse);

    return region;
}

QmlNotificationBase::QmlNotificationBase(QQuickView *parent)
    : QQuickView(parent)
{
    setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    connect(this, &QQuickView::widthChanged, this, &QmlNotificationBase::updateBlur);
    connect(this, &QQuickView::heightChanged, this, &QmlNotificationBase::updateBlur);
    /*connect(this, &QQuickView::activeChanged, this, [=] {
        if (!isActive())
            hide();
    });*/
}

void QmlNotificationBase::updateBlur()
{
    const QRect rect { 0, 0, size().width(), size().height() };
    KWindowEffects::enableBlurBehind(this->winId(), true, cornerMask(rect, 16));
}

void QmlNotificationBase::showEvent(QShowEvent *event)
{
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager | NET::SkipSwitcher);
    QQuickView::showEvent(event);
}

void QmlNotificationBase::hideEvent(QHideEvent *event)
{
    QQuickView::hideEvent(event);
}
