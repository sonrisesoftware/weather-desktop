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
#include "geocoding.h"
#include "cache.h"
#include "weather/units.h"

#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QTime>

namespace Weather
{

	class Service;
	class DataPoint;
	class DataBlock;
	class ManagedList;

	class Location : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
		Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged)
		Q_PROPERTY(Geocoding *coder READ coder NOTIFY coderChanged)
		Q_PROPERTY(QString coordinates READ coordinates WRITE setCoordinates NOTIFY coordinatesChanged)
		
		Q_PROPERTY(Weather::Service *service READ service WRITE setService NOTIFY serviceChanged)
		Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
		
		Q_PROPERTY(Weather::DataPoint *conditions READ conditions NOTIFY conditionsChanged)
		Q_PROPERTY(Weather::DataBlock *dailyForecast READ dailyForecast NOTIFY dailyForecastChanged)
		Q_PROPERTY(Weather::DataBlock *hourlyForecast READ hourlyForecast NOTIFY hourlyForecastChanged)
		Q_PROPERTY(Weather::ManagedList *alerts READ alerts NOTIFY alertsChanged)
		// Add more weather types here
		
		Q_PROPERTY(bool needsRefresh READ needsRefresh NOTIFY needsRefreshChanged)
		Q_PROPERTY(bool refreshing READ isRefreshing NOTIFY refreshingChanged)
		Q_PROPERTY(bool error READ hasError NOTIFY errorChanged)
		Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
		Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)
		
		Q_PROPERTY(bool day READ isDay WRITE setDay NOTIFY dayChanged)
		
		Q_PROPERTY(QTime lastUpdated READ lastUpdated NOTIFY lastUpdatedChanged)
		
		STATIC_PROPERTY(bool, autoRefresh, autoRefresh, setAutoRefresh)
		STATIC_PROPERTY(int, refreshTime, refreshTime, setRefreshTime)
		STATIC_PROPERTY(Service *, defaultService, defaultService, setDefaultService)
		STATIC_PROPERTY(Units *, units, units, setUnits)
		STATIC_PROPERTY(bool, html, html, setHtml)
		
	public:
		explicit Location(const QString& name, const QString& location, Service *service, QObject *parent = 0);
		explicit Location(const QString& name, const QString& location, QObject *parent = 0): Location(name, location, nullptr, parent) {}
		explicit Location(const QString& location, QObject *parent = 0): Location("", location, parent) {}
		explicit Location(const QString& location, Service *service, QObject *parent = 0): Location("", location, service, parent) {}
		
		virtual ~Location();
		
		QVariantMap data(const QString& weather) {
			return data()[weather].toMap();
		}
		
		/**
		 * Called from Service when new weather data is completely downloaded.
		 */
		void finishRefresh(QVariantMap data, QString error);
		
		static Cache *cache() {
			if (s_cache == nullptr) {
				s_cache = new Cache(KStandardDirs::locateLocal("appdata", "weather-cache"));
			}
			
			return s_cache;
		}		
		
		static void setCache(Cache *cache) {
			Q_ASSERT(s_cache == nullptr);
			Q_ASSERT(cache != nullptr);
			
			s_cache = cache;
		}
		
		static void setCache(const QString& cacheDirectory) {
			setCache(new Cache(cacheDirectory));
		}
		
	private:
		static Cache *s_cache;
		
	public slots:
		void refresh();
		void cancelRefresh();
		
	private slots:
		/*
		 * Called by the timer when it is time to refresh again.
		 */
		void timeToRefresh();
		
		/**
		 * Called when the location changed to handle refreshing.
		 */
		void onLocationChanged();
		
	signals:
		void refreshed();

	#include "weather/location.gen"
	};

}

#endif // LOCATION_H
