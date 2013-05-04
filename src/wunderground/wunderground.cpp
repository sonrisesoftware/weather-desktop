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

#include "main.h"
#include "wunderground/wunderground.h"
#include "wunderground/conditions.h"

using namespace Wunderground;

Wunderground::Wunderground::Wunderground(Weather::Location* location): Weather::Service(location)
{
	qDebug() << "Wunderground weather!";
}

Wunderground::Wunderground::~Wunderground()
{

}

QString Wunderground::Wunderground::internalLocation()
{
	if (location()->location().isEmpty()) {
		return "autoip";
	} else {
		QStringList list = location()->location().split(",");
		if (list.size() == 2) {
			return list.at(1) + "/" + list.at(0);
		} else {
			return location()->location();
		}
	}
}

QString Wunderground::Wunderground::prefix()
{
	return "http://api.wunderground.com/api/";
}

void Wunderground::Wunderground::refresh()
{
	json_query("conditions/forecast", "", this, SLOT(onConditionsDownloaded(QString,QVariantMap)));
}

Weather::Conditions* Wunderground::Wunderground::create_conditions()
{
	return new WundergroundConditions(location());
}

void Wunderground::Wunderground::json_query(const QString& query, const QString& params, QObject* reciever, const char* slot)
{
	json_call(Weather::Service::apiKey() + "/" + query + "/q/" + internalLocation() + ".json?" + params, reciever, slot);
}

void Wunderground::Wunderground::onConditionsDownloaded(QString error, const QVariantMap& data)
{
// 	if (error.isEmpty() && data["data"].toMap().contains("error")) {
// 		error = data["data"].toMap()["error"].toList()[0].toMap()["msg"].toString();
// 	}
	
	location()->setUpdating(false);
	
	if (!error.isEmpty()) {
		location()->setError(true);
		location()->setErrorMessage(error);
		return;
	}
	
	//qDebug() << "Saving data: " << data;
	delete this->data();
	this->setData(new QVariantMap(data));
	//qDebug() << "NEW Data: " << *this->data();
	emit refreshed();
}


#include "wunderground/wunderground.moc"