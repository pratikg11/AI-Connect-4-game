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
    char char_Player;
    int count=1;
    if(player==1)
        char_Player='X';
    else if(player==2)
        char_Player='O';
    int r=row;
    int c=column;
    int tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
    bool left=true,right=true,up=true,down=true,leftUp=true,leftdown=true,rightUp=true,rightDown=true;

    //checking if we have winning row
       while(count!=4){
            if((tempLeft-1)>=0 && left){
                if(board[r][tempLeft-1]==char_Player)
                    count++;
                else
                   left=false;
                tempLeft--;
            }
            if((tempRight+1)<=5 && right){
                if(board[r][tempRight+1]==char_Player)
                    count++;
                else
                   right=false;
                   tempRight++;
            }
            if(count==4 && (left || right)){
                return 10;
            }
            if(!(left || right)){
                break;
            }
       }

       //checking if we have winning column
        while(count!=4){
            if((tempUp-1)>=0 && up){
                if(board[tempUp-1][c]==char_Player)
                    count++;
                else
                   up=false;
                tempUp--;
            }
            if((tempDown+1)<=5 && down){
                if(board[tempDown+1][c]==char_Player)
                    count++;
                else
                   down=false;
                   tempDown++;
            }
            if(count==4 && (up || down)){
                return 10;
            }
            if(!(up || down)){
                break;
            }
       }
       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       count=1;

       while(count!=4){
            if((tempUp-1)>=0 && (tempRight+1)<=5 && rightUp){
                if(board[tempUp-1][tempRight+1]==char_Player)
                    count++;
                else
                   rightUp=false;
                tempUp--;
                tempRight++;
            }
            if((tempDown+1)<=5 && (tempLeft-1)>=0 && leftdown){
                if(board[tempDown+1][tempLeft-1]==char_Player)
                    count++;
                else
                   leftdown=false;
                tempDown++;
                tempLeft--;
            }
            if(count==4 && (rightUp || leftdown)){
                return 10;
            }
            if(!(rightUp || leftdown)){
                break;
            }
       }


       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       count=1;

       while(count!=4){
            if((tempUp-1)>=0 && (tempLeft-1)>0 && leftUp){
                if(board[tempUp-1][tempLeft-1]==char_Player)
                    count++;
                else
                   leftUp=false;
                tempUp--;
                tempLeft--;
            }

            if((tempDown+1)<=5 && (tempRight+1)<=5 && rightDown){
                if(board[tempDown+1][tempRight+1]==char_Player)
                    count++;
                else
                   rightDown=false;
                tempDown++;
                tempRight++;
            }
            if(count==4 && (leftUp || rightDown)){
                return 10;
            }
            if(!(leftUp || rightDown)){
                break;
            }
       }
       return 0;

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




