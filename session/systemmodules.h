#ifndef SYSTEMMODULES_H
#define SYSTEMMODULES_H

#include <QObject>

class SystemModules : public QObject
{
    Q_OBJECT

public:
    SystemModules(QObject *parent = nullptr);
    ~SystemModules();
};

#endif