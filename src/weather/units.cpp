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


#include "weather/units.h"

using namespace Weather;

Units::Units(Weather::Units::System system, QObject* parent): QObject(parent)
{
	QObject::connect(this, SIGNAL(systemChanged(Weather::Units::System)), this, SLOT(onSystemChanged()));
	
	setSystem(system);	
	
	QObject::connect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
}

Units::Units(const Units& other)
{
	setSystem(other.system());
	setTemp(other.temp());
	setPressure(other.pressure());
	setSpeed(other.speed());
	setLongDistance(other.longDistance());
	setShortDistance(other.shortDistance());
	
	QObject::connect(this, SIGNAL(systemChanged(Weather::Units::System)), this, SLOT(onSystemChanged()));	
	QObject::connect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
}

Units::~Units()
{

}

void Units::onSystemChanged()
{
	// This is so that unitsChanged is only emitted once
	QObject::disconnect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	
	if (system() == Units::English) {
		setTemp(Units::Fahrenheit);
		setPressure(Units::InchesMercury);
		setSpeed(Units::MilesPerHour);
		setLongDistance(Units::Miles);
		setShortDistance(Units::Feet);
	} else {
		setTemp(Units::Celsius);
		setPressure(Units::Millibars);
		setSpeed(Units::MetersPerSecond);
		setLongDistance(Units::Kilometers);
		setShortDistance(Units::Meters);
	}
	
	// This is so that unitsChanged is only emitted once (see start of function)
	QObject::connect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	emit unitsChanged();
}

Units& Units::operator=(const Units& units)
{
	// This is so that unitsChanged is only emitted once
	QObject::disconnect(this, SIGNAL(systemChanged(Weather::Units::System)), this, SLOT(onSystemChanged()));
	QObject::disconnect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::disconnect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	
	setSystem(units.system());
	setTemp(units.temp());
	setPressure(units.pressure());
	setSpeed(units.speed());
	setLongDistance(units.longDistance());
	setShortDistance(units.shortDistance());
	
	// This is so that unitsChanged is only emitted once (see start of function)
	QObject::connect(this, SIGNAL(systemChanged(Weather::Units::System)), this, SLOT(onSystemChanged()));
	QObject::connect(this, SIGNAL(tempChanged(Weather::Units::Temperature)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(pressureChanged(Weather::Units::Pressure)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(speedChanged(Weather::Units::Speed)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(longDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	QObject::connect(this, SIGNAL(shortDistanceChanged(Weather::Units::Distance)), this, SIGNAL(unitsChanged()));
	emit unitsChanged();
	
	return *this;
}


#include "weather/units.moc"
