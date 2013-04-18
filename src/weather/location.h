/***************************************************************************
 *  Weather Desktop - An advanced, cross-platform weather application.     *
 *  Copyright (C) 2013  Michael Spencer <spencers1993@gmail.com>           *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/


#ifndef LOCATION_H
#define LOCATION_H

#include "main.h"

#include <QObject>
#include <QString>
#include <QImage>
#include <QIcon>

namespace Weather
{

	class Location : public QObject
	{
		Q_OBJECT
		
		P_PROPERTY(QString, name, name, setName)
		P_PROPERTY(QString, location, location, setLocation)
		P_PROPERTY(QString, display, display, setDisplay)
		P_PROPERTY(QIcon, icon, icon, setIcon)
		P_PROPERTY(QImage *, background, background, setBackground)

	public:
		explicit Location(const QString& name, const QString& location, QObject* parent = 0);
		virtual ~Location();
		
	public slots:
		void refresh();
		
	signals:
		void refreshed();
	};

}

#endif // LOCATION_H
