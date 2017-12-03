#include<iostream>
#include"Board.h"
using namespace std;

Board::Board(){
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++){
            board[i][j]=' ';
        }
}

bool Board::isBoardFilled(){
 for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<columns; j++)
        {
            if(board[i][j]==' ')
                return false;
        }
    }
    return true;
}

int Board::checkIfPlayerWins(int player,int row,int column){
    char char_Player;
    int returnValue;
    int count=1;
    if(player==1){
        char_Player='X';
        returnValue=10;
    }
    else if(player==2){
        char_Player='O';
        returnValue=-10;
    }
    int r=row;
    int c=column;
    int tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
    bool left=true,right=true,up=true,down=true,leftUp=true,leftdown=true,rightUp=true,rightDown=true;

    //checking if we have winning row
       while(count!=winCount){
            if((tempLeft-1)>=0 && left){
                if(board[r][tempLeft-1]!=char_Player)
                   left=false;
                tempLeft--;
            }
            else
                left=false;
            if((tempRight+1)<=columns-1 && right){
                if(board[r][tempRight+1]!=char_Player)
                   right=false;
                tempRight++;
            }
            else
                right=false;
            if(left && right)
                count=count+2;
            else
                count++;
            if(count==winCount && (left || right)){
                return returnValue;
            }
            if(!(left || right)){
                break;
            }
       }
       count=1;

       //checking if we have winning column
        while(count!=winCount){
            if((tempUp-1)>=0 && up){
                if(board[tempUp-1][c]!=char_Player)
                   up=false;
                tempUp--;
            }
            else
                up=false;
            if((tempDown+1)<=rows-1 && down){
                if(board[tempDown+1][c]!=char_Player)
                   down=false;
                tempDown++;
            }
            else
                down=false;
            if(up && down)
                count=count+2;
            else
                count++;
            if(count==winCount && (up || down)){
                return returnValue;
            }
            if(!(up || down)){
                break;
            }
       }
       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       count=1;

       while(count!=winCount){
            if((tempUp-1)>=0 && (tempRight+1)<=columns-1 && rightUp){
                if(board[tempUp-1][tempRight+1]!=char_Player)
                   rightUp=false;
                tempUp--;
                tempRight++;
            }
            else
                rightUp=false;
            if((tempDown+1)<=rows-1 && (tempLeft-1)>=0 && leftdown){
                if(board[tempDown+1][tempLeft-1]!=char_Player)
                   leftdown=false;
                tempDown++;
                tempLeft--;
            }
            else
                leftdown=false;
            if(rightUp && leftdown)
                count=count+2;
            else
                count++;
            if(count==winCount && (rightUp || leftdown)){
                return returnValue;
            }
            if(!(rightUp || leftdown)){
                break;
            }
       }


       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       count=1;

       while(count!=winCount){
            if((tempUp-1)>=0 && (tempLeft-1)>0 && leftUp){
                if(board[tempUp-1][tempLeft-1]!=char_Player)
                   leftUp=false;
                tempUp--;
                tempLeft--;
            }
            else
                leftUp=false;
            if((tempDown+1)<=rows-1 && (tempRight+1)<=columns-1 && rightDown){
                if(board[tempDown+1][tempRight+1]!=char_Player)
                   rightDown=false;
                tempDown++;
                tempRight++;
            }
            else
                rightDown=false;
            if(leftUp && rightDown)
                count=count+2;
            else
                count++;
            if(count==winCount && (leftUp || rightDown)){
                return returnValue;
            }
            if(!(leftUp || rightDown)){
                break;
            }
       }
       return 0;
}

bool Board::checkInsertRule(int x,int y){
    if(x==rows-1){
        return true;
    }
    else{
        if(board[x+1][y]!=' ')
            return true;
    }
    return false;
}

