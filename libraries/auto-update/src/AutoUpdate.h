//
//  AutoUpdate.h
//  libraries/auto-update/src
//
//  Created by Leonardo Murillo on 6/1/2015.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AutoUpdate_h
#define hifi_AutoUpdate_h


#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QXmlStreamAttributes>
#include <QtCore/QXmlStreamReader>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <DependencyManager.h>

const QUrl BUILDS_XML_URL("https://highfidelity.com/builds.xml");

class AutoUpdate : public QObject, public Dependency {
    Q_OBJECT
    SINGLETON_DEPENDENCY
    
public:
    AutoUpdate();
    
    void checkForUpdate();
    const QMap<int, QMap<QString, QString>> &getBuildData() { return _builds; }
    void performAutoUpdate(int version);

signals:
    void latestVersionDataParsed();
    void newVersionIsAvailable();
    void newVersionIsDownloaded();

private:
    QMap<int, QMap<QString, QString>> _builds;
    QString _operatingSystem;
    
    void getLatestVersionData();
    void downloadUpdateVersion(int version);
    void appendBuildData(int versionNumber,
                         const QString& downloadURL,
                         const QString& releaseTime,
                         const QString& releaseNotes,
                         const QString& pullRequestNumber);

private slots:
    void parseLatestVersionData();
    void checkVersionAndNotify();
 
};

#endif // _hifi_AutoUpdate_h
