#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "actor.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Role firstPlayerRole=Role::Monte;
    Role secondPlayerRole = Role::Monte;
    QWidget *gameWindow;
    int brdSize = 7;
    _hex* hex_brd;
    actor* player_first;
    actor* player_second;

private slots:
    void fSetPressed();
    void sSetPressed();
    void sizePressed();
    void strtPressed();
};
#endif // MAINWINDOW_H
