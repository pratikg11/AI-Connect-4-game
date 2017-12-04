#include<iostream>
#include"Board.h"
#include"Board.cpp"
#include"AI_Player.h"
#include"AI_Player.cpp"
#include <time.h>
#include <stdio.h>
using namespace std;

int main() {
	int noOfNodes = 0;
	int countminus = 0;
	int pathLength = 0;
	int choice, totalPossibleMoves = 42;
	int evaluateFunctionNo=1;
	int count = 0;
	bool result = true;
	Board b;
	Ai_Player a;
	//Selecting the algorithm
	do {
		cout << "Select 1 choice" << endl;
		cout << "1.Minimax Algorithm" << endl;
		cout << "2.Minimax using alpha beta pruning" << endl;
		cin >> choice;
		if (choice <= 0 || choice >= 3)
			cout << "Invalid Choice.. Please Select Proper Choice" << endl;
	} while (choice <= 0 || choice >= 3);

	//Setting start time
	clock_t tStart = clock();
	while (result) {
		pathLength++;
		int j = a.AIperformMove(b, choice, 1, noOfNodes, countminus,
				evaluateFunctionNo);
		cout << endl << "Player 1 move : ";
		b.displayBoard();
		if (j == 10) {
			cout << "Player 1 wins";
			result = false;
		}
		if (result) {
			pathLength++;
			int k = a.AIperformMove(b, choice, 2, noOfNodes, countminus,
					evaluateFunctionNo);
			cout << endl << "Player 2 move : ";
			b.displayBoard();
			if (k == -10) {
				cout << "Player 2 wins";
				result = false;
			}

			count = count + 2;
			if (j != 10 && k != -10) {
				if (count == totalPossibleMoves) {
					cout << "Game is Over. Its a draw" << endl;
					result = false;
				}
			}
		}

	}
	cout << endl << "No of Nodes Generated is : " << noOfNodes << endl;
	cout << "No of Nodes Expanded : " << noOfNodes - countminus << endl;
	if (choice == 1) {
		if (evaluateFunctionNo == 1) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 149) + 143 << " Bytes" << endl;
		} else if (evaluateFunctionNo == 2) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 165) + 143 << " Bytes" << endl;
		} else if (evaluateFunctionNo == 3) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 145) + 143 << " Bytes" << endl;
		}
	} else if (choice == 2) {

		if (evaluateFunctionNo == 1) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 150) + 143 << " Bytes" << endl;
		} else if (evaluateFunctionNo == 2) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 166) + 143 << " Bytes" << endl;
		} else if (evaluateFunctionNo == 3) {
			cout << "The size of memory used by the program is : "
					<< (noOfNodes * 146) + 143 << " Bytes" << endl;
		}
	}
	cout << "The total length of the game path is : " << pathLength << endl;
//the total time for program
	cout << "Time taken is : " << (double) (clock() - tStart) / CLOCKS_PER_SEC
			<< " seconds" << endl;

}
