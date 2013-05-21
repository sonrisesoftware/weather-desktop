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

#include <QUrl>
#include <QNetworkAccessManager>

#include "config.h"

using namespace Weather;

Weather::DownloadJob::DownloadJob(Weather::Location *location, QObject *receiver, const char *slot) {
	qDebug() << "New DownloadJob!";
	m_location = location;
	QObject::connect(this, SIGNAL(data(Weather::Location *,QString,QVariantMap)), receiver, slot);
}

void Weather::DownloadJob::emit_signal(QString error, QVariantMap map) {
	qDebug() << "Emitting signal:" << error;
	emit data(m_location, error, map);
}

Service::Service(QObject *parent): QObject(parent)
{
	QTimer::singleShot(QDateTime::currentDateTime().msecsTo(QDateTime(QDate::currentDate().addDays(1))), this, SLOT(resetAccessCount()));
	QTimer::singleShot(60 * 1000, this, SLOT(resetAccessMinuteCount()));
}

Service::~Service()
{
	
}

void Service::json_call(Weather::Location *location, const QString& call, QObject *receiver, const char* slot)
{	
	if (maxCalls() > 0) {
		if (accessCount() + 1 > maxCalls()) {
			location->finishRefresh(QVariantMap(), i18n("You have accessed the weather service too many times today!"));
			return;
		}
		
		setAccessCount(accessCount() + 1);
		qDebug() << "Using default service:" << this->objectName();
		qDebug() << "API Call count:" << accessCount();
	}
	
	if (accessMinuteCount() + 1 > 5) {
		location->finishRefresh(QVariantMap(), i18n("You have accessed the weather service too many times within the last minute!"));
		return;
	}
	
	setAccessMinuteCount(accessMinuteCount() + 1);
	qDebug() << "API Call count per minute:" << accessMinuteCount();
	
	
	qDebug() << "JSON Call >>>" << call;
	KIO::TransferJob *job = KIO::get(KUrl(prefix() + '/' + call), KIO::NoReload, KIO::HideProgressInfo);
	
	QObject::connect(job, SIGNAL(result(KJob*)), this, SLOT(process_query(KJob*)));
	QObject::connect(job, SIGNAL(data(KIO::Job*,QByteArray)), this, SLOT(data_downloaded(KIO::Job*,QByteArray)));
	m_jobs[job] = new DownloadJob(location, receiver, slot);
}

void Service::stopJobs(Weather::Location *location)
{
	int index = 0;
	
	while (index <= m_jobs.size()) {
		KIO::Job *job = m_jobs.keys()[index];
		
		if (m_jobs[job]->m_location == location) {
			job->kill();
			job->deleteLater();
			m_jobs[job]->deleteLater();
			m_jobs.remove(job);
		} else {
			index++;
		}
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

#include "weather/service.moc"
