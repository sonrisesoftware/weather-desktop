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

#include "weather/service.h"

#include "main.h"
#include "application.h"
#include "weather/location.h"
#include "weather/conditions.h"
#include "worldweather/worldweatheronline.h"
#include "wunderground/wunderground.h"

#include <QUrl>
#include <QNetworkAccessManager>

#include "config.h"

using namespace Weather;

QString Weather::Service::m_apiKey = "";
Weather::Provider Weather::Service::m_provider = Weather::WorldWeatherOnline;
int Weather::Service::m_maxCalls = 0;
int Weather::Service::m_accessCount = 0;

Service::Service(Location* location): QObject(location)
{
	setLocation(location);
}

Service::~Service()
{
	
}

void Service::json_call(const QString& call, QObject *receiver, const char* slot)
{
	if (!location()->needsUpdate()) return;
	
	if (maxCalls() > 0) {
		if (accessCount() + 1 > maxCalls()) {
			location()->setError(true);
			location()->setErrorMessage(i18n("You have accessed the weather service too many times today!"));
			location()->setUpdating(false);
			return;
		}
		
		setAccessCount(accessCount() + 1);
		qDebug() << "API Call count:" << accessCount();
	}
	
	qDebug() << "JSON Call >>>" << call;
	KIO::TransferJob *job = KIO::get(KUrl(prefix() + '/' + call), KIO::NoReload, KIO::HideProgressInfo);
	
	QObject::connect(job, SIGNAL(result(KJob*)), this, SLOT(process_query(KJob*)));
	QObject::connect(job, SIGNAL(data(KIO::Job*,QByteArray)), this, SLOT(data_downloaded(KIO::Job*,QByteArray)));
	m_jobs[job] = new DownloadJob(receiver, slot);
}

void Service::stopJobs()
{
	while (!m_jobs.isEmpty()) {
		KIO::Job *job = m_jobs.keys()[0];
		job->kill();
		job->deleteLater();
		m_jobs[job]->deleteLater();
		m_jobs.remove(job);
	}
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
	}
	
	obj->emit_signal(error, result);
	m_jobs.remove((KIO::Job *) job);
	obj->deleteLater();
	job->deleteLater();
}

QVariantMap Service::data(const QString& type)
{
	return data()[type].toMap();
}

Service* Weather::Service::create(Location *location)
{
	//qDebug() << "Creating service provider...";
	if (provider() == Weather::WorldWeatherOnline) {
		return new WorldWeatherOnline::WorldWeatherOnline(location);
	} else if (provider() == Weather::Wunderground) {
		return new Wunderground::Wunderground(location);
	} else {
		qFatal("Invalid service provider!");
		return nullptr;
	}
}

void Weather::Service::setProvider(Weather::Provider provider)
{
	m_provider = provider;
	
	if (provider == Weather::Wunderground) {
		Wunderground::Wunderground::init();
	}
}

#include "weather/service.moc"
