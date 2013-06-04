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



#ifndef WEATHER_DATABLOCK_H
#define WEATHER_DATABLOCK_H

#include "weather/datapoint.h"
#include "weather/managedlist.h"

#include <QObject>
#include <QIcon>
#include <QList>
#include <QDebug>

namespace Weather {
	
	class Location;

	class DataBlock : public ManagedList
	{
		Q_OBJECT
		
		Q_PROPERTY(Weather::Location *location READ location NOTIFY locationChanged);
		
		Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged);
		Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged);
		
	public:
		explicit DataBlock(Weather::Location *location);
		virtual ~DataBlock();
		
		const DataPoint *operator[](int index) {
			return (DataPoint *) items()[index];
		}
		
		Q_INVOKABLE Weather::DataPoint *at(int index) {
			//qDebug() << "AT:" << index << m_items.length();
			if (index >= items().length()) {
				return nullptr;
			}
			return (DataPoint *) items().at(index);
		}
		
	#include "weather/datablock.gen"
	};

}

#endif // WEATHER_DATABLOCK_H
