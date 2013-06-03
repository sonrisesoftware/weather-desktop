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


#ifndef WEATHER_MANAGEDLIST_H
#define WEATHER_MANAGEDLIST_H

#include <QObject>


namespace Weather {
	
	class ManagedList : public QObject
	{
		Q_OBJECT
		
		Q_PROPERTY(QList<QObject*> items READ items NOTIFY itemsChanged);
		Q_PROPERTY(int length READ length NOTIFY lengthChanged);
	
	public:
		explicit ManagedList(QObject* parent = 0);
		virtual ~ManagedList();
		
		const QObject *operator[](int index) {
			return items()[index];
		}
		
		Q_INVOKABLE QObject *at(int index) {
			//qDebug() << "AT:" << index << m_items.length();
			if (index >= items().length()) {
				return nullptr;
			}
			return items().at(index);
		}
		
	public slots:
		virtual void refresh() = 0;
		
	signals:
		void refreshed();

	#include "weather/managedlist.gen"
	};

}

#endif // WEATHER_MANAGEDLIST_H
