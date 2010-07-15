/****************************************************************************
**
** Copyright (C) 2007~2010 Colin Willcocks.
** Copyright (C) 2005~2007 Uco Mesdag.
** All rights reserved.
** This file is part of "GT-10 Fx FloorBoard".
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
#include <QWhatsThis>
#include "mainWindow.h"
#include "Preferences.h"
#include "preferencesDialog.h"
#include "statusBarWidget.h"
#include "SysxIO.h"
#include "bulkSaveDialog.h"
#include "bulkLoadDialog.h"
#include "summaryDialog.h"
#include "summaryDialog2.h"
#include "summaryDialogPatchList.h"
#include "summaryDialogSystem.h"
#include "globalVariables.h"


mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent){
        floorBoard *fxsBoard = new floorBoard(this);



        /* Loads the stylesheet for the current platform if present */
        #ifdef Q_OS_WIN
        /* This set the floorboard default style to the "plastique" style,
           as it comes the nearest what the stylesheet uses. */
        //fxsBoard->setStyle(QStyleFactory::create("plastique"));
                if(QFile(":qss/windows.qss").exists())
                {
                        QFile file(":qss/windows.qss");
                        file.open(QFile::ReadOnly);
                        QString styleSheet = QLatin1String(file.readAll());
                        fxsBoard->setStyleSheet(styleSheet);
                };
        #endif

        #ifdef Q_WS_X11
        fxsBoard->setStyle(QStyleFactory::create("plastique"));
                if(QFile(":qss/linux.qss").exists())
                {
                        QFile file(":qss/linux.qss");
                        file.open(QFile::ReadOnly);
                        QString styleSheet = QLatin1String(file.readAll());
                        fxsBoard->setStyleSheet(styleSheet);
                };
        #endif

        #ifdef Q_WS_MAC
        fxsBoard->setStyle(QStyleFactory::create("plastique"));
                if(QFile(":qss/macosx.qss").exists())
                {
                        QFile file(":qss/macosx.qss");
                        file.open(QFile::ReadOnly);
                        QString styleSheet = QLatin1String(file.readAll());
                        fxsBoard->setStyleSheet(styleSheet);
                };
        #endif


        this->setWindowTitle(deviceType + tr(" Fx FloorBoard"));

        this->createActions();
        this->createMenus();
        this->createStatusBar();

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->setMenuBar(menuBar);
        mainLayout->addWidget(fxsBoard);
        mainLayout->addWidget(statusBar);
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);
        setLayout(mainLayout);
        this->statusBar->setWhatsThis("StatusBar<br>midi activity is displayed here<br>and some status messages are displayed.");
        QObject::connect(fxsBoard, SIGNAL( sizeChanged(QSize, QSize) ),
                this, SLOT( updateSize(QSize, QSize) ) );
};

mainWindow::~mainWindow()
{
        Preferences *preferences = Preferences::Instance();
        if(preferences->getPreferences("Window", "Restore", "window")=="true")
        {
                QString posx, width;
                if(preferences->getPreferences("Window", "Restore", "sidepanel")=="true" &&
                        preferences->getPreferences("Window", "Collapsed", "bool")=="true")
                {
                        width = QString::number(this->geometry().width(), 10);
                        posx = QString::number(this->geometry().x(), 10);
                }
                else
                {
                        bool ok;
                        width = preferences->getPreferences("Window", "Size", "minwidth");
                        posx = QString::number(this->geometry().x()+((this->geometry().width()-width.toInt(&ok,10))/2), 10);
                };
                preferences->setPreferences("Window", "Position", "x", posx);
                preferences->setPreferences("Window", "Position", "y", QString::number(this->geometry().y(), 10));
                preferences->setPreferences("Window", "Size", "width", width);
                preferences->setPreferences("Window", "Size", "height", QString::number(this->geometry().height(), 10));
        }
        else
        {
                preferences->setPreferences("Window", "Position", "x", "");
                preferences->setPreferences("Window", "Position", "y", "");
                preferences->setPreferences("Window", "Size", "width", "");
                preferences->setPreferences("Window", "Size", "height", "");
        };
        preferences->savePreferences();
};

