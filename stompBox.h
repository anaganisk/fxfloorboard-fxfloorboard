/****************************************************************************
**
** Copyright (C) 2005, 2006, 2007 Uco Mesdag. All rights reserved.
**
** This file is part of "GT-8 Fx FloorBoard".
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

#ifndef STOMPBOX_H
#define STOMPBOX_H

#include <QtGui>
#include "MidiTable.h"
#include "editWindow.h"
#include "customButton.h"
#include "customLed.h"
#include "customDial.h"
#include "customSlider.h"
#include "customSwitch.h"
#include "customComboBox.h"
#include "editPage.h"

class stompBox : public QWidget
{
    Q_OBJECT

public:
    stompBox(
		QWidget *parent = 0,
		unsigned int id = 0,
		QString imagePath = ":/images/od.png",
		QPoint stompPos = QPoint::QPoint(0, 0));
	void setPos(QPoint newPos);
	void setImage(QString imagePath);
	void setSize(QSize newSize);
	void setId(unsigned int id);

	void setComboBox(QString hex1, QString hex2, QString hex3, 
		QRect geometry = QRect::QRect(7, 79, 80, 13));
	void setKnob1(QString hex1, QString hex2, QString hex3);
	void setKnob2(QString hex1, QString hex2, QString hex3);
	void setSlider1(QString hex1, QString hex2, QString hex3);
	void setSlider2(QString hex1, QString hex2, QString hex3);
	void setSlider3(QString hex1, QString hex2, QString hex3);
	void setSlider4(QString hex1, QString hex2, QString hex3);
	void setSlider5(QString hex1, QString hex2, QString hex3);
	void setButton(QString hex1, QString hex2, QString hex3);
	void setButton(QString hex1, QString hex2, QString hex3, QPoint pos, QString imagePath);
	void setSwitch(QString hex1, QString hex2, QString hex3);
	void setLSB(QString hex1, QString hex2);
	void setLed();
	void updateKnob1(QString hex1, QString hex2, QString hex3);
	void updateKnob2(QString hex1, QString hex2, QString hex3);
	void updateSlider1(QString hex1, QString hex2, QString hex3);
	void updateSlider2(QString hex1, QString hex2, QString hex3);
	void updateSlider3(QString hex1, QString hex2, QString hex3);
	void updateSlider4(QString hex1, QString hex2, QString hex3);
	void updateSlider5(QString hex1, QString hex2, QString hex3);
	void updateComboBox(QString hex1, QString hex2, QString hex3);
	void updateButton(QString hex1, QString hex2, QString hex3);
	void updateSwitch(QString hex1, QString hex2, QString hex3);

	void setComboBoxCurrentIndex(int index);
	unsigned int getId();

	virtual void setEditPages() {};
	editWindow* editDetails();

public slots:
	void updatePos(signed int offsetDif);
	void valueChanged(int value, QString hex1, QString hex2, QString hex3);
	void valueChanged(bool value, QString hex1, QString hex2, QString hex3);
	void valueChanged(int index);
	virtual void updateSignal() {};
	void setDisplayToFxName();
	
signals:
	void valueChanged(QString fxName, QString valueName, QString valueStr);
	void currentIndexChanged(int index);
	void dialogUpdateSignal();
	void setEditDialog(editWindow* editDialog);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	void emitValueChanged(QString hex1, QString hex2, QString hex3, QString valueHex);
	
	editWindow *editDialog;
	QString imagePath;
	QSize stompSize;
	QPoint stompPos; 
	unsigned int id;

	QPoint dragStartPosition;
	QPixmap image;

	customDial *knob1;
	customDial *knob2;
	customSlider *slider1;
	customSlider *slider2;
	customSlider *slider3;
	customSlider *slider4;
	customSlider *slider5;
	customButton *button;
	customLed *led;
	customSwitch *switchbutton;
	customComboBox *stompComboBox;

	QString hex1;
	QString hex2;
	QString hex3;

	QString fxName;
};

#endif // STOMPBOX_H
