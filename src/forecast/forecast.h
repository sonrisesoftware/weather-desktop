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


#ifndef FORECAST_H
#define FORECAST_H

#include "weather/service.h"
#include <KIcon>

namespace Weather {
	class DataPoint;
}

namespace Forecast {

	class Point;
	
	class Forecast : public Weather::Service
	{
		Q_OBJECT

	public:
		explicit Forecast(QObject* parent = 0);
		virtual ~Forecast();
		
		virtual void download(Weather::Location *location);
		virtual Weather::DataPoint *create_conditions(Weather::Location *location);
		virtual Weather::DataBlock *create_dailyForecast(Weather::Location *location);
		virtual Weather::DataBlock *create_hourlyForecast(Weather::Location *location);
		virtual Weather::ManagedList *create_alerts(Weather::Location *location);
		virtual void json_query(Weather::Location *location, const QString& query, const QString& params, QObject* receiver, const char* slot);
		
		static QString temp(float value);
		static QString clouds(float value);
		static QString humidity(float value);
		static QString wind(float speed, float dir);
		static QString pressure(float value);
		static QString probability(float value);
		static QString visibility(float value);
		static KIcon icon(QString name);
		static QString precip(Point *data);
		
	protected:
		virtual QString prefix() { return "https://api.forecast.io"; }
		QString internalLocation(Weather::Location *location);
		
	private slots:
		void onWeatherDownloaded(Weather::Location *location, QString error, const QVariantMap& data);
		
	private:
		
		static QString validate(float value, QString string, QString def = "") {
			if (value != -99) {
				return string;
			} else {
				return def;
			}
		}
		
		static QString validate(QString value, QString string, QString def = "") {
			if (value != "!!!!") {
				return string;
			} else {
				return def;
			}
		}
		
		static QString format(float value, int rounding = 3) {
			return QLocale::system().toString(round(value), 'g', rounding);
		}
		
		static float round(float value) {
			if (value < 1e-10) 
				return 0;
			else
				return value;
		}
		
	#include "forecast/forecast.gen"
	};

};

#endif // FORECAST_H
