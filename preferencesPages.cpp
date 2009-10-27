/****************************************************************************
**
** Copyright (C) 2008 Colin Willcocks.
** Copyright (C) 2005, 2006, 2007 Uco Mesdag. All rights reserved.
**
** This file is part of "GT10B Fx FloorBoard".
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
**
****************************************************************************/


#include <QtGui>
#include "midiIO.h"
#include "RtMidi.h"
#include "preferencesPages.h"
#include "Preferences.h"

GeneralPage::GeneralPage(QWidget *parent)
	: QWidget(parent)
{
	Preferences *preferences = Preferences::Instance();
	QString dir = preferences->getPreferences("General", "Files", "dir");

	QGroupBox *patchGroup = new QGroupBox(QObject::tr("Patch folder"));

	QLabel *descriptionLabel = new QLabel(QObject::tr("Select the default folder for storing patches."));
	QLabel *dirLabel = new QLabel(QObject::tr("Default patch folder:"));
	QLineEdit *dirEdit = new QLineEdit(dir);
	QPushButton *browseButton = new QPushButton(QObject::tr("Browse"));

	connect(browseButton, SIGNAL(clicked()), this, SLOT(browseDir()));

	this->dirEdit = dirEdit;

	QHBoxLayout *dirEditLayout = new QHBoxLayout;
	dirEditLayout->addWidget(dirEdit);
	dirEditLayout->addWidget(browseButton);

	QVBoxLayout *dirLayout = new QVBoxLayout;
	dirLayout->addWidget(descriptionLabel);
	dirLayout->addSpacing(12);
	dirLayout->addWidget(dirLabel);
	dirLayout->addLayout(dirEditLayout);

	QVBoxLayout *patchLayout = new QVBoxLayout;
	patchLayout->addLayout(dirLayout);
	patchGroup->setLayout(patchLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(patchGroup);
	mainLayout->addStretch(1);
	setLayout(mainLayout);
};

MidiPage::MidiPage(QWidget *parent)
	: QWidget(parent)
{
	bool ok; int id;
	midiIO *midi = new midiIO();
	Preferences *preferences = Preferences::Instance();
	QString midiInDevice = preferences->getPreferences("Midi", "MidiIn", "device");
	QString midiOutDevice = preferences->getPreferences("Midi", "MidiOut", "device");
	QString dBugScreen = preferences->getPreferences("Midi", "DBug", "bool");
	QString midiTimeSet = preferences->getPreferences("Midi", "Time", "set");
	QString midiDelaySet = preferences->getPreferences("Midi", "Delay", "set");

	int midiInDeviceID = midiInDevice.toInt(&ok, 10);
	int midiOutDeviceID = midiOutDevice.toInt(&ok, 10);
	QList<QString> midiInDevices = midi->getMidiInDevices();
	QList<QString> midiOutDevices = midi->getMidiOutDevices();
	
	QGroupBox *midiGroup = new QGroupBox(QObject::tr("Midi settings"));

	QLabel *mididescriptionLabel = new QLabel(QObject::tr("Select your midi in and out device."));
	QLabel *midiInLabel = new QLabel(QObject::tr("Midi in:"));
	QLabel *midiOutLabel = new QLabel(QObject::tr("Midi out:"));

	QComboBox *midiInCombo = new QComboBox;
	this->midiInCombo = midiInCombo;
	midiInCombo->addItem(QObject::tr("Select midi-in device"));
	id = 0;
	for (QList<QString>::iterator dev = midiInDevices.begin(); dev != midiInDevices.end(); ++dev)
    {
		QString str(*dev);
		midiInCombo->addItem(str.toAscii().data());
		id++;
    };
	if(!midiInDevice.isEmpty())
	{
		midiInCombo->setCurrentIndex(midiInDeviceID + 1); // +1 because there is a default entry at 0
	};
	if ( midiInDevices.contains("BOSS GT-10B") )
  {
    int inputDevice = midiInDevices.indexOf("BOSS GT-10B") + 1;
    midiInCombo->setCurrentIndex(inputDevice);
	};
	
	QComboBox *midiOutCombo = new QComboBox;
	this->midiOutCombo = midiOutCombo;
	midiOutCombo->addItem(QObject::tr("Select midi-out device"));
	id = 0;
	for (QList<QString>::iterator dev = midiOutDevices.begin(); dev != midiOutDevices.end(); ++dev)
    {
		QString str(*dev);
		midiOutCombo->addItem(str.toAscii().data());
		id++;
    };
	if(!midiOutDevice.isEmpty())
	{
		midiOutCombo->setCurrentIndex(midiOutDeviceID + 1); // +1 because there is a default entry at 0
	};
	if ( midiOutDevices.contains("BOSS GT-10B") )
  {
    int outputDevice = midiOutDevices.indexOf("BOSS GT-10B") + 1;
    midiOutCombo->setCurrentIndex(outputDevice);
  }; 

	QVBoxLayout *midiLabelLayout = new QVBoxLayout;
	midiLabelLayout->addWidget(midiInLabel);
	midiLabelLayout->addWidget(midiOutLabel);

	QVBoxLayout *midiComboLayout = new QVBoxLayout;
	midiComboLayout->addWidget(midiInCombo);
	midiComboLayout->addWidget(midiOutCombo);

	QHBoxLayout *midiSelectLayout = new QHBoxLayout;
	midiSelectLayout->addLayout(midiLabelLayout);
	midiSelectLayout->addLayout(midiComboLayout);
	
	QVBoxLayout *midiDevLayout = new QVBoxLayout;
	midiDevLayout->addWidget(mididescriptionLabel);
	midiDevLayout->addSpacing(12);
	midiDevLayout->addLayout(midiSelectLayout);

	QVBoxLayout *midiLayout = new QVBoxLayout;
	midiLayout->addLayout(midiDevLayout);
	midiGroup->setLayout(midiLayout);



	QGroupBox *dBugScreenGroup = new QGroupBox(QObject::tr("Advanced settings"));

	QLabel *dBugDescriptionLabel = new QLabel(QObject::tr("Debug mode."));
	//QLabel *midiTimeDescriptionLabel = new QLabel(tr("Data receive wait time."));
	//QLabel *midiDelayDescriptionLabel = new QLabel(tr("Realtime edit send rate."));

	QCheckBox *dBugCheckBox = new QCheckBox(QObject::tr("deBug Mode"));
	QSpinBox *midiTimeSpinBox = new QSpinBox;
	QSpinBox *midiDelaySpinBox = new QSpinBox;

	this->dBugCheckBox = dBugCheckBox;
	if(dBugScreen=="true")
	{
		dBugCheckBox->setChecked(true);
	};
	
	this->midiTimeSpinBox = midiTimeSpinBox;
	const int tempDataWrite = preferences->getPreferences("Midi", "Time", "set").toInt(&ok, 10);
	midiTimeSpinBox->setValue(tempDataWrite);
	midiTimeSpinBox->setRange(1, 99);
	midiTimeSpinBox->setPrefix("= ");
	midiTimeSpinBox->setSuffix(QObject::tr("0 millisecond"));

	this->midiDelaySpinBox = midiDelaySpinBox;
	const int minWait = preferences->getPreferences("Midi", "Delay", "set").toInt(&ok, 10);
	midiDelaySpinBox->setValue(minWait);
	midiDelaySpinBox->setRange(1, 20);
	midiDelaySpinBox->setPrefix("= ");
	midiDelaySpinBox->setSuffix(QObject::tr(" times/second"));


	QVBoxLayout *dBugLabelLayout = new QVBoxLayout;
	dBugLabelLayout->addWidget(dBugDescriptionLabel);
	//dBugLabelLayout->addWidget(midiTimeDescriptionLabel);
	//dBugLabelLayout->addWidget(midiDelayDescriptionLabel);

	QVBoxLayout *dBugTimeBoxLayout = new QVBoxLayout;
	dBugTimeBoxLayout->addWidget(dBugCheckBox);
	//dBugTimeBoxLayout->addWidget(midiTimeSpinBox);
	//dBugTimeBoxLayout->addWidget(midiDelaySpinBox);

	QHBoxLayout *dBugSelectLayout = new QHBoxLayout;
	dBugSelectLayout->addLayout(dBugLabelLayout);
	dBugSelectLayout->addLayout(dBugTimeBoxLayout);

	QVBoxLayout *dBugScreenLayout = new QVBoxLayout;
	dBugScreenLayout->addWidget(dBugDescriptionLabel);

	dBugScreenLayout->addLayout(dBugSelectLayout);

	dBugScreenGroup->setLayout(dBugScreenLayout);

	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(midiGroup);
	mainLayout->addWidget(dBugScreenGroup);
	mainLayout->addStretch(1);
	setLayout(mainLayout);
};

WindowPage::WindowPage(QWidget *parent)
	: QWidget(parent)
{
	Preferences *preferences = Preferences::Instance();
	QString windowRestore = preferences->getPreferences("Window", "Restore", "window");
	QString sidepanelRestore = preferences->getPreferences("Window", "Restore", "sidepanel");
	QString splashScreen = preferences->getPreferences("Window", "Splash", "bool");

	QGroupBox *windowGroup = new QGroupBox(QObject::tr("Window settings"));

	QLabel *restoreDescriptionLabel = new QLabel(QObject::tr("Select if you want the window position to be saved on exit."));
	QCheckBox *windowCheckBox = new QCheckBox(QObject::tr("Restore window"));
	QCheckBox *sidepanelCheckBox = new QCheckBox(QObject::tr("Restore sidepanel"));
	this->windowCheckBox = windowCheckBox;
	this->sidepanelCheckBox = sidepanelCheckBox;

	if(windowRestore=="true")
	{
		windowCheckBox->setChecked(true);
	};
	if(sidepanelRestore=="true")
	{
		sidepanelCheckBox->setChecked(true);
	};

	QVBoxLayout *restoreLayout = new QVBoxLayout;
	restoreLayout->addWidget(restoreDescriptionLabel);
	restoreLayout->addSpacing(12);
	restoreLayout->addWidget(windowCheckBox);
	restoreLayout->addWidget(sidepanelCheckBox);
	
	QVBoxLayout *windowLayout = new QVBoxLayout;
	windowLayout->addLayout(restoreLayout);
	windowGroup->setLayout(windowLayout);

	QGroupBox *splashScreenGroup = new QGroupBox(QObject::tr("Show splash screen"));

	QLabel *splashDescriptionLabel = new QLabel(QObject::tr("Disable or enable the splash screen."));
	QCheckBox *splashCheckBox = new QCheckBox(QObject::tr("Splash screen"));
	this->splashCheckBox = splashCheckBox;

	if(splashScreen=="true")
	{
		splashCheckBox->setChecked(true);
	};

	QVBoxLayout *splashLayout = new QVBoxLayout;
	splashLayout->addWidget(splashDescriptionLabel);
	splashLayout->addSpacing(12);
	splashLayout->addWidget(splashCheckBox);

	QVBoxLayout *splashScreenLayout = new QVBoxLayout;
	splashScreenLayout->addLayout(splashLayout);
	splashScreenGroup->setLayout(splashScreenLayout);

	

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(windowGroup);
	mainLayout->addWidget(splashScreenGroup);
	
	mainLayout->addStretch(1);
	setLayout(mainLayout);
};

LanguagePage::LanguagePage(QWidget *parent)
	: QWidget(parent)
{
	Preferences *preferences = Preferences::Instance();
	QString lang = preferences->getPreferences("Language", "Locale", "select");
	bool ok;
	int choice = lang.toInt(&ok, 16);
  
	QGroupBox *languageGroup = new QGroupBox(QObject::tr("Language Selection"));
	
	QRadioButton *englishButton = new QRadioButton(QObject::tr("English"));
	this->englishButton = englishButton;
  this->frenchButton = new QRadioButton(QObject::tr("French"));
  this->germanButton = new QRadioButton(QObject::tr("German"));
  this->chineseButton = new QRadioButton(QObject::tr("Chinese (simplified)"));
  if (choice == 3) {chineseButton->setChecked(true); }
  else if (choice == 2) {germanButton->setChecked(true); }
  else if (choice == 1) {frenchButton->setChecked(true); }
  else {englishButton->setChecked(true); };
 
	QVBoxLayout *languageLayout = new QVBoxLayout;
	languageLayout->addWidget(englishButton);
	languageLayout->addWidget(frenchButton);
	languageLayout->addWidget(germanButton);
	languageLayout->addWidget(chineseButton);
	
  languageGroup->setLayout(languageLayout);
  
  QLabel *note = new QLabel(QObject::tr("Changes take effect on next startup" ));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(languageGroup);
	languageLayout->addSpacing(12);
	mainLayout->addStretch(1);
	mainLayout->addWidget(note);
	setLayout(mainLayout);
};

void GeneralPage::browseDir()
{
	QString dirName = QFileDialog::getExistingDirectory(this, QObject::tr("Select the default folder for storing patches."),
		this->dirEdit->text(),
        QFileDialog::ShowDirsOnly);
	if(!dirName.isEmpty())
	{
		this->dirEdit->setText(dirName);
	};
};

