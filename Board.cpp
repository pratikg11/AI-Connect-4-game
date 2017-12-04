#include<iostream>
#include"Board.h"
using namespace std;
//Setting initial values empty
Board::Board() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			board[i][j] = ' ';
		}
}

//checking if board is filled
bool Board::isBoardFilled() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (board[i][j] == ' ')
				return false;
		}
	}
	return true;
}

//Displaying the board
void Board::displayBoard() {
	cout << endl;
	cout << "  ";
	int i;
	for (i = 0; i < columns; i++)
		cout << " |C" << i;
	cout << " | ";
	cout << endl << "  ----------------------------" << endl;
	for (i = 0; i < rows; i++) {
		cout << "R" << rows - 1 - i << " | ";
		for (int j = 0; j < columns; j++) {
			cout << board[i][j] << " | ";
		}
		cout << endl;
	}
	cout << "  ----------------------------" << endl;
}

//setting values in the board
void Board::setValue(int x, int y, char c) {
	board[x][y] = c;
}

//getting the values from board
char Board::getValue(int x, int y) {
	return board[x][y];
}

//Evaluation function made by pratik Ghogale
int Board::evaluateFunction1(int player, int row, int column) {
	char char_Player;
	int count = -100;
	int count1 = 1;
	if (player == 1) {
		char_Player = 'X';
	} else if (player == 2) {
		char_Player = 'O';
	}
	tempLeft = column, tempRight = column, tempUp = row, tempDown = row;

	//checking if we have winning row
	while (count1 <= winCount) {
		if ((tempLeft - 1) >= 0 && left) {
			if (board[row][tempLeft - 1] != char_Player)
				left = false;
			tempLeft--;
		} else
			left = false;
		if ((tempRight + 1) <= columns - 1 && right) {
			if (board[row][tempRight + 1] != char_Player)
				right = false;
			tempRight++;
		} else
			right = false;
		if (left && right)
			count1 = count1 + 2;
		else if (left || right)
			count1++;
		if (count1 >= winCount && (left || right)) {
			if (player == 1) {
				return 10;
			} else if (player == 2) {
				return -10;
			}
		}
		if (!(left || right)) {
			break;
		}
	}
	count = max(count1, count);
	count1 = 1;
	//count=1;

	//checking if we have winning column
	while (count1 <= winCount) {
		if ((tempUp - 1) >= 0 && up) {
			if (board[tempUp - 1][column] != char_Player)
				up = false;
			tempUp--;
		} else
			up = false;
		if ((tempDown + 1) <= rows - 1 && down) {
			if (board[tempDown + 1][column] != char_Player)
				down = false;
			tempDown++;
		} else
			down = false;
		if (up && down)
			count1 = count1 + 2;
		else if (up || down)
			count1++;
		if (count1 >= winCount && (up || down)) {
			if (player == 1) {
				return 10;
			} else if (player == 2) {
				return -10;
			}
		}
		if (!(up || down)) {
			break;
		}
	}
	count = max(count1, count);
	count1 = 1;
	tempLeft = column, tempRight = column, tempUp = row, tempDown = row;

//Checking if we have winning diagonal 1
	while (count1 <= winCount) {
		if ((tempUp - 1) >= 0 && (tempRight + 1) <= columns - 1 && rightUp) {
			if (board[tempUp - 1][tempRight + 1] != char_Player)
				rightUp = false;
			tempUp--;
			tempRight++;
		} else
			rightUp = false;
		if ((tempDown + 1) <= rows - 1 && (tempLeft - 1) >= 0 && leftdown) {
			if (board[tempDown + 1][tempLeft - 1] != char_Player)
				leftdown = false;
			tempDown++;
			tempLeft--;
		} else
			leftdown = false;
		if (rightUp && leftdown)
			count1 = count1 + 2;
		else if (rightUp || leftdown)
			count1++;
		if (count1 >= winCount && (rightUp || leftdown)) {
			if (player == 1) {
				return 10;
			} else if (player == 2) {
				return -10;
			}
		}
		if (!(rightUp || leftdown)) {
			break;
		}
	}
	count = max(count1, count);
	count1 = 1;

	tempLeft = column, tempRight = column, tempUp = row, tempDown = row;

//Checking if we have winning diagonal 2
	while (count1 <= winCount) {
		if ((tempUp - 1) >= 0 && (tempLeft - 1) >= 0 && leftUp) {
			if (board[tempUp - 1][tempLeft - 1] != char_Player)
				leftUp = false;
			tempUp--;
			tempLeft--;
		} else
			leftUp = false;
		if ((tempDown + 1) <= rows - 1 && (tempRight + 1) <= columns - 1
				&& rightDown) {
			if (board[tempDown + 1][tempRight + 1] != char_Player)
				rightDown = false;
			tempDown++;
			tempRight++;
		} else
			rightDown = false;
		if (leftUp && rightDown)
			count1 = count1 + 2;
		else if (leftUp || rightDown)
			count1++;
		if (count1 >= winCount && (leftUp || rightDown)) {
			if (player == 1) {
				return 10;
			} else if (player == 2) {
				return -10;
			}
		}
		if (!(leftUp || rightDown)) {
			break;
		}
	}
	count = max(count1, count);
	left = true, right = true, up = true, down = true, leftUp = true, leftdown =
			true, rightUp = true, rightDown = true;
	tempLeft = 0, tempRight = 0, tempUp = 0, tempDown = 0;
	if (player == 2) {
		return -count;
	}
	return count;
}
