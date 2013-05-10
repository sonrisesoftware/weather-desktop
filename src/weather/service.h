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
#include <QByteArray>
#include <qjson/parser.h>

#include <KDE/KUrl>
#include <KIO/TransferJob>
#include <KIO/Job>
#include <KLocalizedString>

namespace Weather
{
	class Location;
	class Conditions;
	
	enum Provider {
		WorldWeatherOnline,
		Wunderground
	};
	
	class DownloadJob: public QObject {
		Q_OBJECT
		
	public:
		DownloadJob(QObject *receiver, const char *slot) {
			QObject::connect(this, SIGNAL(data(QString,QVariantMap)), receiver, slot);
		}
		
		void emit_signal(QString error, QVariantMap map) {
			emit data(error, map);
		}
		
		QByteArray m_data;
		
	signals:
		void data(QString error, QVariantMap data);
	};

	class Service : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)
		Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
		
		M_STATIC_PROPERTY(Weather::Provider, provider, provider, setProvider)
		STATIC_PROPERTY(QString, apiKey, apiKey, setAPIKey)
		STATIC_PROPERTY(int, maxCalls, maxCalls, setMaxCalls)
		STATIC_PROPERTY(int, accessCount, accessCount, setAccessCount)

	public:
		explicit Service(Location* location);
		virtual ~Service();

		virtual void json_query(const QString& query, const QString& params, QObject *receiver, const char* slot) = 0;
		
		inline void json_query(const QString& query, QObject *receiver, const char* slot) {
			json_query(query, "", receiver, slot);
		}
		
		virtual Weather::Conditions *create_conditions() = 0;
		
		static Service *create(Location *location);
		
		QVariantMap data(const QString& type);
		
	public slots:
		virtual void refresh() = 0;
		void stopJobs();
		
	signals:
		void refreshed();
		
	protected:
		void json_call(const QString& call, QObject *receiver, const char* slot);
		
		virtual QString prefix() = 0;
		
		virtual QString internalLocation() = 0;
		
	private:		
		QMap<KIO::Job *, DownloadJob *> m_jobs;
		
	private slots:
		void process_query(KJob *job);
		void data_downloaded(KIO::Job* job, const QByteArray& data);
		
	#include "weather/service.gen"
	};
	
}

#endif // SERVICE_H
