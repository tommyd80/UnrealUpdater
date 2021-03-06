﻿/**
 *  This work is distributed under the General Public License,
 *	see LICENSE for details
 *
 *  @author Gwennaël ARBONA
 **/

#ifndef UPDATER_H
#define UPDATER_H

/*----------------------------------------------
	Includes & definitions
----------------------------------------------*/

#include <QCryptographicHash>
#include <QtConcurrentRun>
#include <QFutureWatcher>
#include <QDomDocument>
#include <QTextStream>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QProcess>
#include <QDate>
#include <algorithm>

#include "common.h"
#include "about.h"
#include "serverconfig.h"
#include "downloader.h"


/*----------------------------------------------
	Class definitions
----------------------------------------------*/

namespace Ui {
	class Updater;
}

class Updater : public QMainWindow
{
	Q_OBJECT

	public:
		explicit Updater(QWidget *parent = 0);
		~Updater();

		static bool GetLock(void)
		{
			return QFile::exists(S_LOCK_FILE);
		}

	public slots:
        void Stage1(void);
        void Stage2(void);
        void Stage3(void);
        void BytesDownloaded(int number);
        void FileDownloaded(void);
        void AskForPassword(void);

        void Log(QString message, bool bIsHeavy);
        void SetUserMessage(QString message);

        void LaunchGame(void);
        void LaunchServer(void);
        void AboutMe(void);

    signals:
        void DownloadFile(QString dir, QString file);

	private:
        void ParseReleaseNotes(QDomNode node, bool bIsCurrent);
        void ParseManifest(QDomNode node, QString dirName);

        QString HashFile(QFile* file);
        void InstallNetFramework(void);
        void InstallUE3(void);
        void InstallVC2010(void);
		void SetLock(bool bLockState);
		void SetSettingState(bool bState, QString settingName);
        bool GetSettingState(QString settingName);

        bool        	bAbortUpdate;
        bool            bDownloadPart;

        int             downloadedBytes;
        int             downloadSize;
        int             remainingFiles;

		QDate           currentDate;
		QDate           nextDate;
		QString         currentVersion;
		QString         nextVersion;

        QDomDocument*   dom;
        File_t          currentFd;
		QList<QString>  notUpdatedFiles;
		QList<File_t>   filesToDownload;

        Downloader*     dlObject;
        QThread*		dlThread;
		Ui::Updater     *ui;
};

extern QString TextToHtml(QString data);

#endif // UPDATER_H
