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
#include <application.h>
#include "weather/service.h"
#include "weather/location.h"
#include "weather/conditions.h"
#include "worldweather/worldweatheronline.h"

#include <QUrl>
#include <QNetworkAccessManager>

using namespace Weather;

QString Weather::Service::m_apiKey = "";
Weather::Provider Weather::Service::m_provider = Weather::WorldWeatherOnline;

Service::Service(Location* location): QObject(location)
{
	setData(new QVariantMap());
}

Service::~Service()
{

}

void Service::json_call(const QString& call, QObject *reciever, const char* slot)
{
	//QString text = download(QUrl(prefix() + '/' + call), error);
	KIO::TransferJob *job = KIO::get(KUrl(prefix() + '/' + call), KIO::NoReload, KIO::HideProgressInfo);
	
	QObject::connect(job, SIGNAL(data(KIO::Job*,QByteArray)), this, SLOT(process_query(KIO::Job*,QByteArray)));
	m_slots[job] = new SlotObject(reciever, slot);
}

void Service::process_query(KIO::Job *job, const QByteArray& data) {
	qDebug() << "Data:" << data;
	
	QString error; bool ok;
	QJson::Parser parser;
	QVariantMap result = parser.parse(data, &ok).toMap();
	if (!ok) {
		error = "Unable to parse JSON response!";
		qDebug() << "ERROR:" << error;
	} else if (result["response"].toMap().contains("error")) {
		error = "[" + result["response"].toMap()["error"].toMap()["type"].toString() + "] " + 
				result["response"].toMap()["error"].toMap()["description"].toString();
	}
	
	SlotObject *obj = m_slots[job];
	obj->emit_signal(error, result);
	
	m_slots.remove(job);
	delete obj;
	delete job;
}

Service* Weather::Service::create(Location *location)
{
	qDebug() << "Creating service provider...";
	if (weatherProvider() == Weather::WorldWeatherOnline) {
		return new WorldWeatherOnline::WorldWeatherOnline(location);
	} else {
		qFatal("Invalid service provider!");
		return nullptr;
	}
}

void Weather::Service::setWeatherProvider(Weather::Provider provider)
{
	m_provider = provider;
}



#include "weather/service.moc"