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


#ifndef WUNDERGROUND_H
#define WUNDERGROUND_H

#include "weather/service.h"

#include <KDE/KIcon>

namespace Wunderground {
	class Wunderground : public Weather::Service
	{
		Q_OBJECT

	public:
		explicit Wunderground(QObject *parent = 0);
		virtual ~Wunderground();
		
		virtual void json_query(Weather::Location *location, const QString& query, const QString& params, QObject *receiver, const char* slot);
		virtual Weather::Conditions *create_conditions(Weather::Location *location);
	
		static void init();
		static KIcon icon(const QString &weather, const bool day);
		
	public slots:
		virtual void download(Weather::Location *location);
		
	protected:
		QString internalLocation(Weather::Location *location);
		virtual QString prefix();
		
	private slots:
		void onConditionsDownloaded(Weather::Location *location, QString error, const QVariantMap& data);
		
	private:
		static QMap<QString, KIcon> icons_day;
		static QMap<QString, KIcon> icons_night;
		static bool s_initialized;
		
	#include "wunderground/wunderground.gen"
	};
}

#endif // WUNDERGROUND_H