void mainWindow::updateSize(QSize floorSize, QSize oldFloorSize)
{
        this->setFixedWidth(floorSize.width());
        int x = this->geometry().x() - ((floorSize.width() - oldFloorSize.width()) / 2);
        int y = this->geometry().y();
        this->setGeometry(x, y, floorSize.width(), this->geometry().height());
};

void mainWindow::createActions()
{
        openAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load Patch File... (*.syx, *.mid, *.gxg *.gxb)"), this);
        openAct->setShortcut(tr("Ctrl+O"));
        openAct->setWhatsThis(tr("Open an existing file"));
        connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

        saveAct = new QAction(QIcon(":/images/filesave.png"), tr("&Save Patch...       (*.syx)"), this);
        saveAct->setShortcut(tr("Ctrl+S"));
        saveAct->setStatusTip(tr("Save the document to disk"));
        saveAct->setWhatsThis(tr("Save the document to disk"));
        connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

        saveAsAct = new QAction(QIcon(":/images/filesave.png"), tr("Save &As Patch...  (*.syx)"), this);
        saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
        saveAsAct->setWhatsThis(tr("Save the document under a new name"));
        connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

        exportSMFAct = new QAction(QIcon(":/images/filesave.png"), tr("Save As &SMF Patch... (*.mid)"), this);
        exportSMFAct->setShortcut(tr("Ctrl+Shift+E"));
        exportSMFAct->setWhatsThis(tr("Export as a Standard Midi File"));
        connect(exportSMFAct, SIGNAL(triggered()), this, SLOT(exportSMF()));

        saveGXGAct = new QAction(QIcon(":/images/filesave.png"), tr("Save As GXG Patch... (*.gxg)"), this);
        saveGXGAct->setShortcut(tr("Ctrl+Shift+G"));
        saveGXGAct->setWhatsThis(tr("Export as a Boss Librarian File"));
        connect(saveGXGAct, SIGNAL(triggered()), this, SLOT(saveGXG()));

        systemLoadAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load System and Global Data..."), this);
        systemLoadAct->setShortcut(tr("Ctrl+L"));
        systemLoadAct->setWhatsThis(tr("Load System Data to GT-10"));
        connect(systemLoadAct, SIGNAL(triggered()), this, SLOT(systemLoad()));

        systemSaveAct = new QAction(QIcon(":/images/filesave.png"), tr("Save System and Global Data to File..."), this);
        systemSaveAct->setShortcut(tr("Ctrl+D"));
        systemSaveAct->setWhatsThis(tr("Save System Data to File"));
        connect(systemSaveAct, SIGNAL(triggered()), this, SLOT(systemSave()));

        bulkLoadAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load Bulk Patch File to GT-10..."), this);
        bulkLoadAct->setShortcut(tr("Ctrl+B"));
        bulkLoadAct->setWhatsThis(tr("Load Bulk Data to GT-10"));
        connect(bulkLoadAct, SIGNAL(triggered()), this, SLOT(bulkLoad()));

        bulkSaveAct = new QAction(QIcon(":/images/filesave.png"), tr("Save Bulk GT-10 Patches to File..."), this);
        bulkSaveAct->setShortcut(tr("Ctrl+G"));
        bulkSaveAct->setWhatsThis(tr("Save Bulk Data to File"));
        connect(bulkSaveAct, SIGNAL(triggered()), this, SLOT(bulkSave()));

        exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
        exitAct->setShortcut(tr("Ctrl+Q"));
        exitAct->setWhatsThis(tr("Exit the application"));
        connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

        settingsAct = new QAction(QIcon(":/images/preferences.png"), tr("&Preferences"), this);
        settingsAct->setShortcut(tr("Ctrl+P"));
        settingsAct->setWhatsThis(tr("FxFloorBoard Preferences<br>Select midi device, language,splash, directories"));
        connect(settingsAct, SIGNAL(triggered()), this, SLOT(settings()));

        uploadAct = new QAction(QIcon(":/images/upload.png"), tr("Upload patch to GT-Central"), this);
        uploadAct->setWhatsThis(tr("Upload any saved patch file to a shared patch library<br>via the internet."));
        connect(uploadAct, SIGNAL(triggered()), this, SLOT(upload()));

        summaryAct = new QAction(QIcon(":/images/copy.png"), tr("Patch Text Summary"), this);
        summaryAct->setWhatsThis(tr("Display the current patch parameters<br>in a readable text format, which<br>can be printed or saved to file."));
        connect(summaryAct, SIGNAL(triggered()), this, SLOT(summaryPage()));

        // rrr: insert May 2010
        // Disassemble the Efects Signal Chain Path A & B
        // and Show Only Effects which are ON
        summaryAct2 = new QAction(QIcon(":/images/copy.png"), tr("Summary Page Text2"), this);
        summaryAct2->setStatusTip(tr("........"));
        connect(summaryAct2, SIGNAL(triggered()), this, SLOT(summaryPage2()));
        
        summarySystemAct = new QAction(QIcon(":/images/copy.png"), tr("System/Global Text Summary"), this);
        summarySystemAct->setWhatsThis(tr("Display the current System and Global parameters<br>in a readable text format, which<br>can be printed or saved to file."));
        connect(summarySystemAct, SIGNAL(triggered()), this, SLOT(summarySystemPage()));
        
        summaryPatchListAct = new QAction(QIcon(":/images/copy.png"), tr("GT-10 Patch List Summary"), this);
        summaryPatchListAct->setWhatsThis(tr("Display the GT-10 patch listing names<br>in a readable text format, which<br>can be printed or saved to file."));
        connect(summaryPatchListAct, SIGNAL(triggered()), this, SLOT(summaryPatchList()));

        helpAct = new QAction(QIcon(":/images/help.png"), tr("GT-10 Fx FloorBoard &Help"), this);
        helpAct->setShortcut(tr("Ctrl+F1"));
        helpAct->setWhatsThis(tr("Help page to assist with FxFloorBoard functions."));
        connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

        whatsThisAct = new QAction(QIcon(":/images/help.png"), tr("Whats This? description of items under the mouse cursor"), this);
        whatsThisAct->setShortcut(tr("F1"));
        whatsThisAct->setWhatsThis(tr("ha..ha..ha..!!"));
        connect(whatsThisAct, SIGNAL(triggered()), this, SLOT(whatsThis()));

        homepageAct = new QAction(QIcon(":/images/GT-10FxFloorBoard.png"), tr("GT-10 Fx FloorBoard &Webpage"), this);
        homepageAct->setWhatsThis(tr("download Webpage for FxFloorBoard<br>find if the latest version is available."));
        connect(homepageAct, SIGNAL(triggered()), this, SLOT(homepage()));

        donationAct = new QAction(QIcon(":/images/donate.png"), tr("Donate towards GT test equipment for Gumtown"), this);
        donationAct->setWhatsThis(tr("Even though the software is free,<br>an occassional donation is very much appreciated<br>i am not paid for this work."));
        connect(donationAct, SIGNAL(triggered()), this, SLOT(donate()));

        manualAct = new QAction(QIcon(":/images/manual.png"), tr("User Manual PDF"), this);
        manualAct->setWhatsThis(tr("........"));
        connect(manualAct, SIGNAL(triggered()), this, SLOT(manual()));

        licenseAct = new QAction(QIcon(":/images/licence.png"), tr("&License"), this);
        licenseAct->setWhatsThis(tr("licence agreement which you<br>have accepted by installing this software."));
        connect(licenseAct, SIGNAL(triggered()), this, SLOT(license()));

        aboutAct = new QAction(QIcon(":/images/GT-10FxFloorBoard.png"), tr("&About FxFloorBoard"), this);
        aboutAct->setWhatsThis(tr("Show the application's About box"));
        connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

        aboutQtAct = new QAction(QIcon(":/images/qt-logo.png"),tr("About &Qt"), this);
        aboutQtAct->setWhatsThis(tr("Show the Qt library's About box"));
        connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
};

