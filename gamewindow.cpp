
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QString>
#include <QPainter>
#include <QThread>
#include <QVector>
#include "roadEval.h"
#include <qrandom.h>

QColor RED(240, 10 ,10);
QColor BLUE(10, 10, 240);

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
    for (auto tile : tiles) {
        delete tile;
    }
    delete indicator;
    delete returnButton;
    delete winMessage;
    delete moveMessage;
    delete threadAI;
    delete actorAI;
    delete _brd;
    delete _frst;
    delete _scnd;
}

QColor GameWindow::tpHex2rgb(tpHex color)
{
    if (color == tpHex::Horiz)
        return RED;
    else
        return QColor(BLUE);
}

void GameWindow::switchPlayer()
{
    if (active==_frst){
        active = _scnd;
        indicator->setColor(tpHex2rgb(active->get_color()));
    }
    else {
        active = _frst;
        indicator->setColor(tpHex2rgb(active->get_color()));
    }
}

//void GameWindow::switchAI()
//{
//    if (active_worker == actorAI1){
//        active_worker = actorAI2;
//    }
//    else {
//        active_worker = actorAI1;
//    }
////    threadAI->;
//    threadAI = new QThread(this);
//    active_worker->moveToThread(threadAI);
//}

void GameWindow::endGame()
{

    for (int i= 0 ; i< tiles.size();i++)
        tiles[i]->setEnabled(false);
    connect(returnButton, SIGNAL(pressed()),this,SLOT(onReturn()));
    returnButton->show();
    indicator->hide();
    moveMessage->hide();


    if (active->get_color() == tpHex::Horiz){
        QColor color(160, 10, 10);
        QString format("<font color=\"%1\">%2</font>");
        winMessage->setText(format.arg(color.name(), "RED player won!" ));
    }
    else {
        QColor color(10, 10, 160);
        QString format("<font color=\"%1\">%2</font>");
        winMessage->setText(format.arg(color.name(), "BLUE player won!" ));
    }
    winMessage->setStyleSheet("font-size:20px");
    winMessage->move(_brd->side()*20,_brd->side()*70);
    winMessage->adjustSize();
    emit(finished());
}

void GameWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::NoPen);
    const float bufs=20;
    QPointF upr(bufs*1.5+(_brd->side())+(_brd->side()*65+pseudoW*offSetX/10),offSetY);
    QPointF downr(bufs*1.5+(_brd->side())+(_brd->side()/5.0)+(_brd->side()*65+30),
                  bufs*0.8+(offSetY+pseudoW/1.5));
    QPointF downl(30,
                  bufs*0.8+(offSetY+pseudoW/1.5));
    QPointF upl(pseudoW*offSetX/10,offSetY);
    QPen pen;
    pen.setWidthF(2);
    pen.setColor(RED);
    painter.setPen(pen);
    painter.drawLine(upr,downr);
    painter.drawLine(downl,upl);
    pen.setColor(BLUE);
    painter.setPen(pen);
    painter.drawLine(upl,upr);
    painter.drawLine(downr,downl);

}

