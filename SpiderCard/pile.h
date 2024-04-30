#ifndef PILE_H
#define PILE_H
#include <QLabel>
#include <QMouseEvent>
#include "rule.h"
#include "game.h"
class Card;
class Game;

const int DRAGLAST = 6;
const int DROPLAST = 6;
enum pileType{FOUNDATION, STOCK, WASTE, TABLEAU,FREE_CELL};

class Pile :public QLabel
{
protected:
    QPoint delta;
    Card *top;
    Card *bottom;
    Game *game;
    virtual void paintEvent(QPaintEvent *);
private:


public:
    Pile(int x, int y, int dx, int dy, QWidget *parent, Game *game);
    ~Pile();
    Card *Top(){return top;}
    Card *Bottom(){return bottom;}
    void AcceptCards(Card *c, bool expose = true);
    void ReleaseCards(Card *c, bool expose = true);
    QPoint Delta(){ return delta;}
    bool Empty(){return !bottom;}
    bool CanBeDragged(Card *c);//checks relavent rules for this pile
    bool CanBeDropped(Card *c); //checks relavent rules for this pile
    void FindClosestDrop(Card *c);
    void AddDropRules(int n...);
    void AddDragRules(int n...);

    virtual Rule * DragRule(int i){return 0;}
    virtual void DragRule(int i, Rule *r){}
    virtual Rule *DropRule(int i){return 0;}
    virtual void DropRule(int i, Rule *r){}
    virtual pileType Type()=0;
    void mouseReleaseEvent(QMouseEvent *);
    virtual void onClickEvent(Card *)=0;
    virtual void mouseDoubleClickEvent(Card *){}


};


#endif // PILE_H
