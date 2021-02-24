#ifndef DESKTOPVIEW_H
#define DESKTOPVIEW_H

#include <QQuickView>
#include <QScreen>

class DesktopView : public QQuickView
{
    Q_OBJECT

public:
    explicit DesktopView(QQuickView *parent, QScreen *screen);

private slots:
    void screenGeometryChanged();

private:
    QScreen *m_screen;
};

#endif // DESKTOPVIEW_H