void GameWindow::takeGameData(_hex *board, actor *first, actor *second)
{
    _brd=board;
    _frst=first;
    _scnd=second;
    active = _frst;
    pseudoW=_brd->side()*86;
    int posX = pseudoW*offSetX/10, posY = offSetY;
    for(int i=0 ; i < _brd->all_nodes(); i++){
        tiles.push_back(new hexButton(this));
        tiles[i]->setStyleSheet("background-color: rgba(255,255,255, 0%);");
        tiles[i]->setColor(200,200,200);
        tiles[i]->setText(QString::number(i));
        connect(tiles[i], SIGNAL(pressed()),this,SLOT(onMove()));
        tiles[i]->move(posX, posY);
        posX += pseudoW/(_brd->side()*1.3);
        if ((i+1) % _brd->side() == 0 ){
            posX -= pseudoW/(_brd->side()*1.3)*_brd->side()+((pseudoW*tilesOffSet/10)/(_brd->side()+1));
            posY += pseudoW/(_brd->side()*1.5);
        }
    }

    indicator = new hexButton(this);
    indicator->move(_brd->side()*86,_brd->side()*50);
    indicator->setColor(RED);
    indicator->setStyleSheet("background-color: rgba(255,255,255, 0%);");

    returnButton = new QPushButton(this);
    returnButton->move(_brd->side()*95,_brd->side()*70);
    returnButton->setText("Return");
    returnButton->setStyleSheet("background-color: rgba(100,160,100, 80%);"
                                "border: 5px solid black;"
                                "width: 100px;"
                                "height: 30px;"
                                "font-weight: bold;"
                                "font-size:25px;"
                                "text-align:center;");
    returnButton->hide();
    winMessage= new QLabel(this);

    moveMessage = new QLabel(this);
    moveMessage->move(_brd->side()*95,_brd->side()*55);
    moveMessage->setText("Makes a move..");


    if (_frst->get_role() != Role::Human){
        threadAI = new QThread;
        actorAI = new Worker(first,_brd,thread_result);
        connect(threadAI, SIGNAL (started()), actorAI, SLOT (process()));
        connect(actorAI, SIGNAL (finished()), threadAI, SLOT (quit()));
        connect(actorAI, SIGNAL (finished()), this, SLOT (onMoveAI()));
        connect(this, SIGNAL (finished()), threadAI, SLOT (deleteLater()));
        otherPlayerAI = true;
    }
    if (_scnd->get_role() != Role::Human){
        if (threadAI==nullptr){
            threadAI = new QThread;
            connect(this, SIGNAL (finished()), threadAI, SLOT (deleteLater()));
            actorAI = new Worker (_scnd,_brd,thread_result);
            connect(threadAI, SIGNAL (started()), actorAI, SLOT (process()));
            connect(actorAI, SIGNAL (finished()), threadAI, SLOT (quit()));
            connect(actorAI, SIGNAL (finished()), this, SLOT (onMoveAI()));
        }
        else
            actorAI->addActor(_scnd);
        otherPlayerAI = true;
    }
    if (_frst->get_role() != Role::Human && _scnd->get_role() != Role::Human)
        bothPlayersAI = true;

    if (otherPlayerAI){
       actorAI->moveToThread(threadAI);
        connect(this, SIGNAL (finished()), actorAI, SLOT (deleteLater()));
    }

    if (_frst->get_role()!= Role::Human){
        threadAI->start();
    }
    else
        can_move = true;

}

void GameWindow::onMove()
{
if (!can_move)
    return;
        hexButton *button = (hexButton *)sender();
        int but_ind= button->getText().toInt();
        if (_brd->get_node(but_ind) == tpHex::Empty){
            _brd->set_node(but_ind, active->get_color());
            tiles[but_ind]->setColor(tpHex2rgb(active->get_color()));
            switch (test_win_path(*_brd)) {
            case tpHex::Horiz:
                endGame();
                return;
                break;
            case tpHex::Vert:
                endGame();
                return;
                break;
            case tpHex::Empty:
                break;
            }

            switchPlayer();
            if (otherPlayerAI){
               threadAI->start();
               can_move=false;
            }

        }

}

void GameWindow::onMoveAI()
{

    int but_ind= thread_result;
    _brd->set_node(but_ind, active->get_color());
    tiles[but_ind]->setColor(tpHex2rgb(active->get_color()));
    switch (test_win_path(*_brd)) {
    case tpHex::Horiz:
        endGame();
        return;
        break;
    case tpHex::Vert:
        endGame();
        return;
        break;
    case tpHex::Empty:
        break;
    }
    switchPlayer();
    if (bothPlayersAI){
        threadAI->wait(5000);
        threadAI->start();
    }
    else
        can_move=true;

}

void GameWindow::onReturn()
{
    this->close();
}

