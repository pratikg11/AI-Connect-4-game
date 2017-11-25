#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board{
private:
    char board[6][7];
    int rows=6;
    int columns=7;
    int playerX=1;
    int playerO=2;
    int noPlayer=0;
    int usersCurrent_RowNo;
    int usersCurrent_ColumnNo;
public:
    Board();
    int checkIfPlayerWins(int,int,int);
    void performMove(int,int);
    void displayBoard();
    void getInput();
    void startGame();
    int getRowNo();
    int getColumnNo();

};


#endif // BOARD_H_INCLUDED
