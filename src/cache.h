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
 
#ifndef CACHE_H
#define CACHE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>
 
#define NO_DATA 		"No data in cache!"
#define INVALID_JSON 	"Unable to parse JSON data: "
#define OUTDATED_DATA	"Data is outdated!"
 
class Cache: QObject {
	Q_OBJECT
	
	Q_PROPERTY(QString directory READ directory NOTIFY directoryChanged)
	Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged)
	Q_PROPERTY(QStringList recent READ recent NOTIFY recentChanged)
	Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
	Q_PROPERTY(long maxTime READ maxTime WRITE setMaxTime NOTIFY maxTimeChanged)
	
public:
	explicit Cache(const QString& directory, QObject *parent = 0);
	virtual ~Cache();
	
	QVariant load(QString, QString *error);
	
	void save(QString name, QString *error, QVariant data);
	
	//bool is_current(QString name);

	void remove(QString name);
	
	QDateTime lastUpdated(QString name, QString *error);
	
	bool remove();

#include "cache.gen"
};

#endif // CACHE_H
