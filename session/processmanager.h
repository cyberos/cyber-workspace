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
    ~ProcessManager();

    void start();
    void logout();

    void loadBaseProcesses();
    void loadAutoStartProcesses();
    void loadLateProcesses();

private:
    QMap<QString, QProcess *> m_systemProcess;
    QMap<QString, QProcess *> m_autoStartProcess;

    void startProcess(QPair<QString, QStringList> pair);

    bool m_completedInit;
};

#endif // PROCESSMANAGER_H
