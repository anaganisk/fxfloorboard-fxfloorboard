/****************************************************************************
**
** Copyright (C) 2005, 2006, 2007 Uco Mesdag. All rights reserved.
**
** This file is part of "GT-10B Fx FloorBoard".
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

#include "menuPage.h"
#include "MidiTable.h"
#include "SysxIO.h"
#include "globalVariables.h"
#include "floorBoardDisplay.h"

menuPage::menuPage(QWidget *parent, unsigned int id, QString imagePath, QPoint stompPos)
    : QWidget(parent)
{
	this->id = id;
	this->imagePath = imagePath;
	this->stompSize = QPixmap(imagePath).size();
	this->stompPos = stompPos;	

	this->setFixedSize(stompSize);

	this->editDialog = new editWindow();

	QObject::connect(this, SIGNAL( valueChanged(QString, QString, QString) ),
                this->parent(), SIGNAL( valueChanged(QString, QString, QString) ));
	
	QObject::connect(this->parent(), SIGNAL( updateStompOffset(signed int) ),
                this, SLOT( updatePos(signed int) ));

	QObject::connect(this->parent(), SIGNAL( updateSignal() ),
                this, SLOT( updateSignal() ));

	QObject::connect(this->editDialog, SIGNAL( updateSignal() ),
                this, SLOT( updateSignal() ));

	QObject::connect(this, SIGNAL( dialogUpdateSignal() ),
                this->editDialog, SIGNAL( dialogUpdateSignal() ));	

	QObject::connect(this->parent(), SIGNAL( updateSignal() ),
                this->editDialog, SIGNAL( dialogUpdateSignal() ));

	QObject::connect(this->editDialog, SIGNAL( updateSignal() ),
                this, SLOT( setDisplayToFxName() ));

	QObject::connect(this, SIGNAL( setEditDialog(editWindow*) ),
                this->parent(), SLOT( setEditDialog(editWindow*) ));
                
  QObject::connect(this->parent(), SIGNAL(assignSignal(bool)), this, SLOT(assignSignal(bool)));  //cw             
 
};

void menuPage::paintEvent(QPaintEvent *)
{
	QRectF target(0.0, 0.0, stompSize.width(), stompSize.height());
	QRectF source(0.0, 0.0, stompSize.width(), stompSize.height());
	QPixmap image(imagePath);

	this->image = image;

	QPainter painter(this);
	painter.drawPixmap(target, image, source);
};

editWindow* menuPage::editDetails()
{
	return this->editDialog;
};

void menuPage::mousePressEvent(QMouseEvent *event) 
{ 
	emitValueChanged(this->hex1, this->hex2, "00", "void");

	if (event->button() == Qt::LeftButton) 
	{
		this->editDialog->setWindow(this->fxName);
		emit setEditDialog(this->editDialog);
	}
	else if (event->button() == Qt::RightButton)
	{
		this->editDialog->setWindow(this->fxName);
		emit setEditDialog(this->editDialog);
	};
};

void menuPage::assignSignal(bool value)	
	{
	 QApplication::beep();
	  this->editDialog->setWindow("System Settings");
		emit setEditDialog(this->editDialog);
  };

void menuPage::setPos(QPoint newPos)
{
	this->move(newPos);
	//this->stompPos = newPos;
};

void menuPage::updatePos(signed int offsetDif)
{ 
	this->stompPos = this->pos();
	QPoint newPos = stompPos + QPoint::QPoint(offsetDif, 0);
	this->move(newPos);
	//this->stompPos = newPos;
};
	
void menuPage::setImage(QString imagePath)
{
	this->imagePath = imagePath;
	this->update();
};

void menuPage::setSize(QSize newSize)
{
	this->stompSize = newSize;
	this->setFixedSize(stompSize);
};

void menuPage::setId(unsigned int id)
{
	this->id = id;
};

unsigned int menuPage::getId()
{
	return this->id;
};

void menuPage::setLSB(QString hex1, QString hex2)
{
	this->hex1 = hex1;
	this->hex2 = hex2;
	this->editDialog->setLSB(hex1, hex2);
};

void menuPage::valueChanged(int value, QString hex1, QString hex2, QString hex3)
{
	MidiTable *midiTable = MidiTable::Instance();
	
	QString valueHex = QString::number(value, 16).toUpper();
	if(valueHex.length() < 2) valueHex.prepend("0");

	SysxIO *sysxIO = SysxIO::Instance(); bool ok;
	if(midiTable->isData("Structure", hex1, hex2, hex3))
	{	
		int maxRange = QString("7F").toInt(&ok, 16) + 1;
		int value = valueHex.toInt(&ok, 16);
		int dif = value/maxRange;
		QString valueHex1 = QString::number(dif, 16).toUpper();
		if(valueHex1.length() < 2) valueHex1.prepend("0");
		QString valueHex2 = QString::number(value - (dif * maxRange), 16).toUpper();
		if(valueHex2.length() < 2) valueHex2.prepend("0");
		
		sysxIO->setFileSource(hex1, hex2, hex3, valueHex1, valueHex2);
	}
	else
	{
		sysxIO->setFileSource(hex1, hex2, hex3, valueHex);
	};

	emitValueChanged(hex1, hex2, hex3, valueHex);
};

void menuPage::valueChanged(bool value, QString hex1, QString hex2, QString hex3)
{
	int valueInt;
	(value)? valueInt=1: valueInt=0;
	QString valueHex = QString::number(valueInt, 16).toUpper();
	if(valueHex.length() < 2) valueHex.prepend("0");
	
	SysxIO *sysxIO = SysxIO::Instance();
	sysxIO->setFileSource(hex1, hex2, hex3, valueHex);

	emitValueChanged(hex1, hex2, hex3, valueHex);
};

void menuPage::emitValueChanged(QString hex1, QString hex2, QString hex3, QString valueHex)
{
	QString valueName, valueStr;
	if(hex1 != "void" && hex2 != "void")
	{
		MidiTable *midiTable = MidiTable::Instance();
		if(valueHex != "void")
		{
			Midi items = midiTable->getMidiMap("Structure", hex1, hex2, hex3);
			valueName = items.desc;
			this->fxName = midiTable->getMidiMap("Structure", hex1, hex2, hex3).name;
			valueStr = midiTable->getValue("Structure", hex1, hex2, hex3, valueHex);
			emit dialogUpdateSignal();
		}
		else
		{
		 
		  if (this->id == 18)this->fxName = "System settings";
		  if (this->id == 19)this->fxName = "System Midi";
		  if (this->id == 20)this->fxName = "Assigns";
				 //midiTable->getMidiMap("Structure", hex1, hex2, hex3).name;//hex1).customdesc;
		};
	};

	emit valueChanged(this->fxName, valueName, valueStr);
};

void menuPage::setDisplayToFxName()
{
	emit valueChanged(this->fxName, "", "");
};
