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

#ifndef FLOORPANELBARBUTTON_H
#define FLOORPANELBARBUTTON_H

#include <QtGui>
#include <QWidget>
#include <QPixmap>

class floorPanelBarButton : public QWidget
{
    Q_OBJECT

public:
	floorPanelBarButton(
		bool collapsed = false,
		QPoint buttonPos = QPoint::QPoint(0, 0),
		QWidget *parent = 0,
		QString imagePath = ":/images/panelbarbutton.png",
		QSize buttonSize = QSize::QSize(17, 36),
		unsigned int imageRange = 1);
	void setOffset(signed int imageNr);

public slots:
	void setCollapseState(bool collapsed);

signals:
	void collapseSignal();

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);	
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	bool collapsed;
	QString imagePath;
	QSize buttonSize;
	unsigned int imageRange;
	QPoint buttonPos; 
	QPoint dragStartPosition;
	signed int xOffset;
};

#endif // FLOORPANELBARBUTTON_H
