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


#include "cache.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <qjson/serializer.h>
#include <qjson/parser.h>

QByteArray read_file(QString name, QString *error) {	
	QFile file(name);
	if (!file.open(QFile::ReadOnly)) {
		qDebug() << "Unable to open for reading:" << name;
		*error = "I/O Error: " + file.errorString() + ": " + name;
		return QByteArray();
	}
	QByteArray data = file.readAll();
	
	if (file.error() != QFile::NoError) {
		qDebug() << "Unable to read file:" << name;
		*error = "I/O Error: " + file.errorString() + ": " + name;
		return QByteArray();
	}
	
	file.close();
	
	return data;
}

void write_file(QString name, QString *error, QByteArray data) {
	QFile file(name);
	
	if (!file.open(QFile::WriteOnly)) {
		qDebug() << "Unable to open for writing:" << name;
		*error = "I/O Error: " + file.errorString() + ": " + name;
		return;
	}
	
	file.write(data);
	file.close();
	if (file.error() != QFile::NoError) {
		qDebug() << "Unable to write to file:" << name;
		*error = "I/O Error: " + file.errorString();
	}
}

Cache::Cache(const QString& directory, QObject *parent): QObject(parent)
{
	QDir dir(directory);
	if (!dir.exists())
		QDir().mkpath(directory);
	
	if (QFile(directory + "/cache-info").exists()) {	
		QString error;	
		QByteArray data = read_file(directory + "/cache-info", &error);
		if (error.isEmpty()) {
			setRecent(QString(data).split('\n'));
			qDebug() << recent();
		} else {
			qFatal("Unable to create cache: %s", qPrintable(error));
		}
	}
	
	setDirectory(directory);
	setSize(10);
	setMaxTime(1000 * 60 * 60); // 1 hr
}

Cache::~Cache() {
	QString error;
	write_file(directory() + "/cache-info", &error, recent().join("\n").toAscii());
	if (!error.isEmpty()) {
		qFatal("Unable to save cache: %s", qPrintable(error));
	}
	
	foreach (QString name, recent()) {
		if (!data().contains(name)) continue;
		
		qDebug() << "Saving cached data:" << name;
		
		QVariantMap map = data()[name].toMap();
		
		QString error; bool ok; QJson::Serializer serializer;
		write_file(directory() + '/' + name.replace('/', '-'), &error, serializer.serialize(map, &ok));
		if (!error.isEmpty()) {
			qWarning() << "Error while saving cache: " + error;;
			continue;
		}
		
		if (!ok) {
			error = INVALID_JSON + serializer.errorMessage();
			qWarning() << "Error while saving cache: " + error;
			continue;
		}
	}
}

QVariant Cache::load(QString name, QString *error)
{
	error->clear();
	
	// If the name is in the cache,
	if (recent().contains(name)) {
		QVariantMap result;
		recent().removeOne(name);
		recent().prepend(name);
		
		// If the data is not loaded,
		if (!data().contains(name)) {
			// Load the data
			QByteArray array = read_file(directory() + '/' + name.replace('/', '-'), error);
			if (!error->isEmpty()) return QVariant();
			
			bool ok;
			QJson::Parser parser;
			result = parser.parse(array, &ok).toMap();
			if (!ok) {
				*error = INVALID_JSON + parser.errorString();
				return QVariant();
			}
			
			this->data()[name] = result;
 		} else {
			result = this->data()[name].toMap();
		}
 		
 		//qDebug() << "Saved:" << result["time"].toDateTime();
		//qDebug() << "Now:" << QDateTime::currentDateTime();
		
		qDebug() << "Data exists in cache:" << name;
 		
		// If the data is current,
		if (result["time"].toDateTime().msecsTo(QDateTime::currentDateTime()) < maxTime()) {
			// Return the data
			return result["data"];
		} else { // Otherwise,	
			// Return no data, with error "Outdated data"
			*error = OUTDATED_DATA;
			return result["data"];
		}
	} else { // Otherwise,
		qDebug() << "Data is not in cache:" << name;
		// Return no data, with error "No data in cache"
		*error = NO_DATA;
		return QVariant();
	}
}

void Cache::save(QString name, QString* error, QVariant data)
{
	error->clear();
	
	// If the name is not in the cache,
	if (!recent().contains(name)) {
		// Remove the oldest item
		if (recent().size() >= size())
			remove(recent().last());
		recent().prepend(name);
	}
	
	// Add a timestamp
	QVariantMap map;
	map["time"] = QDateTime::currentDateTime();
	map["data"] = data;
	
	// Save the data to the internal cache
	this->data()[name] = map;	
	
	recent().removeOne(name);
	recent().prepend(name);
	
	// Write only on quitting...
}

void Cache::remove(QString name)
{
	if (recent().length() <= size())
		return;
	
	recent().removeOne(name);
	data().remove(name);
	if (QFile(directory() + '/' + name.replace('/', '-')).exists()) {
		QFile::remove(directory() + '/' + name.replace('/', '-'));
	}
}


QDateTime Cache::lastUpdated(QString name, QString *error)
{
	
	// If the name is in the cache,
	if (recent().contains(name)) {
		QVariantMap result;
		
		// If the data is not loaded,
		if (!data().contains(name)) {
			// Load the data
			QByteArray array = read_file(directory() + '/' + name.replace('/', '-'), error);
			if (!error->isEmpty()) return QDateTime::currentDateTime();
			
			bool ok;
			QJson::Parser parser;
			result = parser.parse(array, &ok).toMap();
			if (!ok) {
				*error = INVALID_JSON + parser.errorString();
				return QDateTime::currentDateTime();
			}
			
			this->data()[name] = result;
 		} else {
			result = this->data()[name].toMap();
		}
 		
 		//qDebug() << "Saved:" << result["time"].toDateTime();
		//qDebug() << "Now:" << QDateTime::currentDateTime();
 		
		return result["time"].toDateTime();
	} else { // Otherwise,
		// Return no data, with error "No data in cache"
		*error = NO_DATA;
		return QDateTime::currentDateTime();
	}
}


#include "cache.moc"
