#include <QtGui/QApplication>
#include <QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>
#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>
#include <qplatformdefs.h>

#include "qmlapplicationviewer.h"
#include "vplayapplication.h"

// Support all possible combinations to run this as an app bundle or standalone utility
static QString adjustPath(const QString &path)
{
    if (QDir::isAbsolutePath(path)) return path;
    QString file = QString::fromLatin1("%1/../Resources/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(file).exists()) return file;
    file = QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(file).exists()) return file;
    file = QString::fromLatin1("%1/qml/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(file).exists()) return file;
    file = QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(file).exists()) return file;
    if (QFileInfo(path).exists()) return QFileInfo(path).absoluteFilePath();
    return QString();
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(new QApplication(argc, argv));

    QString qml = adjustPath("main.qml");
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).endsWith(".qml")) qml = adjustPath(argv[i]);
    }
    if (qml.isEmpty()) {
        fprintf(stderr, "main Qml file not found %s\n", qPrintable(qml));
        exit(1);
    }

    app->setApplicationName("vplay");
    app->addLibraryPath(app->applicationDirPath() + "/../plugins");
    app->addLibraryPath(app->applicationDirPath() + "/../imports");

    QmlApplicationViewer viewer;
    VPlayApplication vplayApplication(viewer);
    vplayApplication.setQmlRendererEnabled(false);

    viewer.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    viewer.setAttribute(Qt::WA_AutoOrientation, true);
    viewer.engine()->addImportPath(adjustPath("qml"));
    viewer.engine()->addImportPath(adjustPath("imports"));
    viewer.engine()->addPluginPath(adjustPath("qml"));
    viewer.engine()->addPluginPath(adjustPath("plugins"));

    vplayApplication.setMainQmlFileName(qml);
    Q_INIT_RESOURCE(resources_vplay);

    return vplayApplication.startApplication();

}

