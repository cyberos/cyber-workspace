#ifndef XDGAUTOSTART_H
#define XDGAUTOSTART_H

#include <QObject>

class XdgAutoStart : public QObject
{
    Q_OBJECT

public:
    explicit XdgAutoStart(QObject *parent = nullptr);

signals:

};

#endif // XDGAUTOSTART_H
