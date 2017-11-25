#include<iostream>
#include"Board.h"
using namespace std;

Board::Board(){
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++){
            board[i][j]=' ';
        }
}

int Board::checkIfPlayerWins(int player,int row,int column){
    

}

//performing the users move
void Board::performMove(int x,int y){
    if(board[rows-1-x][y]==' '){
        board[rows-1-x][y]='X';
        displayBoard();
        int result=checkIfPlayerWins(1,rows-1-x,y);
        if(result==0)
            getInput();
        else
            cout<<"Player 1 wins"<<endl;
    }
    else{
        cout<<"This position is already occupied. Please choose another position"<<endl;
        getInput();
    }
}

//Displaying the board
void Board::displayBoard(){
    cout<<endl;
    cout<<"  ";
    for(int i=0;i<columns;i++)
        cout<<" |C"<<i;
    cout<<" | ";
    cout<<endl<<"  ----------------------------"<<endl;
    for(int i=0;i<rows;i++){
        cout<<"R"<<rows-1-i<<" | ";
        for(int j=0;j<columns;j++){
            cout<<board[i][j]<<" | ";
        }
        cout<<endl;
    }
    cout<<"  ----------------------------"<<endl;
}

//getting inputs from user for X and Y Co-ordinates
void Board::getInput(){
    cout<<"Enter row : ";
    cin>>usersCurrent_RowNo;
    cout<<"Enter column : ";
    cin>>usersCurrent_ColumnNo;
    performMove(usersCurrent_RowNo,usersCurrent_ColumnNo);
}

void Board::startGame(){
    displayBoard();
    getInput();
}

int Board::getRowNo(){
    return usersCurrent_RowNo;
}

int Board::getColumnNo(){
    return usersCurrent_ColumnNo;
}




