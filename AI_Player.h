#ifndef AI_PLAYER_H_INCLUDED
#define AI_PLAYER_H_INCLUDED
#include"Board.h"
struct AI_Move{
int x;
int y;
int score;
int depth;
};

struct Score{
int value;
int depth;
};

class Ai_Player{
private:
    int rows=6;
    int columns=7;
    int playerX=1;
    int playerO=2;
public:
    int AIperformMove(Board&,int,int,int&);
    AI_Move getBestMove(Board,int,int,int&);
    Score performMinimax(Board, int,int,int,int,int&);
    void temp(Board&);
    bool deepEnough(int);
    Score moveGen(Board,int,int,int&);
    Score performMinimax_alfabetaPruning(Board, int,int,int,int,int,int,int&);
    Score moveGen_alfabetaPruning(Board,int,int,int,int,int&);
};

#endif // AI_PLAYER_H_INCLUDED
