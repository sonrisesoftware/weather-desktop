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

#include "weather-desktop.h"

#include "main.h"
#include "application.h"
#include "weather/service.h"
#include "cache.h"
#include "settings.h"

#include <QGraphicsObject>
#include <QDeclarativeEngine>
#include <QDeclarativeProperty>
#include <QDeclarativeContext>
#include <QtDeclarative>

#include <KDE/KApplication>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KMenuBar>
#include <KDE/KStatusBar>
#include <KDE/KInputDialog>
#include <KDE/KConfigDialog>
#include <KDE/KHelpMenu>
#include <KDE/KToggleFullScreenAction>
#include <Plasma/Dialog>
#include <KMessageBox>

WeatherDesktop::WeatherDesktop()
	: KXmlGuiWindow()
{	
	setupActions();
	
	setupGUI();
	setupMenu();
	loadSettings();
	
	if (Settings::firstRun() || (locations().length() == 0 && Weather::Location::cache()->recent().length() == 0)) {
		initialSetup();
	} else if (locations().length() > 0) {
		setCurrentLocation((Weather::Location *) locations()[0]);
	} else if(Weather::Location::cache()->recent().length() > 0) {
		setLocation(Weather::Location::cache()->recent()[0]);
	} else {
		setLocation("St. Louis, MO");
	}
	
	m_view = new QDeclarativeView(this);
	m_view->rootContext()->setContextProperty("WeatherApp", this);
	m_view->setStyleSheet("background-color: transparent;");
	m_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
	
	Application::setupDeclarativeBindings(m_view->engine());
	QObject::connect(m_view->engine(), SIGNAL(quit()), kapp, SLOT(quit()));
	
	m_view->setSource(RESOURCE("qml/main.qml"));
	
	Q_ASSERT(m_view->errors().length() == 0); // Check for errors in the qml file
	
	// Bind the minimum size
	QDeclarativeProperty(m_view->rootObject(), "implicitWidth").connectNotifySignal(this, SLOT(onImplicitWidthChanged()));
	QDeclarativeProperty(m_view->rootObject(), "implicitHeight").connectNotifySignal(this, SLOT(onImplicitHeightChanged()));
	onImplicitWidthChanged();
	onImplicitHeightChanged();
	
	setCentralWidget(m_view);
	
	//menuBar()->setHidden(false); // For debugging only!!!
	menuBar()->setHidden(true);
	statusBar()->setHidden(true);
	
	Application::setWindow(this);
}

WeatherDesktop::~WeatherDesktop()
{
	saveSettings();
}

void WeatherDesktop::setupActions()
{
	KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
	KStandardAction::preferences(this, SLOT(showSettingsDialog()), actionCollection());
	KStandardAction::fullScreen(this, SLOT(setFullScreen(bool)), this, actionCollection());
}

void WeatherDesktop::onImplicitWidthChanged()
{
	m_view->setMinimumWidth(m_view->rootObject()->property("implicitWidth").toInt());
}

void WeatherDesktop::onImplicitHeightChanged()
{
	m_view->setMinimumHeight(m_view->rootObject()->property("implicitHeight").toInt());
}

void WeatherDesktop::loadSettings()
{
	QStringList list = Settings::accessCount().split(':');
	QDate current = QDateTime::currentDateTimeUtc().date();
	QDate lastUsed = QDate::fromString(list[0]);
	
	if (current == lastUsed) {
		App->service()->setAccessCount(list[1].toInt() + App->service()->accessCount());
		qDebug() << "Loading access count:" << App->service()->accessCount();
	}
	
	// FIXME!!!! Load all the unit types
	if (Settings::units() == Settings::EnumUnits::English) {
		Weather::Location::setUnits(Weather::Units::English);
	} else if (Settings::units() == Settings::EnumUnits::Metric) {
		Weather::Location::setUnits(Weather::Units::Metric);
	} else {
		qFatal("Invalid units!");
	}
	
	// MUST BE LAST IN FUNCTION!!!
	foreach(const QString& str, Settings::locations()) {
		QStringList list = str.split(':');
		Q_ASSERT(list.length() == 2);
		addLocation(list[0], list[1]);
	}
}

void WeatherDesktop::saveSettings()
{
	QStringList list;
	foreach(QObject *obj, locations()) {
		Weather::Location *location = (Weather::Location *) obj;
		if (location->location().isEmpty()) continue;
		list.append(location->name() + ':' + location->location());
	}
	Settings::setLocations(list);
	
	qDebug() << "Saving access count:" << QDateTime::currentDateTimeUtc().date().toString() + ':' + QString::number(App->service()->accessCount());
	Settings::setAccessCount(QDateTime::currentDateTimeUtc().date().toString() + ':' + QString::number(App->service()->accessCount()));
	
	// FIXME!!!! Save all the unit types
	if (Weather::Location::units().system() == Weather::Units::English) {
		Settings::setUnits(Settings::EnumUnits::English);
	} else if (Weather::Location::units().system() == Weather::Units::Metric) {
		Settings::setUnits(Settings::EnumUnits::Metric);
	} else {
		qFatal("Invalid units!");
	}

	Settings::setFirstRun(false);
	
	Settings::self()->writeConfig();
}

