#ifndef QTFUNCTIONS_H
#define QTFUNCTIONS_H

#include <QFile>
#include <QApplication>

inline void loadSkin(const char *skin) {
    // :/skin/dark.qss
    QFile file(QString(":/skin/") + QString(skin) + QString(".qss"));
    if (file.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}

#endif // QTFUNCTIONS_H
