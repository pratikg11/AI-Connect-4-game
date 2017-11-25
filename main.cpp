#include<iostream>
#include"Board.h"
#include"Board.cpp"
#include"Ai_Player.h"
#include"Ai_Player.cpp"
#include <time.h>
#include <stdio.h>
//#include"psapi.h"
using namespace std;


int main()
{
    clock_t tStart = clock();
    int noOfNodes=0;
    int choice,totalPossibleMoves=42;
    int count=0;
    bool result=true;
    Board b;
    Ai_Player a;
    char c='y';
    cout<<"Select 1 choice"<<endl;
    cout<<"1.Minimax Algorithm"<<endl;
    cout<<"2.Minimax using alpha beta pruning"<<endl;
    cin>>choice;
    //choice=1;
    //cout<<"Do u want to start 1st with X(Y/N)";
   // cin>>c;

//   b.setValue(5,5,'0');
//   b.setValue(5,4,'0');
//   b.setValue(5,3,'0');
//   b.setValue(5,2,'0');
//   b.setValue(4,4,'0');
//   b.setValue(4,3,'0');
//   b.setValue(4,2,'0');
//   b.setValue(3,3,'0');
  // b.setValue(1,0,'X');
////////    if(c=='y'){
////////            while(result)
////////            {
////////                b.displayBoard();
////////                int i=b.userPerformMove(1);
////////                if(i==1)
////////                    result=false;
////////                else if(i==2)
////////                    result=true;
////////                else if(i==0){
////////                    int j=a.AIperformMove(b,choice);
////////                    b.displayBoard();
////////                    if(j==-10)
////////                    {
////////                       b.displayBoard();
////////                       cout<<"Player 2 wins";
////////                       result=false;
////////                    }
////////
////////                }
////////                count=count+2;
////////                if(count==totalPossibleMoves)
////////                {
////////                    cout<<"Game is Over. Its a draw"<<endl;
////////                    result=false;
////////                }
////////            }
////////
////////    }


while(result)
{
    int j=a.AIperformMove(b,choice,1,noOfNodes);
    cout<<endl<<"Player 1 move : ";
     b.displayBoard();
                    if(j==10)
                    {
                       b.displayBoard();
                       cout<<"Player 1 wins";
                       result=false;
                    }
        if(result){
        int k=a.AIperformMove(b,choice,2,noOfNodes);
        cout<<endl<<"Player 2 move : ";
        b.displayBoard();
                    if(k==-10)
                    {
                       b.displayBoard();
                       cout<<"Player 2 wins";
                       result=false;
                    }

    count=count+2;
                if(j!=10 && k!=-10){
                if(count==totalPossibleMoves)
                {
                    cout<<"Game is Over. Its a draw"<<endl;
                    result=false;
                }
                }
}

}
cout<<endl<<"No of Nodes Generated : "<<noOfNodes<<endl;
cout<<"No of Ticks: "<< (double)(clock() - tStart)<<endl;
cout<<"Clocks per sec: "<<CLOCKS_PER_SEC<<endl;
cout<<"Time taken: "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;




//PROCESS_MEMORY_COUNTERS memCounter;
//bool result2 = GetProcessMemoryInfo(GetCurrentProcess(),
//                                   &memCounter,
//                                   sizeof( memCounter ));
//cout<<result2;
   // else
      //  a.AIperformMove(b);
}
