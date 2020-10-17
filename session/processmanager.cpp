#include "processmanager.h"
#include <QCoreApplication>
#include <QDebug>

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent)
{
}

void ProcessManager::start()
{
    loadSystemProcess();
}

void ProcessManager::logout()
{
    QMap<QString, QProcess *>::iterator itor = m_systemProcess.begin();
    while (itor != m_systemProcess.end()) {
        QProcess *process = itor.value();
        process->terminate();
        if (process->state() != QProcess::NotRunning && !process->waitForFinished(2000)) {
            process->kill();
        }
        ++itor;
    }

    QCoreApplication::exit(0);
}

void ProcessManager::loadSystemProcess()
{
    QList<QPair<QString, QStringList>> list;
    list << qMakePair(QString("kwin_x11"), QStringList());
    list << qMakePair(QString("cyber-settings-daemon"), QStringList());
    list << qMakePair(QString("panda-files"), QStringList() << "--desktop");
    list << qMakePair(QString("panda-statusbar"), QStringList());
    list << qMakePair(QString("cyber-dock"), QStringList());
    list << qMakePair(QString("cyber-launcher"), QStringList());
    list << qMakePair(QString("cyber-xembedsniproxy"), QStringList());

    for (QPair<QString, QStringList> pair : list) {
        QProcess *process = new QProcess;
        process->setProgram(pair.first);
        process->setArguments(pair.second);
        process->start();

        qDebug() << "loadSystemProcess(): " << pair.first << pair.second;

        // Add to map
        m_systemProcess.insert(pair.first, process);
    }
}
