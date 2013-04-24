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


#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QVariantMap>
#include <qjson/parser.h>

namespace Weather
{
	class Location;
	class Conditions;

	class Service : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString apiKey READ apiKey NOTIFY apiKeyChanged)
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)

	public:
		explicit Service(Location* location);
		virtual ~Service();

		//virtual QVariantMap json_query(QString *error, const QString& query, const QString& params = "") = 0;
		
		//Weather::Conditions *create_conditions() = 0;
		Weather::Conditions *create_conditions();
		
	protected:
		QVariantMap json_call(QString *error, const QString& call);
		
		//virtual QString prefix() = 0;
		virtual QString prefix() { return ""; };
		
	#include "weather/service.gen"
	};
	
}

#endif // SERVICE_H
