#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QProcess>
#include <QMap>

class ProcessManager : public QObject
{
    Q_OBJECT

public:
    explicit ProcessManager(QObject *parent = nullptr);

    void start();
    void logout();

    void loadSystemProcess();

private:
    QMap<QString, QProcess *> m_systemProcess;
    QMap<QString, QProcess *> m_autoStartProcess;
};

#endif // PROCESSMANAGER_H
