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

#include <KDE/KStandardDirs>
#include <KDE/KCmdLineArgs>
#include <KDE/KAboutData>

#define RESOURCE(file) QUrl::fromLocalFile(KStandardDirs::locate("data", 	\
		KCmdLineArgs::aboutData()->appName() + QString("/") + file))



#define PROPERTY(type, name, reader, writer)									\
public:																			\
	Q_PROPERTY(type name READ reader WRITE writer NOTIFY name ## Changed)		\
																				\
	type reader() const {														\
		return m_ ## name;														\
	}																			\
																				\
public Q_SLOTS:																	\
	void writer(type name) {													\
		m_ ## name = name;														\
		emit name ## Changed(name);												\
	}																			\
																				\
private:																		\
	type m_ ## name;															\
																				\
Q_SIGNALS:																		\
	void name ## Changed(type name);



#define CUSTOM_PROPERTY(type, name, reader, writer)								\
public:																			\
	Q_PROPERTY(type name READ reader WRITE writer NOTIFY name ## Changed)		\
																				\
	type reader() const {														\
		return m_ ## name;														\
	}																			\
																				\
public slots:																	\
	void writer(type name);														\
																				\
private:																		\
	type m_ ## name;															\
																				\
signals:																		\
	void name ## Changed(type name);


	
#define R_PROPERTY(type, name, reader)							\
public:															\
	Q_PROPERTY(type name READ reader)							\
																\
	type reader() const {										\
		return m_ ## name;										\
	}															\
																\
protected:														\
	type m_ ## name;											\


#define P_PROPERTY(type, name, reader, writer)									\
public:																			\
	Q_PROPERTY(type name READ reader NOTIFY name ## Changed)					\
																				\
	type reader() const {														\
		return m_ ## name;														\
	}																			\
																				\
protected slots:																\
	void writer(type name) {													\
		m_ ## name = name;														\
		emit name ## Changed(name);												\
	}																			\
																				\
private:																		\
	type m_ ## name;															\
																				\
signals:																		\
	void name ## Changed(type name);
	
#define CUSTOM_P_PROPERTY(type, name, reader, writer)							\
public:																			\
	Q_PROPERTY(type name READ reader NOTIFY name ## Changed)					\
																				\
	type reader() const {														\
		return m_ ## name;														\
	}																			\
																				\
protected slots:																\
	void writer(type name);														\
																				\
private:																		\
	type m_ ## name;															\
																				\
signals:																		\
	void name ## Changed(type name);


#define STATIC_PROPERTY(type, name, reader, writer)				\
public:															\
																\
	static type reader() {										\
		return m_ ## name;										\
	}															\
																\
	static void writer(type name) {								\
		m_ ## name = name;										\
	}															\
																\
private:														\
	static type m_ ## name;



#define CUSTOM_STATIC_PROPERTY(type, name, reader, writer)		\
public:															\
																\
	static type reader() {										\
		return m_ ## name;										\
	}															\
																\
	static void writer(type name);								\
																\
private:														\
	static type m_ ## name;

#endif