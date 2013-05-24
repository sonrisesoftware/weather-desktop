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

#include "main.h"

#include <QTextStream>
#include <QVariant>
#include <KDE/KTemporaryFile>
#include <KDE/KActionCollection>
#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <KIO/NetAccess>

#include <QString>

QString readFile(const QString& fileName, QString *error) {
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	return QTextStream(&file).readAll();
}

QString download(const QUrl& url, QString *error) {
	QString text;
	
	/*QString tmpFile;
	if(KIO::NetAccess::download(url, tmpFile, 0))
	{
		QFile file(tmpFile);
		file.open(QIODevice::ReadOnly);
		text = QTextStream(&file).readAll();
		qDebug() << text;
	
		KIO::NetAccess::removeTempFile(tmpFile);
	} else {
		*error = KIO::NetAccess::lastErrorString();
	}*/
	
	KTemporaryFile tmpFile;
	if (tmpFile.open()) {
		KIO::Job* getJob = KIO::file_copy(url, KUrl(tmpFile.fileName()), -1, KIO::Overwrite | KIO::HideProgressInfo);
		if (KIO::NetAccess::synchronousRun(getJob, 0)) {
			text = readFile(tmpFile.fileName(), error);
		} else {
			*error = getJob->errorString();
		}
	} else {
		*error = tmpFile.errorString();
	}		
	
	return text;
}

QVariant getJson(const QVariant& data, const QString& path) {
	QStringList list = path.split('.');
	QVariant result = data;
	
	foreach (const QString& item, list) {
		qDebug() << item << result.typeName();
		if (result.type() == QVariant::List) {
			result = result.toList()[item.toInt()];
		} else if (result.type() == QVariant::Map) {
			result = result.toMap()[item];
		} else {
			qFatal("Invalid type in path: %s", qPrintable(result.type()));
		}
		
		Q_ASSERT(!result.isNull());
	}
	
	return result;
}
