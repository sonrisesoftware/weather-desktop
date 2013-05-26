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

#include "main.h"
#include "cache.h"

#include <QObject>
#include <QVariantMap>
#include <QTimer>
#include <QDateTime>
#include <QByteArray>
#include <qjson/parser.h>

#include <KDE/KUrl>
#include <KIO/TransferJob>
#include <KIO/Job>
#include <KDE/KLocalizedString>

namespace Weather
{
	class Location;
	class DataPoint;
	class DataBlock;
	
	class DownloadJob: public QObject {
		Q_OBJECT
		
	public:
		DownloadJob(Weather::Location *location, QObject *receiver, const char *slot);
		
		void emit_signal(QString error, QVariantMap map);
		
		QByteArray m_data;
		Weather::Location *m_location;
		
	signals:
		void data(Weather::Location *location, QString error, QVariantMap data);
	};

	class Service : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged)
		Q_PROPERTY(int maxCalls READ maxCalls WRITE setMaxCalls NOTIFY maxCallsChanged)
		Q_PROPERTY(int accessCount READ accessCount WRITE setAccessCount NOTIFY accessCountChanged)
		Q_PROPERTY(int accessMinuteCount READ accessMinuteCount WRITE setAccessMinuteCount NOTIFY accessMinuteCountChanged)

	public:
		explicit Service(QObject *parent = 0);
		virtual ~Service();

		virtual void json_query(Weather::Location *location, const QString& query, const QString& params, QObject *receiver, const char* slot) = 0;
		
		inline void json_query(Weather::Location *location, const QString& query, QObject *receiver, const char* slot) {
			json_query(location, query, "", receiver, slot);
		}
		
		virtual Weather::DataPoint *create_conditions(Weather::Location *location) = 0;
		virtual Weather::DataBlock *create_dailyForecast(Weather::Location *location) = 0;
		
	public slots:
		virtual void download(Weather::Location *location) = 0;
		void stopJobs(Weather::Location *location);
		
		void resetAccessCount() {
			setAccessCount(0);
			QTimer::singleShot(QDateTime::currentDateTime().msecsTo(QDateTime(QDate::currentDate().addDays(1))), this, SLOT(resetAccessCount()));
		}
		
		void resetAccessMinuteCount() {
			setAccessMinuteCount(0);
			QTimer::singleShot(60 * 1000, this, SLOT(resetAccessMinuteCount()));
		}
		
	signals:
		void refreshed();
		
	protected:
		void json_call(Weather::Location *location, const QString& call, QObject *receiver, const char* slot);
		
		virtual QString prefix() = 0;
		
	private:		
		QMap<KIO::Job *, DownloadJob *> m_jobs;
		
	private slots:
		void process_query(KJob *job);
		void data_downloaded(KIO::Job* job, const QByteArray& data);
		
	#include "weather/service.gen"
	};
	
}

#endif // SERVICE_H
