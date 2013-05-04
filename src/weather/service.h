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

#include <KDE/KUrl>
#include <KIO/TransferJob>
#include <KIO/Job>

namespace Weather
{
	class Location;
	class Conditions;
	
	enum Provider {
		WorldWeatherOnline,
		Wunderground
	};
	
	class SlotObject: public QObject {
		Q_OBJECT
		
	public:
		SlotObject(QObject *reciever, const char *slot) {
			QObject::connect(this, SIGNAL(data(QString,QVariantMap)), reciever, slot);
		}
		
		void emit_signal(QString error, QVariantMap map) {
			emit data(error, map);
		}
		
	signals:
		void data(QString error, QVariantMap data);
	};

	class Service : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged)
		Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged)

	public:
		explicit Service(Location* location);
		virtual ~Service();

		virtual void json_query(const QString& query, const QString& params, QObject *reciever, const char* slot) = 0;
		
		inline void json_query(const QString& query, QObject *reciever, const char* slot) {
			json_query(query, "", reciever, slot);
		}
		
		virtual Weather::Conditions *create_conditions() = 0;
		
		static Service *create(Location *location);
		static void setWeatherProvider(Weather::Provider provider);
		static void setAPIKey(const QString& apiKey) { m_apiKey = apiKey; }
		static Weather::Provider weatherProvider() { return m_provider; }
		static QString apiKey() { return m_apiKey; }
		
	public slots:
		virtual void refresh() = 0;
		
	signals:
		void refreshed();
		
	protected:
		void json_call(const QString& call, QObject *reciever, const char* slot);
		
		virtual QString prefix() = 0;
		
		virtual QString internalLocation() = 0;
		
	private:
		static Weather::Provider m_provider;
		static QString m_apiKey;
		
		QMap<KIO::Job *, SlotObject *> m_slots;
		
	private slots:
		void process_query(KIO::Job *job, const QByteArray& data);
		
	#include "weather/service.gen"
	};
	
}

#endif // SERVICE_H
