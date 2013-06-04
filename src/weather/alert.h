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


#ifndef WEATHER_ALERT_H
#define WEATHER_ALERT_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QDateTime>

namespace Weather {

	class Location;
	
	class Alert : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)
		Q_PROPERTY(QString title READ title NOTIFY titleChanged)
		Q_PROPERTY(QDateTime expires READ expires NOTIFY expiresChanged)
		Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)

	public:
		explicit Alert(Weather::Location *location);
		virtual ~Alert();
		
	public slots:
		virtual void refresh() = 0;
	
	signals:
		void refreshed();
		
	#include "weather/alert.gen"
	};

}

#endif // WEATHER_ALERT_H
