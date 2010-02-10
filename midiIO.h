/****************************************************************************
**
** Copyright (C) 2007~2010 Colin Willcocks.
** Copyright (C) 2005~2007 Uco Mesdag. 
** All rights reserved.
** This file is part of "GT-5 Fx FloorBoard".
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
**
****************************************************************************/

#ifndef MIDIIO_H
#define MIDIIO_H
#include <vector>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QList>

class midiIO: public QThread
{
	Q_OBJECT

public:
	midiIO();
	void run();
	void sendSysxMsg(QString sysxOutMsg, int midiOutport, int midiInPort);
	void sendMidi(QString midiMsg, int midiOutport);
	void callbackMsg(QString rxData);
	QList<QString> getMidiOutDevices();
	QList<QString> getMidiInDevices();
	
		
signals:
	void errorSignal(QString windowTitle, QString errorMsg);
	void replyMsg(QString sysxInMsg);
	void midiFinished();
	void started();
	void setStatusSymbol(int value);
	void setStatusProgress(int value);
  void setStatusMessage(QString message);
  void setStatusdBugMessage(QString dBug);
		
private:
	void queryMidiInDevices();
	void queryMidiOutDevices();
	void sendSyxMsg(QString sysxOutMsg, int midiOutport);
	void sendMidiMsg(QString sysxOutMsg, int midiOutport);
	void receiveMsg(QString sysxMsg, int midiInPort);
	QList<QString> midiOutDevices;
	QList<QString> midiInDevices;
	
	static QString msgType;
	static QString sysxBuffer;
	static bool dataReceive;
	static int bytesTotal;
	int midiOutPort;
	int midiInPort;
	QString sysxOutMsg;
	QString sysxInMsg;
	QString midiMsg;
	int dataSize;
	int h;
	QString reBuild;
	QString hex;
	bool midi;
	int count;
};

#endif // MIDIIO_H
