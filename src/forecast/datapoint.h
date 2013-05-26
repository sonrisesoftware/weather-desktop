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


#ifndef FORECAST_DATAPOINT_H
#define FORECAST_DATAPOINT_H

#include <QObject>
#include <QDateTime>
#include <QIcon>

namespace Weather {
	class Location;
}

namespace Forecast {

	class Point: public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged);
		Q_PROPERTY(QString path READ path NOTIFY pathChanged)
		
		Q_PROPERTY(QDateTime time READ time WRITE setTime NOTIFY timeChanged);
		Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged);
		Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged);

		Q_PROPERTY(QDateTime sunriseTime READ sunriseTime WRITE setSunriseTime NOTIFY sunriseTimeChanged);
		Q_PROPERTY(QDateTime sunsetTime READ sunsetTime WRITE setSunsetTime NOTIFY sunsetTimeChanged);

		Q_PROPERTY(float precipIntensity READ precipIntensity WRITE setPrecipIntensity NOTIFY precipIntensityChanged);
		Q_PROPERTY(float precipIntensityMax READ precipIntensityMax WRITE setPrecipIntensityMax NOTIFY precipIntensityMaxChanged);
		Q_PROPERTY(QDateTime precipIntensityMaxTime READ precipIntensityMaxTime WRITE setPrecipIntensityMaxTime NOTIFY precipIntensityMaxTimeChanged);
		Q_PROPERTY(float precipProbability READ precipProbability WRITE setPrecipProbability NOTIFY precipProbabilityChanged);
		Q_PROPERTY(QString precipType READ precipType WRITE setPrecipType NOTIFY precipTypeChanged);
		Q_PROPERTY(float precipAccumulation READ precipAccumulation WRITE setPrecipAccumulation NOTIFY precipAccumulationChanged);

		Q_PROPERTY(float temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged);
		Q_PROPERTY(float temperatureMin READ temperatureMin WRITE setTemperatureMin NOTIFY temperatureMinChanged);
		Q_PROPERTY(QDateTime temperatureMinTime READ temperatureMinTime WRITE setTemperatureMinTime NOTIFY temperatureMinTimeChanged);
		Q_PROPERTY(float temperatureMax READ temperatureMax WRITE setTemperatureMax NOTIFY temperatureMaxChanged);
		Q_PROPERTY(QDateTime temperatureMaxTime READ temperatureMaxTime WRITE setTemperatureMaxTime NOTIFY temperatureMaxTimeChanged);

		Q_PROPERTY(float dewPoint READ dewPoint WRITE setDewPoint NOTIFY dewPointChanged);
		Q_PROPERTY(float windSpeed READ windSpeed WRITE setWindSpeed NOTIFY windSpeedChanged);
		Q_PROPERTY(float windBearing READ windBearing WRITE setWindBearing NOTIFY windBearingChanged);
		Q_PROPERTY(float cloudCover READ cloudCover WRITE setCloudCover NOTIFY cloudCoverChanged);

		Q_PROPERTY(float humidity READ humidity WRITE setHumidity NOTIFY humidityChanged);
		Q_PROPERTY(float pressure READ pressure WRITE setPressure NOTIFY pressureChanged);
		Q_PROPERTY(float visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged);
		Q_PROPERTY(float ozone READ ozone WRITE setOzone NOTIFY ozoneChanged);
		
	public:
		explicit Point(Weather::Location *location,const QString& path);
		virtual ~Point();
		
	public slots:
		void load();
			
	#include "forecast/datapoint.gen"
	};

}

#endif // FORECAST_DATAPOINT_H
