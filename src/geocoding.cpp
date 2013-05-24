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


#include "geocoding.h"

#include "main.h"

#include "qjson/parser.h"
#include <QString>
#include <QByteArray>

Cache *Geocoding::s_geocache = nullptr;
int Geocoding::s_count = 0;

Geocoding::Geocoding(const QString& location, QObject* parent): QObject(parent)
{
	s_count++;
	setLocation(location);
}

Geocoding::~Geocoding()
{
	if (--s_count == 0) {
		delete s_geocache;
		s_geocache = nullptr;
	}
}

void Geocoding::run()
{
	QString error;
	QVariantList list = geocache()->load(location(), &error).toList();
	if (!error.isEmpty()) {
		QString call = "http://open.mapquestapi.com/nominatim/v1/search.php?format=json&q=" + location().replace(' ', '+');
		QString data = download(QUrl(call), &error);
		bool ok;
		QJson::Parser parser;
		list = parser.parse(data.toAscii(), &ok).toList();
		geocache()->save(location(), &error, list);
		if (!ok) {
			error = "Unable to parse JSON response: " + parser.errorString();
			qDebug() << "ERROR:" << error;
			qDebug() << data;
			return;
		}
	}
	
	setCoordinates("");
	
	for (int i = 0; i < list.length(); i++) {
		QVariant item = list[i];
		//qDebug() << "CHECKING:" << getJson(item, "class").toString() << getJson(item, "type").toString();
		//qDebug() << item;
		
		if (getJson(item, "class").toString() == "place" && getJson(item, "type").toString() == "city") {
			setName(getJson(item, "display_name").toString());
			setCoordinates(getJson(item, "lat").toString() + ',' + getJson(item, "lon").toString());
			qDebug() << "FOUND LOCATION:" << name() << coordinates();
			break;
		}
	}
	
	if (list.length() > 0 && coordinates().isEmpty()) {
		QVariant item = list[0];
		
		setName(getJson(item, "display_name").toString());
		setCoordinates(getJson(item, "lat").toString() + ',' + getJson(item, "lon").toString());
		qDebug() << "FOUND LOCATION:" << name() << coordinates();
	}
}


#include "geocoding.moc"