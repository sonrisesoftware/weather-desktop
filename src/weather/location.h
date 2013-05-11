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

#include "cache.h"

#include <QObject>
#include <QVariantMap>

namespace Weather
{
	class Conditions;
	class Service;

	class Location : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
		Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged)
		
		Q_PROPERTY(Weather::Service *service READ service WRITE setService NOTIFY serviceChanged)
		Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
		Q_PROPERTY(Cache *cache READ cache NOTIFY cacheChanged)
		
		Q_PROPERTY(Weather::Conditions *conditions READ conditions NOTIFY conditionsChanged)
		// TODO: Add more weather types here
		
		Q_PROPERTY(bool refreshing READ isRefreshing NOTIFY refreshingChanged)
		Q_PROPERTY(bool error READ hasError NOTIFY errorChanged)
		Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
		
		Q_PROPERTY(bool day READ isDay NOTIFY dayChanged)
		
		Q_PROPERTY(QString lastUpdated READ lastUpdated NOTIFY lastUpdatedChanged)
			
	public:
		explicit Location(const QString& name, const QString& location, Service *service, QObject *parent = 0);
	
	#include "weather/location.gen"
	};

}

#endif // LOCATION_H