void mainWindow::createMenus()
{
    menuBar = new QMenuBar;

  QMenu *fileMenu = new QMenu(tr("&File"), this);
        fileMenu->addAction(openAct);
        fileMenu->addSeparator();
        //fileMenu->addAction(saveAct);
        fileMenu->addAction(saveAsAct);
        //fileMenu->addSeparator();
        //fileMenu->addAction(importSMFAct);
        fileMenu->addAction(exportSMFAct);
        //fileMenu->addSeparator();
        //fileMenu->addAction(openGXGAct);
        fileMenu->addAction(saveGXGAct);
        fileMenu->addSeparator();
        fileMenu->addAction(bulkLoadAct);
        fileMenu->addAction(bulkSaveAct);
        fileMenu->addSeparator();
        fileMenu->addAction(systemLoadAct);
        fileMenu->addAction(systemSaveAct);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAct);
        menuBar->addMenu(fileMenu);
        fileMenu->setWhatsThis(tr("File Saving and Loading,<br> and application Exit."));


        QMenu *toolsMenu = new QMenu(tr("&Tools"), this);
        toolsMenu->addAction(settingsAct);
        toolsMenu->addAction(uploadAct);
        fileMenu->addSeparator();
        toolsMenu->addAction(summaryAct);
        //toolsMenu->addAction(summaryAct2);
        toolsMenu->addAction(summarySystemAct);
        toolsMenu->addAction(summaryPatchListAct);
        menuBar->addMenu(toolsMenu);


        QMenu *helpMenu = new QMenu(tr("&Help"), this);
        helpMenu->addAction(helpAct);
        helpMenu->addAction(whatsThisAct);
        helpMenu->addAction(homepageAct);
        helpMenu->addSeparator();
        helpMenu->addAction(donationAct);
        helpMenu->addSeparator();
        helpMenu->addAction(manualAct);
        helpMenu->addAction(licenseAct);
        helpMenu->addSeparator();
        helpMenu->addAction(aboutAct);
        helpMenu->addAction(aboutQtAct);
        menuBar->addMenu(helpMenu);

};

