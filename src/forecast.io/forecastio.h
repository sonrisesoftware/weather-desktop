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


#ifndef FORECASTIO_H
#define FORECASTIO_H

#include "weather/service.h"

namespace ForecastIO {

	class ForecastIO : public Weather::Service
	{
		Q_OBJECT

	public:
		explicit ForecastIO(QObject* parent = 0);
		virtual ~ForecastIO();
		
		virtual void download(Weather::Location* location);
		virtual Weather::Conditions* create_conditions(Weather::Location* location);
		virtual void json_query(Weather::Location* location, const QString& query, const QString& params, QObject* receiver, const char* slot);
	
	protected:
		virtual QString prefix() { return "https://api.forecast.io"; }
		QString internalLocation(Weather::Location *location);
		
	private slots:
		void onWeatherDownloaded(Weather::Location *location, QString error, const QVariantMap& data);
		
	#include "forecast.io/forecastio.gen"
	};

};

#endif // FORECASTIO_H
