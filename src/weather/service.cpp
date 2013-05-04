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
#include "service.h"
#include <application.h>
#include "weather/service.h"
#include "weather/location.h"
#include "weather/conditions.h"
#include "worldweather/worldweatheronline.h"
#include "wunderground/wunderground.h"

#include <QUrl>
#include <QNetworkAccessManager>

using namespace Weather;

QString Weather::Service::m_apiKey = "";
Weather::Provider Weather::Service::m_provider = Weather::WorldWeatherOnline;

Service::Service(Location* location): QObject(location)
{
	setData(new QVariantMap());
	setLocation(location);
}

Service::~Service()
{
	delete data();
}

void Service::json_call(const QString& call, QObject *reciever, const char* slot)
{
	qDebug() << call;
	//QString text = download(QUrl(prefix() + '/' + call), error);
	KIO::TransferJob *job = KIO::get(KUrl(prefix() + '/' + call), KIO::NoReload, KIO::HideProgressInfo);
	
	QObject::connect(job, SIGNAL(result(KJob*)), this, SLOT(process_query(KJob*)));
	QObject::connect(job, SIGNAL(data(KIO::Job*,QByteArray)), this, SLOT(data_downloaded(KIO::Job*,QByteArray)));
	m_jobs[job] = new DownloadJob(reciever, slot);
}

void Weather::Service::data_downloaded(KIO::Job* job, const QByteArray& data)
{
	DownloadJob *obj = m_jobs[job];
	obj->m_data.append(data);
}

void Service::process_query(KJob *job) {
	DownloadJob *obj = m_jobs[(KIO::Job *) job];
	QByteArray data = obj->m_data;
	
	if (job->error()) {
		obj->emit_signal(job->errorString(), QVariantMap());
	}
	
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
	
	obj->emit_signal(error, result);
	m_jobs.remove((KIO::Job *) job);
	obj->deleteLater();
	job->deleteLater();
}

QVariantMap Service::data(const QString& type)
{
	return (*data())[type].toMap();
}

Service* Weather::Service::create(Location *location)
{
	qDebug() << "Creating service provider...";
	if (weatherProvider() == Weather::WorldWeatherOnline) {
		return new WorldWeatherOnline::WorldWeatherOnline(location);
	} else if (weatherProvider() == Weather::Wunderground) {
		return new Wunderground::Wunderground(location);
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