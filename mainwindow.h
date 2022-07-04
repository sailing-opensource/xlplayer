#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

#include "ClickableLabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void switchLayout(int id);
    void play(int index);

protected:
    void InitUI();
    void ClearLayout();
    ClickableLabel* GenQLabel();

private:
    Ui::MainWindow *ui;
    QSignalMapper *m_signalMapper;
    int m_labelIndex = 0;
};
#endif // MAINWINDOW_H
