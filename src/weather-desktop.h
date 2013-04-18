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

#ifndef WEATHER-DESKTOP_H
#define WEATHER-DESKTOP_H

#include <QDeclarativeView>
#include <KDE/KMainWindow>

/**
 * This class serves as the main window for WeatherDesktop.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Michael Spencer <spencers1993@gmail.com>
 * @version 0.1
 */
class WeatherDesktop : public KMainWindow
{
	Q_OBJECT
public:
	/**
	 * Default Constructor
	 */
	WeatherDesktop();

	/**
	 * Default Destructor
	 */
	virtual ~WeatherDesktop();

public slots:
	void onMinimumWidthChanged();
	void onMinimumHeightChanged();
	
private:
	QDeclarativeView *view;
};

#endif // _WEATHER-DESKTOP_H_
