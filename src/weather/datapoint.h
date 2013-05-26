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


#ifndef WEATHER_DATAPOINT_H
#define WEATHER_DATAPOINT_H

#include <QObject>
#include <QDateTime>
#include <QIcon>

namespace Weather {
	
	class Location;

	/**
	 * This represents weather at a specific point in time, such as current
	 * conditions or the forecast for a certain day or hour.
	 */
	class DataPoint: public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged);
		Q_PROPERTY(QString path READ path NOTIFY pathChanged)
		
		Q_PROPERTY(QDateTime time READ time WRITE setTime NOTIFY timeChanged);
		Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged);
		Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged);
		Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

		Q_PROPERTY(QDateTime sunrise READ sunrise WRITE setSunrise NOTIFY sunriseChanged);
		Q_PROPERTY(QDateTime sunset READ sunset WRITE setSunset NOTIFY sunsetChanged);

		Q_PROPERTY(QString precip READ precip NOTIFY precipChanged)
		Q_PROPERTY(QString precipProbability READ precipProbability WRITE setPrecipProbability NOTIFY precipProbabilityChanged);
		Q_PROPERTY(QString precipAccumulation READ precipAccumulation WRITE setPrecipAccumulation NOTIFY precipAccumulationChanged);

		Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged);
		Q_PROPERTY(QString temperatureMin READ temperatureMin WRITE setTemperatureMin NOTIFY temperatureMinChanged);
		Q_PROPERTY(QString temperatureMax READ temperatureMax WRITE setTemperatureMax NOTIFY temperatureMaxChanged);
		
		Q_PROPERTY(QString feelsLike READ feelsLike NOTIFY feelsLikeChanged)
		Q_PROPERTY(QString dewPoint READ dewPoint WRITE setDewPoint NOTIFY dewPointChanged);
		Q_PROPERTY(QString wind READ wind WRITE setWind NOTIFY windChanged);
		Q_PROPERTY(QString windGust READ windGust NOTIFY windGustChanged)
		Q_PROPERTY(QString cloudCover READ cloudCover WRITE setCloudCover NOTIFY cloudCoverChanged);

		Q_PROPERTY(QString humidity READ humidity WRITE setHumidity NOTIFY humidityChanged);
		Q_PROPERTY(QString pressure READ pressure WRITE setPressure NOTIFY pressureChanged);
		Q_PROPERTY(QString visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged);
		Q_PROPERTY(QString ozone READ ozone WRITE setOzone NOTIFY ozoneChanged);
		
	public:
		explicit DataPoint(Weather::Location *location, const QString& path);
		virtual ~DataPoint();
		
	protected:
		// Temperature must be in Fahrenheit
		void updateColor(float temp);
		
	public slots:
		virtual void refresh() = 0;
		
	signals:
		void refreshed();
			
	#include "weather/datapoint.gen"
	};

}

#endif // WEATHER_DATAPOINT_H
