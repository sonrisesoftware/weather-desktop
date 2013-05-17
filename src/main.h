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

#ifndef MAIN_H
#define MAIN_H

#include <QDebug>
#include <QUrl>
#include <qglobal.h>

#include <KDE/KStandardDirs>
#include <KDE/KCmdLineArgs>
#include <KDE/KAboutData>
#include <KDE/KMainWindow>

#define DEG	"°"
#define TEMP_F i18n(" °F")
#define TEMP_C i18n(" °C")

#define RESOURCE(file) QUrl::fromLocalFile(KStandardDirs::locate("appdata", file))
		
#define STATIC_PROPERTY(type, name, read, write)							\
public:																		\
	static void write(type name) { s_ ## name = name; }						\
	static type read() { return s_ ## name; }								\
																			\
private:																	\
	static type s_ ## name;
	
#define M_STATIC_PROPERTY(type, name, read, write)							\
public:																		\
	static void write(type name);											\
	static type read() { return s_ ## name; }								\
																			\
private:																	\
	static type s_ ## name;
	
#define P_STATIC_PROPERTY(type, name, read, write)							\
protected:																	\
	static void write(type name) { s_ ## name = name; }						\
public:																		\
	static type read() { return s_ ## name; }								\
																			\
private:																	\
	static type s_ ## name;
		
QString download(const QUrl& url, QString *error);

class Application;

extern Application *App;

#endif
