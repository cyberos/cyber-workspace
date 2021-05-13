#ifndef QML_NOTIFICATIONBASE_H
#define QML_NOTIFICATIONBASE_H

#include <QQuickView>
#include <QTimer>

class QmlNotificationBase : public QQuickView
{
    Q_OBJECT

public:
    QmlNotificationBase(QQuickView *view = nullptr);

    Q_INVOKABLE void updateBlur();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // QML_NOTIFICATIONBASE_H
