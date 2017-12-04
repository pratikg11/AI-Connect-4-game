#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board {
private:
	char board[6][7];
	int rows = 6;
	int columns = 7;
	int winCount = 4;
	int playerX = 1;
	int playerO = 2;
	bool left = true, right = true, up = true, down = true, leftUp = true,
			leftdown = true, rightUp = true, rightDown = true;
	int tempLeft = 0, tempRight = 0, tempUp = 0, tempDown = 0;

public:
	Board();
	int checkIfPlayerWins(int, int, int);
	int performMove(int, int);
	void displayBoard();
	int getInput();
	int userPerformMove(int);
	int getRowNo();
	int getColumnNo();
	bool checkInsertRule(int, int);
	bool isBoardFilled();
	void setValue(int, int, char);
	char getValue(int, int);
	int evaluateFunction1(int, int, int);
	int evaluateFunction2(int, int, int);
	int evaluateFunction3(int, int, int);
};

#endif // BOARD_H_INCLUDED
