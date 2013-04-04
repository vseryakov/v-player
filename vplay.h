/*
 *  Author: Vlad Seryakov vseryakov@gmail.com
 *  April 2013
 *
 */

#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include <QtGui>
#include <QtGui/QApplication>
#include <QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>
#include <QIcon>
#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>
#include <qplatformdefs.h>
#include "qmlapplicationviewer.h"
#include "vplayapplication.h"

#define Stringify2(x) #x
#define Stringify(x) Stringify2(x)

class VApplication : public QApplication {
    Q_OBJECT

public:
    VApplication(int &argc, char **argv): QApplication(argc, argv) {
        setApplicationName("vplay");
        addLibraryPath(applicationDirPath() + "/../plugins");
        addLibraryPath(applicationDirPath() + "/../imports");
        setWindowIcon(QIcon(QPixmap(":/vplay.png")));
    }

    // Support all possible combinations to run this as an app bundle or standalone utility
    QString adjustPath(const QString &path) {
        if (QDir::isAbsolutePath(path)) return path;
        QString file = QString::fromLatin1("%1/../Resources/%2").arg(applicationDirPath(), path);
        if (QFileInfo(file).exists()) return file;
        file = QString::fromLatin1("%1/../%2").arg(applicationDirPath(), path);
        if (QFileInfo(file).exists()) return file;
        file = QString::fromLatin1("%1/qml/%2").arg(applicationDirPath(), path);
        if (QFileInfo(file).exists()) return file;
        file = QString::fromLatin1("%1/%2").arg(applicationDirPath(), path);
        if (QFileInfo(file).exists()) return file;
        if (QFileInfo(path).exists()) return QFileInfo(path).absoluteFilePath();
        return QString();
    }
    static void raise();

protected slots:
    void onStatusChanged(QDeclarativeView::Status status) {
        if (status == QDeclarativeView::Error) {
            _exit(0);
        }
        if (status == QDeclarativeView::Ready) {
            raise();
        }
    }

};

#endif
