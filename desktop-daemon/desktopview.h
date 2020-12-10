#ifndef DESKTOPVIEW_H
#define DESKTOPVIEW_H

#include <QQuickView>

class DesktopView : public QQuickView
{
    Q_OBJECT

public:
    explicit DesktopView(QQuickView *parent = nullptr);
};

#endif // DESKTOPVIEW_H