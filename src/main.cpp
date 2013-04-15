/***************************************************************************
 *  Weather Desktop - An advanced weather application for KDE.             *
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
#include "weather-desktop.h"

// KDE headers
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("An advanced weather application for KDE.");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("weather-desktop", 0, ki18n("Weather Desktop"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2013 Michael Spencer"), KLocalizedString(), 0, "spencers1993@gmail.com");
    about.addAuthor( ki18n("Michael Spencer"), KLocalizedString(), "spencers1993@gmail.com");
	about.addCredit(ki18n("Christopher Spencer"), ki18n("Application design"));
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

	// See if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(WeatherDesktop);
    }
    else
	{
		WeatherDesktop *mainWindow = new WeatherDesktop;
		mainWindow->show();
	}
    
    return app.exec();
}
