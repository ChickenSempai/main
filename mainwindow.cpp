#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "_hex.h"
#include "gamewindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fHuman, SIGNAL(released()),this,SLOT(fSetPressed()));
    connect(ui->fMonte, SIGNAL(released()),this,SLOT(fSetPressed()));
    connect(ui->fRand, SIGNAL(released()),this,SLOT(fSetPressed()));

    ui->fHuman->setCheckable(true);
    ui->fMonte->setCheckable(true);
    ui->fRand->setCheckable(true);

    if (firstPlayerRole == Role::Human)
        ui->fHuman->setChecked(true);
    else
        if (firstPlayerRole == Role::Random)
        ui->fRand->setChecked(true);
    else
        if (firstPlayerRole ==  Role::Monte)
        ui->fMonte->setChecked(true);


    connect(ui->sHuman, SIGNAL(released()),this,SLOT(sSetPressed()));
    connect(ui->sMonte, SIGNAL(released()),this,SLOT(sSetPressed()));
    connect(ui->sRand, SIGNAL(released()),this,SLOT(sSetPressed()));

    if (secondPlayerRole == Role::Human)
        ui->sHuman->setChecked(true);
    else
        if (secondPlayerRole == Role::Random)
        ui->sRand->setChecked(true);
    else
        if (secondPlayerRole ==  Role::Monte)
        ui->sMonte->setChecked(true);


    connect(ui->sizeButton_7, SIGNAL(released()),this,SLOT(sizePressed()));
    connect(ui->sizeButton_9, SIGNAL(released()),this,SLOT(sizePressed()));
    connect(ui->sizeButton_11, SIGNAL(released()),this,SLOT(sizePressed()));

    ui->sizeButton_7->setCheckable(true);
    ui->sizeButton_9->setCheckable(true);
    ui->sizeButton_11->setCheckable(true);

    ui->sizeButton_7->setChecked(true);

    connect(ui->startButton, SIGNAL(released()),this,SLOT(strtPressed()));

    ui->startButton->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fSetPressed()
{

    ui->fHuman->setChecked(false);
    ui->fMonte->setChecked(false);
    ui->fRand->setChecked(false);

    QPushButton *button = static_cast<QPushButton *> (sender());
    if (button->objectName()=="fHuman")
        firstPlayerRole = Role::Human;
    else if (button->objectName()=="fRand")
        firstPlayerRole = Role::Random;
    else
        firstPlayerRole = Role::Monte;

    MainWindow::findChild<QPushButton *>(button->objectName())->setChecked(true);
}

void MainWindow::sSetPressed()
{

    ui->sHuman->setChecked(false);
    ui->sMonte->setChecked(false);
    ui->sRand->setChecked(false);

    QPushButton *button = static_cast<QPushButton *> (sender());
    if (button->objectName()=="sHuman")
        secondPlayerRole = Role::Human;

    else if (button->objectName()=="sRand")
        secondPlayerRole = Role::Random;

    else
        secondPlayerRole = Role::Monte;

    MainWindow::findChild<QPushButton *>(button->objectName())->setChecked(true);
}

void MainWindow::sizePressed()
{

    ui->sizeButton_7->setChecked(false);
    ui->sizeButton_9->setChecked(false);
    ui->sizeButton_11->setChecked(false);

    QPushButton *button = static_cast<QPushButton *> (sender());
    brdSize = button->text().toInt();

    MainWindow::findChild<QPushButton *>(button->objectName())->setChecked(true);
}

void MainWindow::strtPressed()
{
    hex_brd = new _hex(brdSize);

    if (firstPlayerRole == Role::Human)
        player_first = new Human(tpHex::Horiz);
    else
        if (firstPlayerRole == Role::Random)
        player_first = new AI_weak(tpHex::Horiz);
    else
        if (firstPlayerRole ==  Role::Monte)
        player_first = new AI_MonteCarlo(tpHex::Horiz);

    if (secondPlayerRole == Role::Human)
        player_second = new Human(tpHex::Vert);
    else
        if (secondPlayerRole == Role::Random)
        player_second = new AI_weak(tpHex::Vert);
    else
        if (secondPlayerRole ==  Role::Monte)
        player_second = new AI_MonteCarlo(tpHex::Vert);

    GameWindow *game = new GameWindow();
    game->setGeometry(200,20,hex_brd->side()*120,hex_brd->side()*80);
    game->takeGameData(hex_brd, player_first, player_second);
    game->show();

}

