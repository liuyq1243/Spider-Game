#include "cardmove.h"
#include "card.h"
#include "pile.h"

QStack<CardMove*> CardMove::undostack;

CardMove::CardMove(Card *c, Pile *fr, Pile *t)
    :card(c), from(fr), to(t)
{
    count = 0;
    wasFaceUp = c->Faceup();
    wasUnderFaceUp = c->Under()?c->Under()->Faceup():false;
    undostack.push(this);
}
CardMove::CardMove(int n): count(n)
{
    undostack.push(this);
}

void CardMove::UndoMove()
{
    if(undostack.empty()) return;
    CardMove *u = undostack.pop();
    int n = u->count;
    do
    {
        if (n)
        {
            delete u;
            u = undostack.pop();
        }
        if (u->from->Top() && u->from->Top()->Faceup() != u->wasUnderFaceUp)
            u->from->Top()->Flip();
        u->card->Move(u->from, true, u->wasFaceUp,false);
        if(u->from->Type()==STOCK) u->card->Faceup(false);
    }while(--n>0);
    delete u;
}

void CardMove::Clear(){

    while(!undostack.empty()){
        CardMove * u = undostack.pop();
        delete u;
    }
}
