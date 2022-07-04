#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QLoggingCategory>

#include "qtfunctions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadSkin("dark");
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    MainWindow w;

    QScreen *screen = a.primaryScreen();
    int sw = screen->size().width();
    int sh = screen->size().height();
    w.move((sw - w.width()) / 2, (sh - w.height()) / 2);

    w.show();
    return a.exec();
}