void mainWindow::createStatusBar()
{
        SysxIO *sysxIO = SysxIO::Instance();

        statusBarWidget *statusInfo = new statusBarWidget(this);
        statusInfo->setStatusSymbol(0);
        statusInfo->setStatusMessage(tr("Not connected"));

        QObject::connect(sysxIO, SIGNAL(setStatusSymbol(int)), statusInfo, SLOT(setStatusSymbol(int)));
        QObject::connect(sysxIO, SIGNAL(setStatusProgress(int)), statusInfo, SLOT(setStatusProgress(int)));
        QObject::connect(sysxIO, SIGNAL(setStatusMessage(QString)), statusInfo, SLOT(setStatusMessage(QString)));
        QObject::connect(sysxIO, SIGNAL(setStatusdBugMessage(QString)), statusInfo, SLOT(setStatusdBugMessage(QString)));

        statusBar = new QStatusBar;
        statusBar->addWidget(statusInfo);
        statusBar->setSizeGripEnabled(false);
};

/* FILE MENU */
void mainWindow::open()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("for GT-10, GT-10B, or GT-8   (*.syx *.mid *.gxg *.gxb)"));
        if (!fileName.isEmpty())
        {
                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());
                        sysxIO->setFileName(fileName);
                        sysxIO->setSyncStatus(false);
                        sysxIO->setDevice(false);
                        emit updateSignal();
                        if(sysxIO->isConnected())
                        {sysxIO->writeToBuffer();};
                };
        };
};

