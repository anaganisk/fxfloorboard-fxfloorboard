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

#include "floorPanelBarButton.h"

floorPanelBarButton::floorPanelBarButton(bool collapsed, QPoint buttonPos, QWidget *parent,
						   QString imagePath, QSize buttonSize, unsigned int imageRange)
    : QWidget(parent)
{
	this->collapsed = collapsed;
	this->imagePath = imagePath;
	this->buttonSize = buttonSize;
	this->imageRange = imageRange;
	this->buttonPos = buttonPos;
	setOffset(0);
    setGeometry(buttonPos.x(), buttonPos.y(), buttonSize.width(), buttonSize.height());

	QObject::connect(this, SIGNAL( collapseSignal() ),
                this->parent(), SIGNAL( collapseSignal() ) );

	QObject::connect(this->parent(), SIGNAL( collapseState(bool) ),
                this, SLOT( setCollapseState(bool) ) );

	this->setCursor(Qt::ArrowCursor);
};

void floorPanelBarButton::paintEvent(QPaintEvent *)
{
	QRectF target(0.0 , 0.0, buttonSize.width(), buttonSize.height());
	QRectF source(xOffset, 0.0, buttonSize.width(), buttonSize.height());
	QPixmap image(imagePath);

	QPainter painter(this);
	painter.drawPixmap(target, image, source);
};

void floorPanelBarButton::setOffset(signed int imageNr)
{
	this->xOffset = imageNr*buttonSize.width();
	this->update();
};

void floorPanelBarButton::mousePressEvent(QMouseEvent *event)
{
	if ( event->button() == Qt::LeftButton )
	{	
		this->dragStartPosition = event->pos();
	};
};

void floorPanelBarButton::mouseReleaseEvent(QMouseEvent *event) 
{ 
	if ( event->button() == Qt::LeftButton && 
		(event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance() ) 
	{
		emit collapseSignal();
	}; 
};

void floorPanelBarButton::mouseMoveEvent(QMouseEvent *event)
{
	event;
};

void floorPanelBarButton::setCollapseState(bool collapsed)
{
	if(collapsed == false)
	{
		setOffset(1);
	}
	else
	{
		setOffset(0);
	};
};
