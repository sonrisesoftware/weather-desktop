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

// application header
#include "main.h"
#include "weather-desktop.h"

#include "application.h"
#include "forecast/datapoint.h"
#include "forecast/datablock.h"
#include "cache.h"
#include "geocoding.h"

// KDE headers
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KMessageBox>
#include <KDE/KLocale>

static const char description[] =
		I18N_NOOP("An advanced, cross-platform weather application.");
		
static const char credits[] =
		I18N_NOOP("Powered by <a href=\"http://forecast.io/\">Forecast.io</a>\nNominatim Search Courtesy of <a href=\"http://www.mapquest.com/\" target=\"_blank\">MapQuest</a>");

static const char version[] = "0.2.3";
Application *App;

int main(int argc, char **argv)
{
	KAboutData about("weather-desktop", 0, ki18nc("@title", "Weather Desktop"),
			version, ki18nc("@title", description), KAboutData::License_GPL_V3, 
			ki18nc("@info", "(C) 2013 Michael Spencer"), ki18nc("@info", credits),
			"https://github.com/iBeliever/weather-desktop" /* Home page */,
			"https://github.com/iBeliever/weather-desktop/issues" /* Reporting bugs */);
	about.addAuthor(ki18nc("@info:credit", "Michael Spencer"),
			ki18nc("@info:credit", "Maintainer, developer, and designer"),
			"spencers1993@gmail.com");
	about.addAuthor(ki18nc("@info:credit", "Christopher Spencer"),
			ki18nc("@info:credit", "Designer"),
			"spencers1993@gmail.com");
	KCmdLineArgs::init(argc, argv, &about);
	
	KCmdLineOptions options;
	KCmdLineArgs::addCmdLineOptions(options);
	Application app;
	App = &app;

	qDebug() << "Debugging is enabled.";
	
	// See if we are starting with session management
	if (app.isSessionRestored())
	{
		RESTORE(WeatherDesktop);
	}
	else
	{
		WeatherDesktop *mainWindow = new WeatherDesktop;
		mainWindow->show();

		// For debugging purposes
		//KMessageBox::informationList(mainWindow, "Command line arguments:", KCmdLineArgs::allArguments());
	}
    
	return app.exec();
}
