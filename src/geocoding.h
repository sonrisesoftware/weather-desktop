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

#ifndef GEOCODING_H
#define GEOCODING_H

#include "cache.h"

#include <QObject>
#include <QString>
#include <KStandardDirs>

class Geocoding : public QObject
{
	Q_OBJECT
	
	Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
	Q_PROPERTY(QString name READ name NOTIFY nameChanged)
	Q_PROPERTY(QString coordinates READ coordinates NOTIFY coordinatesChanged)

public:
	explicit Geocoding(const QString& location, QObject* parent = 0);
	virtual ~Geocoding();
	
	static Cache *geocache() {
		if (s_geocache == nullptr) {
			s_geocache = new Cache(KStandardDirs::locateLocal("appdata", "geocache"));
			s_geocache->setMaxTime(0);
		}
		
		return s_geocache;
	}	

public slots:	
	void run();
	
private:
	static Cache *s_geocache;
	static int s_count;
	
#include "geocoding.gen"
};

#endif // GEOCODING_H
