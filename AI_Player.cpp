#include<iostream>
#include<cmath>
#include <stdlib.h>
#include <time.h>
#include"Ai_Player.h"
#include"Board.h"
//#include"Board.cpp"

using namespace std;

Score Ai_Player::moveGen(Board board,int depth,int player, int &noOfNodes)
{
     if(player==playerO)
    {
        Score best;
        best.value = 1000;
        best.depth=-1;
        //int best = 1000;

        // Traverse all cells
        for (int i = 0; i<rows; i++)
        {
            for (int j = 0; j<columns; j++)
            {
                // Check if cell is empty
                if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
                {
                    // Make the move
//                    int valuex,valuey;
                    board.setValue(i,j,'O');
//                    for(int k=0;k<rows;k++){
//                        bool result=false;
//                        for(int l=0;l<columns;l++){
//                            if ((k==rows-1 && board.getValue(k,l)==' ')||(board.getValue(k,l)==' ' && board.getValue(k+1,l)!=' ')){
//                                valuex=k;
//                                valuey=l;
//                                result=true;
//                                break;
//                            }
//                        }
//                        if(result)
//                            break;
//                    }


                    // Call minimax recursively and choose
                    // the minimum value
                    //best = min(best,performMinimax(board, depth+1, playerX,i,j,noOfNodes));
                   // best=performMinimax(board, depth+1, playerX,i,j,noOfNodes);
                    Score tempBest=performMinimax(board, depth+1, playerX,i,j,noOfNodes);
                    if(best.value==tempBest.value){
                        if(tempBest.depth<best.depth){
                            best=tempBest;
                        }
                    }
                    else{
                        best.value=min(best.value,tempBest.value);
                        best.depth=depth;
                    }


       //                    cout<<"Min Turn..at depth"<<depth<<"..putting at"<<i<<","<<j<<" best value : "<<best<<endl;
                    // Undo the move
                    board.setValue(i,j,' ');
                }
            }
        }
        return best;
    }
    else if(player==playerX){

        //int best = -1000;
        Score best;
        best.value =-1000;
        best.depth=-1;
        // Traverse all cells
        for (int i = 0; i<rows; i++)
        {
            for (int j = 0; j<columns; j++)
            {
                // Check if cell is empty
                if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
                {
                    // Make the move
//                    int valuex,valuey;
                    board.setValue(i,j,'X');
//                    for(int k=0;k<rows;k++){
//                        bool result=false;
//                        for(int l=0;l<columns;l++){
//                            if ((k==rows-1 && board.getValue(k,l)==' ')||(board.getValue(k,l)==' ' && board.getValue(k+1,l)!=' ')){
//                                valuex=k;
//                                valuey=l;
//                                result=true;
//                                break;
//                            }
//                        }
//                        if(result)
//                            break;
//                    }
//                    cout<<"Value of i "<<valuex<<" and value of j"<<valuey<<endl;
                    // Call minimax recursively and choose
                    // the maximum value
                   //// best = performMinimax(board, depth+1, playerX,i,j,noOfNodes);
                     Score tempBest=performMinimax(board, depth+1, playerO,i,j,noOfNodes);
                    if(best.value==tempBest.value){
                        if(tempBest.depth<best.depth){
                            best=tempBest;
                        }
                    }
                    else{
                        best.value=max(best.value,tempBest.value);
                        best.depth=depth;
                    }
                    //best.depth=depth;
                    //cout<<"Max Turn..at depth "<<depth<<"..putting at"<<i<<","<<j<<" best value : "<<best<<endl;
                    // Undo the move
                    board.setValue(i,j,' ');
                }
            }
        }
        return best;
    }
}

bool Ai_Player::deepEnough(int depth){
if(depth>=3)
    return true;
return false;
}

void Ai_Player::temp(Board& b){
    b.setValue(0,1,'O');
}