void WeatherDesktop::setFullScreen(bool fullScreen)
{
	KToggleFullScreenAction::setFullScreen(this, fullScreen);
}


void WeatherDesktop::setupMenu()
{
	m_menu = new KMenu(this);	
	
	m_menu->addAction(actionCollection()->action(KStandardAction::name(KStandardAction::Quit)));
	m_menu->addAction(actionCollection()->action(KStandardAction::name(KStandardAction::FullScreen)));
	m_menu->addSeparator();
	m_menu->addAction(actionCollection()->action(KStandardAction::name(KStandardAction::Preferences)));
	m_menu->addSeparator();
	KHelpMenu* helpMenu = new KHelpMenu(m_menu, KCmdLineArgs::aboutData(), false, actionCollection());
	m_menu->addMenu(helpMenu->menu());
}


void WeatherDesktop::showMenu(int x, int y)
{
	m_menu->popup(m_view->mapToGlobal(QPoint(x, y)));
}

void WeatherDesktop::showError(const QString& error)
{
	KMessageBox::error(this, error);
}

void WeatherDesktop::showSettingsDialog()
{
	// An instance of your dialog could be already created and could be
	// cached, in which case you want to display the cached dialog 
	// instead of creating another one
	if (KConfigDialog::showDialog("settings"))
		return; 
	
	// KConfigDialog didn't find an instance of this dialog, so lets
	// create it : 
	KConfigDialog* dialog = new KConfigDialog(this, "settings", Settings::self());
	dialog->setFaceType(KPageDialog::List);
	dialog->setModal(true);
	
	QWidget *generalPage = new QWidget(dialog);	
	dialog->addPage(generalPage, i18n("General"), "configure", i18n("General Settings")); 
	
	// User edited the configuration - update your local copies of the 
	// configuration data 
	//connect(dialog, SIGNAL(settingsChanged()), 
	//		this, SLOT(updateConfiguration())); 
	
	dialog->show();
}

void WeatherDesktop::updateConfiguration()
{
	
}



Weather::Location *WeatherDesktop::addLocation(const QString& name, const QString& location)
{
	Q_ASSERT(!location.isEmpty());
	Weather::Location *l = new Weather::Location(name, location, this);
	locations().append(l);
	emit locationsChanged(locations());
	setCurrentLocation(l);
	return l;
}

void WeatherDesktop::addCurrentLocation()
{
	if (location(currentLocation()->location()) != nullptr) {
		return;
	}
	
	bool ok;	
	QString name = KInputDialog::getText(i18n("New Location"),
			i18n("Name for '%1':",currentLocation()->location()), 
			currentLocation()->display(), &ok, this);
	
	if (!ok) return;
	
	addLocation(name, currentLocation()->location());
}

void WeatherDesktop::removeCurrentLocation()
{
	Weather::Location *l = location(currentLocation()->location());
	int index = locations().indexOf(l);
	
	if (l == nullptr) return;
	
	locations().removeOne(l);
	emit locationsChanged(locations());
	
	if (locations().length() > 0) {
		setCurrentLocation((Weather::Location *) locations()[index - 1]);
	} else {
		setLocation(l->location());
	}
	
	delete l;
}


Weather::Location* WeatherDesktop::location(QString name)
{
	foreach(QObject *obj, locations()) {
		Weather::Location *location = (Weather::Location *) obj;
		if (location->location() == name)
			return location;
	}
	
	return nullptr;
}

Weather::Location* WeatherDesktop::location(int index)
{
	if (index < locations().length()) {
		return (Weather::Location*) locations()[index];
	} else {
		return nullptr;
	}
}

void WeatherDesktop::setLocation(const QString& location)
{
	if (location.isEmpty()) {
		//setCurrentLocation(autoLocation());
		return;
	} else {
		Weather::Location *l = this->location(location);
		if (l != nullptr) {
			setCurrentLocation(l);
		} else {		
			if (searchLocation() == nullptr) {
				setSearchLocation(new Weather::Location("", location, this));
			} else if (searchLocation()->location() != location) {
				searchLocation()->setLocation(location);
			}
			setCurrentLocation(searchLocation());
		}
	}
}

void WeatherDesktop::initialSetup()
{
	bool ok;	
	QString location = KInputDialog::getText(i18n("Setup Weather Desktop"),
			i18n("Enter your home location:"), 
			QString(), &ok, this);
	
	if (ok) {
		addLocation("Home", location);
	} else {
		setLocation("St. Louis, MO");
	}
	
	QStringList units = {"English", "Metric"};
	QString ans = KInputDialog::getItem(i18n("Setup Weather Desktop"),
			i18n("Select your preferred units:"),
			units, 0, false, &ok, this);
	
	if (ok) {
		if (ans == "English") {
			Weather::Location::setUnits(Weather::Units(Weather::Units::English));
		} else if (ans == "Metric") {
			Weather::Location::setUnits(Weather::Units(Weather::Units::Metric));
		} else {
			qFatal("Invalid units!");
		}
	} else {
		Weather::Location::setUnits(Weather::Units(Weather::Units::English));
	}
}

#include "weather-desktop.moc"
