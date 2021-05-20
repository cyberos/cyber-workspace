
/*
 * Copyright (C) 2020 CyberOS Project
 *
 * Author:     omame <me@omame.tech>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hotkeys.h"

// https://github.com/cyberos/cyber-workspace/blob/main/session/processmanager.cpp#L55-L71
void startProcess(QPair<QString, QStringList> pair) {
    QProcess *process = new QProcess;
    process->setProcessChannelMode(QProcess::ForwardedChannels);
    process->setProgram(pair.first);
    process->setArguments(pair.second);
    process->start();
    process->waitForStarted();
}

Hotkeys::Hotkeys(QObject *parent) : QObject(parent) {
	// register shortcut
	auto launcherShortcut = new QHotkey();
	auto nativeShortcut = QHotkey::NativeShortcut(133);
	qDebug() << nativeShortcut.isValid();
	launcherShortcut->setNativeShortcut(nativeShortcut, true);
	qDebug() << "Launcher hotkey registered:" << launcherShortcut->isRegistered();
	
	connect(launcherShortcut, &QHotkey::activated, this, &Hotkeys::startLauncher);
}

void Hotkeys::startLauncher() {
	qDebug() << "Starting launcher...";
	startProcess(qMakePair(QString("cyber-launcher"), QStringList()));
}
