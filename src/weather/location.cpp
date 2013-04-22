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


#include "weather/location.h"
#include <QDateTime>

using namespace Weather;

Location::Location(const QString& name, const QString& location, QObject* parent)
	: QObject(parent)
{
	qDebug() << "New location...";
	// Whenever the location is changed, redownload the weather
	QObject::connect(this, SIGNAL(locationChanged(QString)), this, SLOT(refresh()));
	setName(name);
	setLocation(location);
}

Location::~Location()
{

}

void Location::refresh()
{
	qDebug() << "Refreshing...";
	emit refreshed();
}

#include "weather/location.moc"
