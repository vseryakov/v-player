/*
 *  Author: Vlad Seryakov vseryakov@gmail.com
 *  April 2013
 *
 */

#include "vplay.h"

#ifdef Q_OS_MAC
#include <Carbon/Carbon.h>
#endif

// Bring process to the front
void VApplication::raise()
{
#ifdef Q_OS_MAC
	Boolean sameProc;
    ProcessSerialNumber myProc, frProc;
    if (GetFrontProcess(&frProc) == noErr && GetCurrentProcess(&myProc)== noErr) {
        if (SameProcess(&frProc, &myProc, &sameProc) == noErr && !sameProc) {
            TransformProcessType(&myProc, kProcessTransformToForegroundApplication);
        }
        SetFrontProcess(&myProc);
    }
#endif
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    VApplication app(argc, argv);

    QmlApplicationViewer viewer;
    viewer.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    viewer.setAttribute(Qt::WA_AutoOrientation, true);

    // Add all import and plugins paths known to us
    viewer.engine()->addImportPath(app.adjustPath("qml"));
    viewer.engine()->addPluginPath(app.adjustPath("qml"));
    viewer.engine()->addImportPath(app.adjustPath("imports"));
    viewer.engine()->addPluginPath(app.adjustPath("plugins"));
#ifdef QML_GENERIC_PATH
    viewer.engine()->addImportPath(Stringify(QML_GENERIC_PATH));
    viewer.engine()->addPluginPath(Stringify(QML_GENERIC_PATH));
#endif
#ifdef QML_PLATFORM_PATH
    viewer.engine()->addImportPath(Stringify(QML_PLATFORM_PATH));
    viewer.engine()->addPluginPath(Stringify(QML_PLATFORM_PATH));
#endif

    // Catch QML errors on load and exit
    app.connect((QObject*)&viewer, SIGNAL(statusChanged(QDeclarativeView::Status)), &app, SLOT(onStatusChanged(QDeclarativeView::Status)));

    VPlayApplication vapp(viewer);
    vapp.setQmlRendererEnabled(false);

    QString qmlFile = app.adjustPath("main.qml");
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).endsWith(".qml")) qmlFile = app.adjustPath(argv[i]);
        if (QString(argv[i]) == "-qmlrender") vapp.setQmlRendererEnabled(true);
        if (QString(argv[i]) == "-log") vapp.setLogMessagesEnabled(true);
        if (QString(argv[i]) == "-no-log") vapp.setLogMessagesEnabled(false);
    }
    if (qmlFile.isEmpty()) {
        fprintf(stderr, "main Qml file not found\n");
        exit(1);
    }

    vapp.setMainQmlFileName(qmlFile);
    Q_INIT_RESOURCE(resources_vplay);
    return vapp.startApplication();
}

