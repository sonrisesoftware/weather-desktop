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


#ifndef LOCATION_H
#define LOCATION_H

#include "main.h"

#include <QObject>
#include <QString>
#include <QImage>
#include <QIcon>
#include <QDateTime>
#include <QTimer>

namespace Weather
{
	class Conditions;
	class Service;

	class Location : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		
		Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
		Q_PROPERTY(QString display READ display NOTIFY displayChanged)
		
		Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged)
		Q_PROPERTY(QImage *background READ background WRITE setBackground NOTIFY backgroundChanged)
		
		Q_PROPERTY(int timezone READ timezone NOTIFY timezoneChanged)
		Q_PROPERTY(QTime lastUpdated READ lastUpdated NOTIFY lastUpdatedChanged)
		Q_PROPERTY(bool needsUpdate READ needsUpdate NOTIFY needsUpdateChanged)
		Q_PROPERTY(bool day READ isDay NOTIFY dayChanged)
		
		Q_PROPERTY(Weather::Conditions *conditions READ conditions NOTIFY conditionsChanged)
		Q_PROPERTY(Weather::Service *api READ api NOTIFY apiChanged)
		
		Q_PROPERTY(bool updating READ isUpdated WRITE setUpdating NOTIFY updatingChanged)
		Q_PROPERTY(bool error READ hasError WRITE setError NOTIFY errorChanged)
		Q_PROPERTY(QString errorMessage READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged)

	public:
		explicit Location(const QString& name, const QString& location, QObject* parent = 0);
		explicit Location(QObject *parent = 0);
		virtual ~Location();
		
		Q_INVOKABLE static void refreshAll();
		Q_INVOKABLE static void stopAllRefresh();
		void finishedRefresh();
		
	public slots:
		void refresh();		
		void stopRefresh();
		
	signals:		
		void refreshed();
		
	private:		
		bool m_updating = false;
		static QList<Location *> m_locations;
		
		//QTimer m_updateTimer;
		
	private slots:
		void timeToUpdate();
	
	#include "weather/location.gen"
	};

}

#endif // LOCATION_H
