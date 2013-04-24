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
#include <KDE/KMessageBox>
#include <KDE/KXmlGuiWindow>
#include <KDE/KActionCollection>
#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <KIO/NetAccess>

KMainWindow *kmainwin;

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

void KError(const QString& msg, const QString& error) {
	KError("<b>" + msg + "</b><p><p>");
}

void KError(const QString& msg) {
	KMessageBox::error(kmainwin, msg);
	exit(-1);
}