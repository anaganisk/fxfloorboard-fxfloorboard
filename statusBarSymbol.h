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

#ifndef STATUSBARSYMBOL_H
#define STATUSBARSYMBOL_H

#include <QWidget>

class statusBarSymbol : public QWidget
{
    Q_OBJECT

public:
    statusBarSymbol(QWidget *parent = 0, QString imagePath = ":/images/statusbarsymbols.png");

public slots:
	void setValue(int value);

protected:
	void paintEvent(QPaintEvent *event);

private:
	void setOffset(signed int imageNr);

	QString imagePath;
	QSize symbolSize;
	int xOffset;
};

#endif // STATUSSYMBOL_H