void mainWindow::save()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        SysxIO *sysxIO = SysxIO::Instance();
        file.setFile(sysxIO->getFileName());

        if(file.getFileName().isEmpty())
        {
                QString fileName = QFileDialog::getSaveFileName(
                                                this,
                                                tr("Save As"),
                                                dir,
                                                tr("System Exclusive (*.syx)"));
                if (!fileName.isEmpty())
                {
                        if(!fileName.contains(".syx"))
                        {
                                fileName.append(".syx");
                        };
                        file.writeFile(fileName);

                        file.setFile(fileName);
                        if(file.readFile())
                        {
                                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                                SysxIO *sysxIO = SysxIO::Instance();
                                QString area = "Structure";
                          sysxIO->setFileSource(area, file.getFileSource());
                                emit updateSignal();
                        };
                };
        }
        else
        {
                file.writeFile(file.getFileName());
        };
};

void mainWindow::saveAs()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save As"),
                    dir,
                    tr("System Exclusive (*.syx)"));
        if (!fileName.isEmpty())
        {
                if(!fileName.contains(".syx"))
                {
                        fileName.append(".syx");
                };
                file.writeFile(fileName);

                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());


                        emit updateSignal();
                };
        };
};

void mainWindow::importSMF()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("Standard Midi File (*.mid)"));
        if (!fileName.isEmpty())
        {
                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());
                        sysxIO->setFileName(fileName);
                        sysxIO->setSyncStatus(false);
                        sysxIO->setDevice(false);
                        emit updateSignal();
                        if(sysxIO->isConnected())
                        {sysxIO->writeToBuffer(); };
                };
        };
};

void mainWindow::exportSMF()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Export SMF"),
                    dir,
                    tr("Standard Midi File (*.mid)"));
        if (!fileName.isEmpty())
        {
                if(!fileName.contains(".mid"))
                {
                        fileName.append(".mid");
                };
                file.writeSMF(fileName);

                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());

                        emit updateSignal();
                };
        };
};

void mainWindow::openGXG()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("Boss Librarian File (*.gxg *.gxb)"));
        if (!fileName.isEmpty())
        {
                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());
                        sysxIO->setFileName(fileName);
                        sysxIO->setSyncStatus(false);
                        sysxIO->setDevice(false);

                        emit updateSignal();
                        if(sysxIO->isConnected())
                        {sysxIO->writeToBuffer(); };
                };
        };
};

void mainWindow::saveGXG()
{
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Export GXG"),
                    dir,
                    tr("Boss Librarian File (*.gxg)"));
        if (!fileName.isEmpty())
        {
                if(!fileName.contains(".gxg"))
                {
                        fileName.append(".gxg");
                };
                file.writeGXG(fileName);

                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                        SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "Structure";
                        sysxIO->setFileSource(area, file.getFileSource());

                        emit updateSignal();
                };
        };
};

void mainWindow::systemLoad()
{
   SysxIO *sysxIO = SysxIO::Instance();
     if (sysxIO->isConnected())
               {
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                deviceType + tr(" System Data File (*.GT10_system_syx)"));
        if (!fileName.isEmpty())
        {
                file.setFile(fileName);
                if(file.readFile())
                {
                        // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                  SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "System";
                        sysxIO->setFileSource(area, file.getSystemSource());
                        sysxIO->setFileName(fileName);
                        //sysxIO->setSyncStatus(false);
                        //sysxIO->setDevice(false);
                        emit updateSignal();
                                 QMessageBox *msgBox = new QMessageBox();
                                        msgBox->setWindowTitle(deviceType + tr(" Fx FloorBoard"));
                                        msgBox->setIcon(QMessageBox::Warning);
                                        msgBox->setTextFormat(Qt::RichText);
                                        QString msgText;
                                        msgText.append("<font size='+1'><b>");
                                        msgText.append(tr("You have chosen to load a SYSTEM DATA file."));
                                        msgText.append("<b></font><br>");
                                        msgText.append(tr("This will overwrite the SYSTEM DATA currently stored in the ")+ deviceType);
                                        msgText.append(tr ("<br> and can't be undone.<br>"));
                                        msgText.append(tr("Select 'NO' to only update the Editor - Select 'YES' to update the GT System<br>"));


                                        msgBox->setInformativeText(tr("Are you sure you want to write to the ")+ deviceType);
                                        msgBox->setText(msgText);
                                        msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);

                                        if(msgBox->exec() == QMessageBox::Yes)
                                        {	// Accepted to overwrite system data.
                                        sysxIO->systemWrite();
                                        };
                         };
               };
        }
         else
             {
              QString snork = tr("Ensure connection is active and retry");
              QMessageBox *msgBox = new QMessageBox();
                                msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
                                msgBox->setIcon(QMessageBox::Information);
                                msgBox->setText(snork);
                                msgBox->setStandardButtons(QMessageBox::Ok);
                                msgBox->exec();
              };
};

