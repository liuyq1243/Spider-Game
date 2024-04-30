#include "gameboard.h"
#include <QTime>
#include <QtGlobal>
#include "game.h"
#include"cardmove.h"
#include "spider.h"
#include "ui_gameboard.h"
#include "card.h"
#include "rule.h"
#include "help.h"
#include "about.h"
#include<QTimer>

Game *game = 0;

gameboard::gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameboard)
{
    ui->setupUi(this);
    QTime time = QTime::currentTime();
    srand((uint)time.msec());
    menuBar()->setNativeMenuBar(false);

    QTimer* timer = new QTimer(this);
    timer->start(1000);

    ui->time->setText("0");
    static int t = 0;
    connect(timer,&QTimer::timeout,[=](){
        ui->time->setText(QString("%1").arg(t++));
    });

}

gameboard::~gameboard()
{
    delete ui;
}

void gameboard::on_actionSpider_triggered()
{
    // initialize
   Card::Initialize();
   if(game)
       delete game;
   game = new Spider(ui->centralWidget);
   setWindowTitle(game->GameName());
   game->ReDeal(REPEAT);

}

void gameboard::on_actionRedeal_triggered()
{
    if(!game) return;
    game->ReDeal();

}

void gameboard::on_actionUndo_triggered()
{
    CardMove::UndoMove();
}


void gameboard::on_actionAbout_3_triggered()
{

        about *a = new about(gb);
        a->exec();

}

void gameboard::on_actionHelp_3_triggered()
{
    help *h = new help(this);
    h->exec();
}

void gameboard::on_actionPlay_Off_triggered()
{
    if(!game) return;
    game->PlayOffAll();
}
