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


#include "unitylauncher.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>

// /* progress bar count must be float between 0 and 1 (mean from 0.00 to 0.100)*/
// setProperty.insert("progress", double(0.80));
// 
// /* show progress bar */
// setProperty.insert("progress-visible", true);

UnityLauncher::UnityLauncher(const QString& desktopId, QObject* parent): QObject(parent)
{
	setDesktopId(desktopId);
}

UnityLauncher::~UnityLauncher()
{

}

void UnityLauncher::setCount(int count)
{
	QVariantMap properties;
	properties.insert("count", (qint64) count);
	sendSignal(properties);
}

void UnityLauncher::setUrgent(bool urgent)
{
	QVariantMap properties;
	properties.insert("urgent", urgent);
	sendSignal(properties);
}

void UnityLauncher::showCount(bool visible)
{
	QVariantMap properties;
	properties.insert("count-visible", visible);
	sendSignal(properties);
}

void UnityLauncher::sendSignal(QVariantMap properties) {
	/* Create Qt Dbus Signal to send Dbus Message to unity Dbus API
	 s ignal com.canonical.Unity.LauncherEntry.U*pdate (in s app_uri, in a{sv} properties)
	 */
	QDBusMessage signal = QDBusMessage::createSignal(
		"/", ///com/canonical/unity/launcherentry/application://" + desktopId(), /* Path */
		"com.canonical.Unity.LauncherEntry", /* Unity DBus Interface */
		"Update"); /* Update Signal */
	
	
	/* app_uri
	 D esktop ID ex: firefox -> need to be pin**ed in the launcher to see the effect
	 */
	signal << QVariant("application://" + desktopId());
	
	
	/* Pack the properties Map to the signal */
	signal << properties;
	
	qDebug() << "Sending signal to" << desktopId() << signal;
	
	/* Send the signal */
	qDebug() << "Success:" <<QDBusConnection::sessionBus().send(signal);
}

#include "unitylauncher.moc"