int Ai_Player::AIperformMove(Board& board,int choice,int player,int &noOfNodes){
    if(player==playerO){
    AI_Move ai_move=getBestMove(board,choice,player,noOfNodes);
    board.setValue(ai_move.x,ai_move.y,'O');
    return board.evaluateFunction(playerO,ai_move.x,ai_move.y);
    }
    else if(player==playerX){
    AI_Move ai_move=getBestMove(board,choice,player,noOfNodes);
    board.setValue(ai_move.x,ai_move.y,'X');
    return board.evaluateFunction(playerX,ai_move.x,ai_move.y);
    }

}

Score Ai_Player::performMinimax(Board board, int depth,int player,int row,int column,int &noOfNodes){
    noOfNodes++;
    //int score;
    Score score;
    score.depth=depth-1;
    if(player==playerO){
         score.value=board.evaluateFunction(playerX,row,column);
         if(score.value!=10){
            score.value=board.evaluateFunction(playerO,row,column);
            if (score.value == -10){
               score.value=10;
               return score;
            }
         }
    }
    else if(player==playerX){
         score.value=board.evaluateFunction(playerO,row,column);
         if(score.value!=-10){
            score.value=board.evaluateFunction(playerX,row,column);
            if (score.value == 10){
               score.value=-10;
               return score;
            }
         }
    }
    //cout<<"working"<<endl;
    if (score.value == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score.value == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (board.isBoardFilled()){
        score.value=0;
        return score;
    }

    if(deepEnough(depth)){
         //score.value=0;
        return score;
    }
    return moveGen(board,depth,player,noOfNodes);
}

Score Ai_Player::moveGen_alfabetaPruning(Board board,int depth,int player,int alpha, int beta,int &noOfNodes)
{
     if(player==playerO)
    {
       // int best = 1000;
        Score best;
        best.value = 1000;
        best.depth=-1;

        // Traverse all cells
        for (int i = 0; i<rows; i++)
        {
            bool breakResult=false;
            for (int j = 0; j<columns; j++)
            {
                // Check if cell is empty
                if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
                {
                    // Make the move
//                    int valuex,valuey;
                    board.setValue(i,j,'O');
//                    for(int k=0;k<rows;k++){
//                        bool result=false;
//                        for(int l=0;l<columns;l++){
//                            if ((k==rows-1 && board.getValue(k,l)==' ')||(board.getValue(k,l)==' ' && board.getValue(k+1,l)!=' ')){
//                                valuex=k;
//                                valuey=l;
//                                result=true;
//                                break;
//                            }
//                        }
//                        if(result)
//                            break;
//                    }
                    // Call minimax recursively and choose
                    // the minimum value
                   Score tempBest=performMinimax(board, depth+1, playerX,i,j,noOfNodes);
                    if(best.value==tempBest.value){
                        if(tempBest.depth<best.depth){
                            best=tempBest;
                        }
                    }
                    else{
                        best.value=min(best.value,tempBest.value);
                        best.depth=depth;
                    }
               // cout<<"Min Turn....putting at"<<i<<","<<j<<" best value : "<<best<<endl;
                    // Undo the move
                    board.setValue(i,j,' ');
            beta = min(beta, best.value);
           // cout<<"min called";
            // Alpha Beta Pruning
            if (beta <= alpha){
                breakResult=true;
                   // cout<<" min called"<<endl;
                break;
            }

                }
            }
            if(breakResult)
                break;
        }
        return best;
    }
    else if(player==playerX){

       // int best = -1000;
        Score best;
        best.value = -1000;
        best.depth=-1;
        // Traverse all cells
        for (int i = 0; i<rows; i++)
        {
            bool breakResult=false;
            for (int j = 0; j<columns; j++)
            {
                // Check if cell is empty
                if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
                {
                    // Make the move
//                    int valuex,valuey;
                    board.setValue(i,j,'X');
//
//                    for(int k=0;k<rows;k++){
//                        bool result=false;
//                        for(int l=0;l<columns;l++){
//                            if ((k==rows-1 && board.getValue(k,l)==' ')||(board.getValue(k,l)==' ' && board.getValue(k+1,l)!=' ')){
//                                valuex=k;
//                                valuey=l;
//                                result=true;
//                                break;
//                            }
//                        }
//                        if(result)
//                            break;
//                    }
                    // Call minimax recursively and choose
                    // the maximum value
                    Score tempBest=performMinimax(board, depth+1, playerO,i,j,noOfNodes);
                    if(best.value==tempBest.value){
                        if(tempBest.depth<best.depth){
                            best=tempBest;
                        }
                    }
                    else{
                        best.value=max(best.value,tempBest.value);
                        best.depth=depth;
                    }
                   // cout<<"Max Turn....putting at"<<i<<","<<j<<" best value : "<<best<<endl;
                    // Undo the move
                    board.setValue(i,j,' ');
                    alpha = max(alpha, best.value);

                    // Alpha Beta Pruning
                    if (beta <= alpha){
                         //   cout<<" max called"<<endl;
                          breakResult=true;
                    break;
                    }
                }
            }
            if(breakResult)
                break;
        }
        return best;
    }
}

Score Ai_Player::performMinimax_alfabetaPruning(Board board,int depth,int player,int row,int column,int alpha,int beta, int &noOfNodes)
{
    noOfNodes++;
     //int score;
     Score score;
    score.depth=depth-1;
    if(player==playerO){
         score.value=board.evaluateFunction(playerX,row,column);
          if(score.value!=10){
            score.value=board.evaluateFunction(playerO,row,column);
            if (score.value == -10){
               score.value=10;
               return score;
            }
         }
    }
    else if(player==playerX){
         score.value=board.evaluateFunction(playerO,row,column);
         if(score.value!=-10){
            score.value=board.evaluateFunction(playerX,row,column);
            if (score.value == 10){
               score.value=-10;
               return score;
            }
         }
    }
    //cout<<"working"<<endl;
    if (score.value == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score.value == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (board.isBoardFilled()){
        score.value=0;
        return score;
    }

    if(deepEnough(depth)){
        return score;
    }

    return moveGen_alfabetaPruning(board,depth,player,alpha,beta,noOfNodes);
}

AI_Move Ai_Player::getBestMove(Board board,int choice,int player,int &noOfNodes){
   AI_Move bestMove;
   int count1,count;
    srand(time(0));
    int arr1[6];
    int arr[7];
//    if(player==playerO){
//    for (int i = 0; i<rows; i++)
//    {
//        for (int j = 0; j<columns; j++)
//        {
//            // Check if celll is empty
//            if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
//            {
//               int result= board.checkIfPlayerWins(playerO,i,j);
//               if(result==-10){
//                bestMove.x=i;
//                bestMove.y=j;
//                return bestMove;
//               }
//               result=board.checkIfPlayerWins(playerX,i,j);
//               if(result==10){
//                bestMove.x=i;
//                bestMove.y=j;
//                return bestMove;
//               }
//            }
//        }
//    }
//    }
//    if(player==playerX){
//    for (int i = 0; i<rows; i++)
//    {
//        for (int j = 0; j<columns; j++)
//        {
//            // Check if celll is empty
//            if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
//            {
//               int result= board.checkIfPlayerWins(playerX,i,j);
//               if(result==10){
//                bestMove.x=i;
//                bestMove.y=j;
//                return bestMove;
//               }
//               result=board.checkIfPlayerWins(playerO,i,j);
//               if(result==-10){
//                bestMove.x=i;
//                bestMove.y=j;
//                return bestMove;
//               }
//            }
//        }
//    }
//    }


   switch(player){

case 1:

    bestMove.score=-100;
    bestMove.x = -1;
    bestMove.y = -1;
    bestMove.depth=-1;



//    for (int i = 0; i<rows; i++)
//    {
//        for (int j = 0; j<columns; j++)
//        {
//            // Check if cell is empty
//            if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
//            {
//                // Make the move
//                int valOfMove;
//                board.setValue(i,j,'X');
//
//                // compute evaluation function for this
//                // move.
//                if(choice==1)
//                 valOfMove = performMinimax(board, 0, playerO,i,j);
//                else if(choice==2)
//                 valOfMove = performMinimax_alfabetaPruning(board, 0, playerO,i,j,100,-100);
//
//                // Undo the move
//                board.setValue(i,j,' ');
//
//                // If the value of the current move is
//                // more than the best value, then update
//                // best/
//                if (valOfMove > bestMove.score)
//                {
//                    bestMove.x = i;
//                    bestMove.y = j;
//                    bestMove.score = valOfMove;
//                }
//            }
//        }
//    }
//    return bestMove;

 count1=0;
        for(int l=0;l<rows;l++){
        //cout<<rand()%10<<endl;
        arr1[l]=0;
    }
         while(count1!=6){
        int i=rand()%6;
        if(arr1[i]==0){
            arr1[i]=1;
            count1++;

        count=0;
        for(int k=0;k<columns;k++){
        //cout<<rand()%10<<endl;
        arr[k]=0;
    }
       // for (int j = 0; j<columns; j++)
        //{
            // Check if cell is empty
        while(count!=7){
        int j=rand()%7;
        if(arr[j]==0){
            arr[j]=1;
            count++;
            if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
            {
                // Make the move
                //int valOfMove;
                Score valOfMove;
                board.setValue(i,j,'X');

                // compute evaluation function for this
                // move.
                if(choice==2)
                valOfMove = performMinimax_alfabetaPruning(board, 0, playerX,i,j,100,-100,noOfNodes);
                else if(choice==1)
                 valOfMove = performMinimax(board, 0, playerO,i,j,noOfNodes);


                // Undo the move
                board.setValue(i,j,' ');

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (valOfMove.value > bestMove.score)
                {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestMove.score = valOfMove.value;
                    bestMove.depth = valOfMove.depth;
                }
                else if(valOfMove.value==bestMove.score){
                    if (valOfMove.depth < bestMove.depth)
                    {
                        bestMove.x = i;
                        bestMove.y = j;
                        bestMove.score = valOfMove.value;
                        bestMove.depth = valOfMove.depth;
                    }
                }
            }
        }
}
       // }
    }
         }
    return bestMove;

case 2:
//int bestVal = 100;
   // AI_Move bestMove;
    bestMove.score=100;
    bestMove.x = -1;
    bestMove.y = -1;
    bestMove.depth=-1;
   // for (int i = 0; i<rows; i++)
   // {
        count1=0;
        for(int l=0;l<rows;l++){
        //cout<<rand()%10<<endl;
        arr1[l]=0;
    }
         while(count1!=6){
        int i=rand()%6;
        if(arr1[i]==0){
            arr1[i]=1;
            count1++;

        count=0;
        for(int k=0;k<columns;k++){
        //cout<<rand()%10<<endl;
        arr[k]=0;
    }
       // for (int j = 0; j<columns; j++)
        //{
            // Check if cell is empty
        while(count!=7){
        int j=rand()%7;
        if(arr[j]==0){
            arr[j]=1;
            count++;
            if ((i==rows-1 && board.getValue(i,j)==' ')||(board.getValue(i,j)==' ' && board.getValue(i+1,j)!=' '))
            {


                // Make the move
                //int valOfMove;
                Score valOfMove;
                board.setValue(i,j,'O');

                // compute evaluation function for this
                // move.
                if(choice==2)
                 valOfMove = performMinimax_alfabetaPruning(board, 0, playerX,i,j,100,-100,noOfNodes);
                else if(choice==1)
                 valOfMove = performMinimax(board, 0, playerX,i,j,noOfNodes);

                // Undo the move
                board.setValue(i,j,' ');

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (valOfMove.value < bestMove.score)
                {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestMove.score = valOfMove.value;
                    bestMove.depth = valOfMove.depth;
                }
                else if(valOfMove.value==bestMove.score){
                    if (valOfMove.depth < bestMove.depth)
                    {
                        bestMove.x = i;
                        bestMove.y = j;
                        bestMove.score = valOfMove.value;
                        bestMove.depth = valOfMove.depth;
                    }
                }
            }
        }
}
       // }
    }
         }
    return bestMove;
    }
}

