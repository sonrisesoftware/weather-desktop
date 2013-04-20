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
		
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
		Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged)
		Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
		Q_PROPERTY(QImage *background READ background WRITE setBackground NOTIFY backgroundChanged)

	public:
		explicit Location(const QString& name, const QString& location, QObject* parent = 0);
		virtual ~Location();
		
	public slots:
		void refresh();
		
	signals:		
		void refreshed();
	
	#include "weather/location.gen"
	};

}

#endif // LOCATION_H
