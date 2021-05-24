#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <actor.h>
#include <hexbutton.h>
#include <QLabel>
#include <worker.h>


namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    void takeGameData(_hex* board, actor* first, actor* second);
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    QVector <hexButton*> tiles;
    QThread *threadAI = nullptr;
    int thread_result;
    _hex *_brd;
    actor *_frst;
    actor *_scnd;

    actor *active;

    Worker *actorAI;

    float pseudoW;
    const float offSetX = 4.5;
    const float offSetY = 40;
    const float tilesOffSet = 4.15; //do not change

    bool bothPlayersAI = false;
    bool otherPlayerAI = false;
    hexButton *indicator;
    QPushButton *returnButton;
    QPainter qp();
    QLabel *winMessage;
    QLabel *moveMessage;
    bool can_move = false;


private:
    QColor tpHex2rgb (tpHex);
    void switchPlayer();
    void switchAI();
    void endGame();
    void paintEvent(QPaintEvent *event);
private slots:
    void onMove();
    void onMoveAI();
    void onReturn();
signals:
    void finished();
};

#endif // GAMEWINDOW_H