//performing the users move
int Board::performMove(int x,int y){
    if(board[rows-1-x][y]==' '){
        if(checkInsertRule(rows-1-x,y)){
            board[rows-1-x][y]='X';
            displayBoard();
            int result=evaluateFunction(1,rows-1-x,y);
            if(result==0){
                //getInput();
                //displayBoard();
            return 0;
            }
            else if(result==10){
                cout<<"Player 1 wins"<<endl;
                return 1;
            }else if(result==-10){
                cout<<"Player 2 wins"<<endl;
            }
        }
        else{
            cout<<"Cannot Insert in this position. Please try new position"<<endl;
            return 2;
        }

    }
    else{
        cout<<"This position is already occupied. Please choose another position"<<endl;
        return 2;
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
int Board::getInput(){
    cout<<"Enter row : ";
   cin>>usersCurrent_RowNo;
    cout<<"Enter column : ";
    cin>>usersCurrent_ColumnNo;
   // board[3][2]='X';
//    board[2][0]='0';
//    board[1][0]='X';
   // usersCurrent_RowNo=2;
   // usersCurrent_ColumnNo=2;
    return performMove(usersCurrent_RowNo,usersCurrent_ColumnNo);
}

int Board::userPerformMove(int player){
    //displayBoard();
    return getInput();
}

int Board::getRowNo(){
    return usersCurrent_RowNo;
}

int Board::getColumnNo(){
    return usersCurrent_ColumnNo;
}


void Board::setValue(int x,int y,char c){
    board[x][y]=c;
}
char Board::getValue(int x,int y){
    return board[x][y];
}


int Board::evaluateFunction(int player,int row,int column){
    char char_Player;
    int returnValue;
    int count1=1,count2=1,count3=1,count4=1;
    if(player==1){
        char_Player='X';
        returnValue=10;
    }
    else if(player==2){
        char_Player='O';
        returnValue=-10;
    }
    int r=row;
    int c=column;
    int tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
    bool left=true,right=true,up=true,down=true,leftUp=true,leftdown=true,rightUp=true,rightDown=true;

    //checking if we have winning row
       while(count1!=winCount){
            if((tempLeft-1)>=0 && left){
                if(board[r][tempLeft-1]!=char_Player)
                   left=false;
                tempLeft--;
            }
            else
                left=false;
            if((tempRight+1)<=columns-1 && right){
                if(board[r][tempRight+1]!=char_Player)
                   right=false;
                tempRight++;
            }
            else
                right=false;
            if(left && right)
                count1=count1+2;
            else if(left || right)
                count1++;
            if(count1>=winCount && (left || right)){
                return returnValue;
            }
            if(!(left || right)){
                break;
            }
       }
       //count=1;

       //checking if we have winning column
        while(count2!=winCount){
            if((tempUp-1)>=0 && up){
                if(board[tempUp-1][c]!=char_Player)
                   up=false;
                tempUp--;
            }
            else
                up=false;
            if((tempDown+1)<=rows-1 && down){
                if(board[tempDown+1][c]!=char_Player)
                   down=false;
                tempDown++;
            }
            else
                down=false;
            if(up && down)
                count2=count2+2;
            else if(up || down)
                count2++;
            if(count2>=winCount && (up || down)){
                return returnValue;
            }
            if(!(up || down)){
                break;
            }
       }
       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       //count=1;

       while(count3!=winCount){
            if((tempUp-1)>=0 && (tempRight+1)<=columns-1 && rightUp){
                if(board[tempUp-1][tempRight+1]!=char_Player)
                   rightUp=false;
                tempUp--;
                tempRight++;
            }
            else
                rightUp=false;
            if((tempDown+1)<=rows-1 && (tempLeft-1)>=0 && leftdown){
                if(board[tempDown+1][tempLeft-1]!=char_Player)
                   leftdown=false;
                tempDown++;
                tempLeft--;
            }
            else
                leftdown=false;
            if(rightUp && leftdown)
                count3=count3+2;
            else if(rightUp || leftdown)
                count3++;
            if(count3>=winCount && (rightUp || leftdown)){
                return returnValue;
            }
            if(!(rightUp || leftdown)){
                break;
            }
       }


       tempLeft=c,tempRight=c,tempUp=r,tempDown=r;
       //count=1;

       while(count4!=winCount){
            if((tempUp-1)>=0 && (tempLeft-1)>0 && leftUp){
                if(board[tempUp-1][tempLeft-1]!=char_Player)
                   leftUp=false;
                tempUp--;
                tempLeft--;
            }
            else
                leftUp=false;
            if((tempDown+1)<=rows-1 && (tempRight+1)<=columns-1 && rightDown){
                if(board[tempDown+1][tempRight+1]!=char_Player)
                   rightDown=false;
                tempDown++;
                tempRight++;
            }
            else
                rightDown=false;
            if(leftUp && rightDown)
                count4=count4+2;
            else if (leftUp || rightDown)
                count4++;
            if(count4>=winCount && (leftUp || rightDown)){
                return returnValue;
            }
            if(!(leftUp || rightDown)){
                break;
            }
       }
       int count= max(count1,count2);
        count= max(count,count3);
        count= max(count,count4);
       // cout<<"Count1: "<<count1<<" ";
        //cout<<"Count2: "<<count2<<" ";
        //cout<<"Count3: "<<count3<<" ";
        //cout<<"Max Count: "<<count<<" "<<endl;
       if(player==2){
          return -count;
       }
       return count;
       //return 0;
}

int Board::evaluateFunction2(int player,int row,int column){
        char cplayer='X';
        int result=10;

    if(player==2){
         cplayer='O';
         result=-10;
    }

    if((board[row][column]==cplayer && (column-1)>=0 && board[row][column-1]==cplayer && (column-2)>=0 && board[row][column-2]==cplayer && (column-3)>=0
        && board[row][column-3]==cplayer) ||
       (board[row][column]==cplayer && (column+1)<7 && board[row][column+1]==cplayer && (column+2)<7 && board[row][column+2]==cplayer
        && (column+3)<7 && board[row][column+3]==cplayer) ||
        (board[row][column]==cplayer && (column-1)>=0 && board[row][column-1]==cplayer &&(column+1)<7 && board[row][column+1]==cplayer &&
         (column+2)<7 && board[row][column+2]==cplayer) ||
       (board[row][column]==cplayer && (column+1)<7 && board[row][column+1]==cplayer && (column-1)>=0 &&  board[row][column-1]==cplayer &&
         (column-2)>=0 && board[row][column-2]==cplayer))
        return result;

    if((board[row][column]==cplayer && board[row-1][column]==cplayer && board[row-2][column]==cplayer && board[row-3][column]==cplayer
        && (row-1)>=0 && (row-2)>=0 && (row-3)>=0) ||
       (board[row][column]==cplayer && board[row+1][column]==cplayer && board[row+2][column]==cplayer && board[row+3][column]==cplayer
        && (row+1)<6 && (row+2)<6 && (row+3)<6) ||
       (board[row][column]==cplayer && board[row+1][column]==cplayer && board[row-1][column]==cplayer && board[row-2][column]==cplayer
        && (row+1)<6 && (row-1)>=0 && (row-2)>=0) ||
       (board[row][column]==cplayer && board[row-1][column]==cplayer && board[row+1][column]==cplayer && board[row+2][column]==cplayer
        && (row-1)>=0 && (row+1)<6 && (row+2)<6))
        return result;

    if((board[row][column]==cplayer && board[row-1][column-1]==cplayer && board[row-2][column-2]==cplayer && board[row-3][column-3]==cplayer
        && (row-1)>=0 && (row-2)>=0 && (row-3)>=0 && (column-1)>=0 && (column-2)>=0 && (column-3)>=0) ||
       (board[row][column]==cplayer && board[row+1][column+1]==cplayer && board[row+2][column+2]==cplayer && board[row+3][column+3]==cplayer
        && (row+1)<6 && (row+2)<6 && (row+3)<6 && (column+1)<7 && (column+2)<7 && (column+3)<7) ||
       (board[row][column]==cplayer && board[row+1][column+1]==cplayer && board[row-1][column-1]==cplayer && board[row-2][column-2]==cplayer
        && (row+1)<6 && (column+1)<7 && (row-1)>=0 && (row-2)>=0 && (column-1)>=0 && (column-2)>=0) ||
       (board[row][column]==cplayer && board[row-1][column-1]==cplayer && board[row+1][column+1]==cplayer && board[row+2][column+2]==cplayer
        && (row-1)>=0 && (column-1)>=0 && (row+1)<6 && (row+2)<6 && (column+1)<7 && (column+2)<7))
        return result;
  //  char ch=board[row+3][column-3];
    if((board[row][column]==cplayer && board[row+1][column-1]==cplayer && board[row+2][column-2]==cplayer && board[row+3][column-3]==cplayer
        && (row+1)<6 && (row+2)<6 && (row+3)<6 && (column-1)>=0 && (column-2)>=0 && (column-3)>=0) ||

        (board[row][column]==cplayer && board[row-1][column+1]==cplayer && board[row-2][column+2]==cplayer && board[row-3][column+3]==cplayer
         && (row-1)>=0 && (row-2)>=0 && (row-3)>=0 && (column+1)<7 && (column+2)<7 && (column+3)<7) ||
       (board[row][column]==cplayer && board[row+1][column-1]==cplayer && board[row-1][column+1]==cplayer && board[row-2][column+2]==cplayer
        && (row+1)<6 && (row-1)>=0 && (row-2)>=0 && (column-1)>=0 && (column+1)<7 && (column+2)<7 ) ||
       (board[row][column]==cplayer && board[row-1][column+1]==cplayer && board[row+1][column-1]==cplayer && board[row+2][column-2]==cplayer
        && (row-1)>=0 && (row+1)<6 && (row+2)<6 && (column-1)>=0 && (column+1)<7 && (column-2)>=0))
       return result;

    return 0;
}