void mainWindow::systemSave()
{


SysxIO *sysxIO = SysxIO::Instance();
     if (sysxIO->isConnected())
               {
  sysxIO->systemDataRequest();

        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save System Data"),
                    dir,
                    tr("System Exclusive File (*.GT10_system_syx)"));
        if (!fileName.isEmpty())
        {
          if(!fileName.contains(".GT10_system_syx"))
                {
                        fileName.append(".GT10_system_syx");
                };

                file.writeSystemFile(fileName);

                file.setFile(fileName);
                if(file.readFile())
                {
                  SysxIO *sysxIO = SysxIO::Instance();
                        QString area = "System";
                        sysxIO->setFileSource(area, file.getSystemSource());
                        emit updateSignal();
                };
        };
         }
         else
             {
              QString snork = tr("Ensure connection is active and retry<br>");
              QMessageBox *msgBox = new QMessageBox();
                                msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
                                msgBox->setIcon(QMessageBox::Information);
                                msgBox->setText(snork);
                                msgBox->setStandardButtons(QMessageBox::Ok);
                                msgBox->exec();
              };
};

void mainWindow::bulkLoad()
{
   SysxIO *sysxIO = SysxIO::Instance();
     if (sysxIO->isConnected())
               {
                bulkLoadDialog *loadDialog = new bulkLoadDialog();
            loadDialog->exec();
        }
         else
             {
              QString snork = tr("Ensure connection is active and retry");
              QMessageBox *msgBox = new QMessageBox();
                                msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
                                msgBox->setIcon(QMessageBox::Information);
                                msgBox->setText(snork);
                                msgBox->setStandardButtons(QMessageBox::Ok);
                                msgBox->exec();
              };
};

void mainWindow::bulkSave()
{

 SysxIO *sysxIO = SysxIO::Instance();
     if (sysxIO->isConnected())
               {
            bulkSaveDialog *bulkDialog = new bulkSaveDialog();
            bulkDialog->exec();
                }
           else
             {
              QString snork = tr("Ensure connection is active and retry");
              QMessageBox *msgBox = new QMessageBox();
                                msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
                                msgBox->setIcon(QMessageBox::Information);
                                msgBox->setText(snork);
                                msgBox->setStandardButtons(QMessageBox::Ok);
                                msgBox->exec();
              };
};

