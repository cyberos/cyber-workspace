#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "processmanager.h"
#include "powermanager/power.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);


public slots:
    void logout()
    {
        m_processManager->logout();
    }

    void reboot()
    {
        m_power.reboot();
        QCoreApplication::exit(0);
    }

    void powerOff()
    {
        m_power.shutdown();
        QCoreApplication::exit(0);
    }

private:
    void initEnvironments();
    void initLanguage();
    void initScreenScaleFactors();
    void syncDBusEnvironment();
    void createConfigDirectory();
    int runSync(const QString &program, const QStringList &args, const QStringList &env = {});

private:
    ProcessManager *m_processManager;
    Power m_power;
};

#endif // APPLICATION_H
