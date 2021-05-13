#ifndef ICONTHEMEPROVIDER_H
#define ICONTHEMEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QFile>

#define PIXMAP_PATH "/usr/share/pixmaps/"

class IconThemeProvider : public QQuickImageProvider
{
public:
    IconThemeProvider();

    QPixmap requestPixmap(const QString &id, QSize *realSize, const QSize &requestedSize);
};

#endif // ICONTHEMEPROVIDER_H