/* TOOLS MENU */
void mainWindow::settings()
{
        preferencesDialog *dialog = new preferencesDialog();
        if (dialog->exec())
        {
                Preferences *preferences = Preferences::Instance();

                QString dir = dialog->generalSettings->dirEdit->text();
                QString sidepanel = (dialog->windowSettings->sidepanelCheckBox->checkState())?QString("true"):QString("false");
                QString window = (dialog->windowSettings->windowCheckBox->checkState())?QString("true"):QString("false");
                QString splash = (dialog->windowSettings->splashCheckBox->checkState())?QString("true"):QString("false");
                QString dBug = (dialog->midiSettings->dBugCheckBox->checkState())?QString("true"):QString("false");
                QString midiIn = QString::number(dialog->midiSettings->midiInCombo->currentIndex() - 1, 10); // -1 because there is a default entry at index 0
                QString midiOut = QString::number(dialog->midiSettings->midiOutCombo->currentIndex() - 1, 10);
                QString midiTimeSet =QString::number(dialog->midiSettings->midiTimeSpinBox->value());
                QString receiveTimeout =QString::number(dialog->midiSettings->midiDelaySpinBox->value());
                 QString lang;
    if (dialog->languageSettings->chineseButton->isChecked() ) {lang="3"; }
    else if (dialog->languageSettings->germanButton->isChecked() ) {lang="2"; }
    else if (dialog->languageSettings->frenchButton->isChecked() ) {lang="1"; }
    else {lang="0"; };
    preferences->setPreferences("Language", "Locale", "select", lang);

                if(midiIn=="-1") { midiIn = ""; };
                if(midiOut=="-1") {	midiOut = ""; };

                preferences->setPreferences("General", "Files", "dir", dir);
                preferences->setPreferences("Midi", "MidiIn", "device", midiIn);
                preferences->setPreferences("Midi", "MidiOut", "device", midiOut);
                preferences->setPreferences("Midi", "DBug", "bool", dBug);
                preferences->setPreferences("Midi", "Time", "set", midiTimeSet);
                preferences->setPreferences("Midi", "Delay", "set", receiveTimeout);
                preferences->setPreferences("Window", "Restore", "sidepanel", sidepanel);
                preferences->setPreferences("Window", "Restore", "window", window);
                preferences->setPreferences("Window", "Splash", "bool", splash);
                preferences->savePreferences();
        };
};

/* HELP MENU */
void mainWindow::help()
{
        Preferences *preferences = Preferences::Instance();
        QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Help", "url") ));
};

void mainWindow::whatsThis()
{
    QWhatsThis::enterWhatsThisMode();
};


void mainWindow::upload()
{
        Preferences *preferences = Preferences::Instance();
        QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Upload", "url") ));
};

void mainWindow::summaryPage()
{
   summaryDialog *summary = new summaryDialog();
   summary->setMinimumWidth(800);
   summary->setMinimumHeight(650);
   summary->show();
};

void mainWindow::summaryPage2()
{
   summaryDialog2 *summary2 = new summaryDialog2();
   summary2->setMinimumWidth(800);
   summary2->setMinimumHeight(750); // a little taller
   summary2->show();
};

void mainWindow::summarySystemPage()
{
   summaryDialogSystem *summarySystem = new summaryDialogSystem();
   summarySystem->setMinimumWidth(800);
   summarySystem->setMinimumHeight(650);
   summarySystem->show();
};

void mainWindow::summaryPatchList()
{
   summaryDialogPatchList *summaryPatchList = new summaryDialogPatchList();
   summaryPatchList->setMinimumWidth(800);
   summaryPatchList->setMinimumHeight(650);
   summaryPatchList->show();
};   

void mainWindow::homepage()
{
        Preferences *preferences = Preferences::Instance();
        QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Webpage", "url") ));
};

void mainWindow::donate()
{
        Preferences *preferences = Preferences::Instance();
        QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Donate", "url") ));
};

void mainWindow::manual()
{
        Preferences *preferences = Preferences::Instance();
        QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Manual", "url") ));
};

void mainWindow::license()
{
        QDesktopServices::openUrl(QUrl(":license.txt"));
};

void mainWindow::about()
{
    Preferences *preferences = Preferences::Instance();
        QString version = preferences->getPreferences("General", "Application", "version");

        QFile file(":about");
        if(file.open(QIODevice::ReadOnly))
        {
                QMessageBox::about(this, deviceType + tr(" Fx FloorBoard - About"),
                        deviceType + tr(" Fx FloorBoard - ") + tr("version") + " " + version + "<br>" + file.readAll());
        };
};

void mainWindow::closeEvent(QCloseEvent* ce)
{
        Preferences *preferences = Preferences::Instance();
        preferences->savePreferences();
        ce->accept();
        emit closed();
};
