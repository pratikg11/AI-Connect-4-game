#include<iostream>
#include<cmath>
#include <stdlib.h>
#include <time.h>
#include"AI_Player.h"
#include"Board.h"

using namespace std;
//Move-Gen function which is plausible-move generator
Score Ai_Player::moveGen(Board board, int depth, int player, int &noOfNodes,
		int &countminus, int evaluateFunctionNo) {
	if (player == playerO) {
		Score best;
		best.value = 1000;
		best.depth = -1;

		// Traverse through the rows
		for (int i = 0; i < rows; i++) {
			// Traverse through the columns
			for (int j = 0; j < columns; j++) {
				// Check if cell is empty
				if ((i == rows - 1 && board.getValue(i, j) == ' ')
						|| (board.getValue(i, j) == ' '
								&& board.getValue(i + 1, j) != ' ')) {
					// Set the value
					board.setValue(i, j, 'O');
					//calling Minimax function
					Score tempBest = performMinimax(board, depth + 1, playerX,
							i, j, noOfNodes, countminus, evaluateFunctionNo);

					//getting best value
					if (best.value == 10 && tempBest.value == 10) {
						if (tempBest.depth > best.depth) {
							best = tempBest;
						}
					} else if (best.value == tempBest.value) {
						if (tempBest.depth < best.depth) {
							best = tempBest;
						}
					} else {
						best.value = min(best.value, tempBest.value);
						best.depth = depth;
					}

					// again setting the value of the position to empty
					board.setValue(i, j, ' ');
				}
			}
		}
		return best;
	} else if (player == playerX) {

		//int best = -1000;
		Score best;
		best.value = -1000;
		best.depth = -1;
		//  // Traverse through the rows
		for (int i = 0; i < rows; i++) {
			// Traverse through the columns
			for (int j = 0; j < columns; j++) {
				// Check if cell is empty
				if ((i == rows - 1 && board.getValue(i, j) == ' ')
						|| (board.getValue(i, j) == ' '
								&& board.getValue(i + 1, j) != ' ')) {
					// Set the value
					board.setValue(i, j, 'X');
					//calling Minimax function
					Score tempBest = performMinimax(board, depth + 1, playerO,
							i, j, noOfNodes, countminus, evaluateFunctionNo);
					//getting best value
					if (best.value == -10 && tempBest.value == -10) {
						if (tempBest.depth > best.depth) {
							best = tempBest;
						}
					} else if (best.value == tempBest.value) {
						if (tempBest.depth < best.depth) {
							best = tempBest;
						}
					} else {
						best.value = max(best.value, tempBest.value);
						best.depth = depth;
					}

					// again setting the value of the position to empty
					board.setValue(i, j, ' ');
				}
			}
		}
		return best;
	}
}

//checking the depth
bool Ai_Player::deepEnough(int depth) {
	if (depth >= 3)
		return true;
	return false;
}

//Performing move
int Ai_Player::AIperformMove(Board& board, int choice, int player,
		int &noOfNodes, int &countminus, int evaluateFunctionNo) {
	//If payer is player 2
	if (player == playerO) {
		AI_Move ai_move = getBestMove(board, choice, player, noOfNodes,
				countminus, evaluateFunctionNo);
		board.setValue(ai_move.x, ai_move.y, 'O');
		if (evaluateFunctionNo == 1)
			return board.evaluateFunction1(playerO, ai_move.x, ai_move.y);
		else if (evaluateFunctionNo == 2)
			return board.evaluateFunction2(playerO, ai_move.x, ai_move.y);
		else if (evaluateFunctionNo == 3)
			return board.evaluateFunction3(playerO, ai_move.x, ai_move.y);
	}
	//If payer is player 1
	else if (player == playerX) {
		AI_Move ai_move = getBestMove(board, choice, player, noOfNodes,
				countminus, evaluateFunctionNo);
		board.setValue(ai_move.x, ai_move.y, 'X');
		if (evaluateFunctionNo == 1)
			return board.evaluateFunction1(playerX, ai_move.x, ai_move.y);
		else if (evaluateFunctionNo == 2)
			return board.evaluateFunction2(playerX, ai_move.x, ai_move.y);
		else if (evaluateFunctionNo == 3)
			return board.evaluateFunction3(playerX, ai_move.x, ai_move.y);
	}

}

//Performing Minimax
Score Ai_Player::performMinimax(Board board, int depth, int player, int row,
		int column, int &noOfNodes, int &countminus, int evaluateFunctionNo) {
	noOfNodes++;
	Score score;
	score.depth = depth - 1;
	//If payer is player 2
	if (player == playerO) {
		if (evaluateFunctionNo == 1)
			score.value = board.evaluateFunction1(playerX, row, column);
		else if (evaluateFunctionNo == 2)
			score.value = board.evaluateFunction2(playerX, row, column);
		else if (evaluateFunctionNo == 3)
			score.value = board.evaluateFunction3(playerX, row, column);
		if (score.value != 10) {
			if (evaluateFunctionNo == 1)
				score.value = board.evaluateFunction1(playerO, row, column);
			else if (evaluateFunctionNo == 2)
				score.value = board.evaluateFunction2(playerO, row, column);
			else if (evaluateFunctionNo == 3)
				score.value = board.evaluateFunction3(playerO, row, column);
			if (score.value == -10) {
				countminus++;
				score.value = 10;
				return score;
			}
		}
	}
	//If payer is player 1
	else if (player == playerX) {
		if (evaluateFunctionNo == 1)
			score.value = board.evaluateFunction1(playerO, row, column);
		else if (evaluateFunctionNo == 2)
			score.value = board.evaluateFunction2(playerO, row, column);
		else if (evaluateFunctionNo == 3)
			score.value = board.evaluateFunction3(playerO, row, column);
		if (score.value != -10) {
			if (evaluateFunctionNo == 1)
				score.value = board.evaluateFunction1(playerX, row, column);
			else if (evaluateFunctionNo == 2)
				score.value = board.evaluateFunction2(playerX, row, column);
			else if (evaluateFunctionNo == 3)
				score.value = board.evaluateFunction3(playerX, row, column);
			if (score.value == 10) {
				countminus++;
				score.value = -10;
				return score;
			}
		}
	}
	// If Player 1 has won the game return evaluated score
	if (score.value == 10) {
		countminus++;
		return score;
	}

	// If Player 2 has won the game return evaluated score
	if (score.value == -10) {
		countminus++;
		return score;
	}

	// If it is tie return 0
	if (board.isBoardFilled()) {
		countminus++;
		score.value = 0;
		return score;
	}
	// if deep Enough is true return 0
	if (deepEnough(depth)) {
		countminus++;
		score.value = 0;
		return score;
	}
	return moveGen(board, depth, player, noOfNodes, countminus,
			evaluateFunctionNo);
}

//Move-Gen function which is plausible-move generator
Score Ai_Player::moveGen_alfabetaPruning(Board board, int depth, int player,
		int alpha, int beta, int &noOfNodes, int &countminus,
		int evaluateFunctionNo) {
	if (player == playerO) {
		Score best;
		best.value = 1000;
		best.depth = -1;

		// Traverse all rows
		for (int i = 0; i < rows; i++) {
			bool breakResult = false;
			// Traverse all columns
			for (int j = 0; j < columns; j++) {
				// Check if cell is empty
				if ((i == rows - 1 && board.getValue(i, j) == ' ')
						|| (board.getValue(i, j) == ' '
								&& board.getValue(i + 1, j) != ' ')) {
					// set the value
					board.setValue(i, j, 'O');
//
					Score tempBest = performMinimax_alfabetaPruning(board,
							depth + 1, playerX, i, j, alpha, beta, noOfNodes,
							countminus, evaluateFunctionNo);
					//get the best value
					if (best.value == 10 && tempBest.value == 10) {
						if (tempBest.depth > best.depth) {
							best = tempBest;
						}
					}
					if (best.value == tempBest.value) {
						if (tempBest.depth < best.depth) {
							best = tempBest;
						}
					} else {
						best.value = min(best.value, tempBest.value);
						best.depth = depth;
					}

					// setting the board value again to empty
					board.setValue(i, j, ' ');
					beta = min(beta, best.value);
					// alpha beta Pruning
					if (beta <= alpha) {
						breakResult = true;
						break;
					}

				}
			}
			if (breakResult)
				break;
		}
		return best;
	} else if (player == playerX) {

		Score best;
		best.value = -1000;
		best.depth = -1;
		// Traverse all rows
		for (int i = 0; i < rows; i++) {
			bool breakResult = false;
			// Traverse all columns
			for (int j = 0; j < columns; j++) {
				// Check if cell is empty
				if ((i == rows - 1 && board.getValue(i, j) == ' ')
						|| (board.getValue(i, j) == ' '
								&& board.getValue(i + 1, j) != ' ')) {
					// set the value
					board.setValue(i, j, 'X');
					// Call minimax Function
					Score tempBest = performMinimax_alfabetaPruning(board,
							depth + 1, playerO, i, j, alpha, beta, noOfNodes,
							countminus, evaluateFunctionNo);
					//get best value
					if (best.value == -10 && tempBest.value == -10) {
						if (tempBest.depth > best.depth) {
							best = tempBest;
						}
					}
					if (best.value == tempBest.value) {
						if (tempBest.depth < best.depth) {
							best = tempBest;
						}
					} else {
						best.value = max(best.value, tempBest.value);
						best.depth = depth;
					}

					// setting the board value again to empty
					board.setValue(i, j, ' ');
					alpha = max(alpha, best.value);

					// alpha beta Pruning
					if (beta <= alpha) {
						breakResult = true;
						break;
					}
				}
			}
			if (breakResult)
				break;
		}
		return best;
	}
}

//performing minimax
Score Ai_Player::performMinimax_alfabetaPruning(Board board, int depth,
		int player, int row, int column, int alpha, int beta, int &noOfNodes,
		int &countminus, int evaluateFunctionNo) {
	noOfNodes++;
	Score score;
	score.depth = depth - 1;

	//If player is player 2
	if (player == playerO) {
		if (evaluateFunctionNo == 1)
			score.value = board.evaluateFunction1(playerX, row, column);
		else if (evaluateFunctionNo == 2)
			score.value = board.evaluateFunction2(playerX, row, column);
		else if (evaluateFunctionNo == 3)
			score.value = board.evaluateFunction3(playerX, row, column);
		if (score.value != 10) {
			if (evaluateFunctionNo == 1)
				score.value = board.evaluateFunction1(playerO, row, column);
			else if (evaluateFunctionNo == 2)
				score.value = board.evaluateFunction2(playerO, row, column);
			else if (evaluateFunctionNo == 3)
				score.value = board.evaluateFunction3(playerO, row, column);
			if (score.value == -10) {
				countminus++;
				score.value = 10;
				return score;
			}
		}
	}
	//If player is player 1
	else if (player == playerX) {
		if (evaluateFunctionNo == 1)
			score.value = board.evaluateFunction1(playerO, row, column);
		else if (evaluateFunctionNo == 2)
			score.value = board.evaluateFunction2(playerO, row, column);
		else if (evaluateFunctionNo == 3)
			score.value = board.evaluateFunction3(playerO, row, column);
		if (score.value != -10) {
			if (evaluateFunctionNo == 1)
				score.value = board.evaluateFunction1(playerX, row, column);
			else if (evaluateFunctionNo == 2)
				score.value = board.evaluateFunction2(playerX, row, column);
			else if (evaluateFunctionNo == 3)
				score.value = board.evaluateFunction3(playerX, row, column);
			if (score.value == 10) {
				countminus++;
				score.value = -10;
				return score;
			}
		}
	}
	// If Player 1 has won the game return evaluated score
	if (score.value == 10) {
		countminus++;
		return score;
	}

	// If Player 2 has won the game return evaluated score
	if (score.value == -10) {
		countminus++;
		return score;
	}

	//
	//If it is a tie return 0
	if (board.isBoardFilled()) {
		countminus++;
		score.value = 0;
		return score;
	}

	// if deep Enough is true return 0
	if (deepEnough(depth)) {
		score.value = 0;
		countminus++;
		return score;
	}

	return moveGen_alfabetaPruning(board, depth, player, alpha, beta, noOfNodes,
			countminus, evaluateFunctionNo);
}

AI_Move Ai_Player::getBestMove(Board board, int choice, int player,
		int &noOfNodes, int &countminus, int evaluateFunctionNo) {
	AI_Move bestMove;
	int count1, count;
	srand(time(0));
	int arr1[6];
	int arr[7];

	int p, q;

	if (player == playerO) {
		//checking if player 2 is winning
		for (p = 0; p < rows; p++) {
			for (q = 0; q < columns; q++) {
				// Check if celll is empty
				if ((p == rows - 1 && board.getValue(p, q) == ' ')
						|| (board.getValue(p, q) == ' '
								&& board.getValue(p + 1, q) != ' ')) {

					int result;
					if (evaluateFunctionNo == 1)
						result = board.evaluateFunction1(playerO, p, q);
					else if (evaluateFunctionNo == 2)
						result = board.evaluateFunction2(playerO, p, q);
					else if (evaluateFunctionNo == 3)
						result = board.evaluateFunction3(playerO, p, q);

					if (result == -10) {
						bestMove.x = p;
						bestMove.y = q;
						bestMove.score = -10;
						return bestMove;
					}

				}
			}
		}
		//checking if player 1 is winning
		for (p = 0; p < rows; p++) {
			for (q = 0; q < columns; q++) {
				// Check if celll is empty
				if ((p == rows - 1 && board.getValue(p, q) == ' ')
						|| (board.getValue(p, q) == ' '
								&& board.getValue(p + 1, q) != ' ')) {

					int result;
					if (evaluateFunctionNo == 1)
						result = board.evaluateFunction1(playerX, p, q);
					else if (evaluateFunctionNo == 2)
						result = board.evaluateFunction2(playerX, p, q);
					else if (evaluateFunctionNo == 3)
						result = board.evaluateFunction3(playerX, p, q);

					if (result == 10) {
						bestMove.x = p;
						bestMove.y = q;
						bestMove.score = -10;
						return bestMove;
					}

				}
			}
		}
	}
	if (player == playerX) {
		//checking if player 1 is winning
		for (p = 0; p < rows; p++) {
			for (q = 0; q < columns; q++) {
				// Check if celll is empty
				if ((p == rows - 1 && board.getValue(p, q) == ' ')
						|| (board.getValue(p, q) == ' '
								&& board.getValue(p + 1, q) != ' ')) {

					int result;
					if (evaluateFunctionNo == 1)
						result = board.evaluateFunction1(playerX, p, q);
					else if (evaluateFunctionNo == 2)
						result = board.evaluateFunction2(playerX, p, q);
					else if (evaluateFunctionNo == 3)
						result = board.evaluateFunction3(playerX, p, q);

					if (result == 10) {
						bestMove.x = p;
						bestMove.y = q;
						bestMove.score = 10;
						return bestMove;
					}

				}
			}
		}
		//checking if player 2 is winning
		for (p = 0; p < rows; p++) {
			for (q = 0; q < columns; q++) {
				// Check if celll is empty
				if ((p == rows - 1 && board.getValue(p, q) == ' ')
						|| (board.getValue(p, q) == ' '
								&& board.getValue(p + 1, q) != ' ')) {
					int result;

					if (evaluateFunctionNo == 1)
						result = board.evaluateFunction1(playerO, p, q);
					else if (evaluateFunctionNo == 2)
						result = board.evaluateFunction2(playerO, p, q);
					else if (evaluateFunctionNo == 3)
						result = board.evaluateFunction3(playerO, p, q);

					if (result == -10) {
						bestMove.x = p;
						bestMove.y = q;
						bestMove.score = 10;
						return bestMove;
					}

				}
			}
		}
	}

	switch (player) {

	case 1:

		bestMove.score = -100;
		bestMove.x = -1;
		bestMove.y = -1;
		bestMove.depth = -1;

		count1 = 0;
		for (int l = 0; l < rows; l++) {
			arr1[l] = 0;
		}
		while (count1 != 6) {

			int i = rand() % 6;
			if (arr1[i] == 0) {
				arr1[i] = 1;
				count1++;

				count = 0;
				for (int k = 0; k < columns; k++) {

					arr[k] = 0;
				}

				while (count != 7) {
					//For putting values randomly in any row
					int j = rand() % 7;
					if (arr[j] == 0) {
						arr[j] = 1;
						count++;
						if ((i == rows - 1 && board.getValue(i, j) == ' ')
								|| (board.getValue(i, j) == ' '
										&& board.getValue(i + 1, j) != ' ')) {
							// Setting the value
							Score valOfMove;
							board.setValue(i, j, 'X');

							//calling the minimax function
							if (choice == 2)
								valOfMove = performMinimax_alfabetaPruning(
										board, 0, playerO, i, j, 100, -100,
										noOfNodes, countminus,
										evaluateFunctionNo);
							else if (choice == 1)
								valOfMove = performMinimax(board, 0, playerO, i,
										j, noOfNodes, countminus,
										evaluateFunctionNo);

							// setting the value to empty
							board.setValue(i, j, ' ');

							//getting the best move
							if (valOfMove.value > bestMove.score) {
								bestMove.x = i;
								bestMove.y = j;
								bestMove.score = valOfMove.value;
								bestMove.depth = valOfMove.depth;
							} else if (valOfMove.value == -10
									&& bestMove.score == -10) {
								if (valOfMove.depth > bestMove.depth) {
									bestMove.x = i;
									bestMove.y = j;
									bestMove.score = valOfMove.value;
									bestMove.depth = valOfMove.depth;
								}
							} else if (valOfMove.value == bestMove.score) {
								if (valOfMove.depth < bestMove.depth) {
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
		bestMove.score = 100;
		bestMove.x = -1;
		bestMove.y = -1;
		bestMove.depth = -1;

		count1 = 0;
		for (int l = 0; l < rows; l++) {

			arr1[l] = 0;
		}
		while (count1 != 6) {
			int i = rand() % 6;
			if (arr1[i] == 0) {
				arr1[i] = 1;
				count1++;

				count = 0;
				for (int k = 0; k < columns; k++) {
					arr[k] = 0;
				}

				while (count != 7) {
					//For putting values randomly in any row
					int j = rand() % 7;
					if (arr[j] == 0) {
						arr[j] = 1;
						count++;
						if ((i == rows - 1 && board.getValue(i, j) == ' ')
								|| (board.getValue(i, j) == ' '
										&& board.getValue(i + 1, j) != ' ')) {

							// Setting the value
							Score valOfMove;
							board.setValue(i, j, 'O');

							//calling the minimax function
							if (choice == 2)
								valOfMove = performMinimax_alfabetaPruning(
										board, 0, playerX, i, j, 100, -100,
										noOfNodes, countminus,
										evaluateFunctionNo);
							else if (choice == 1)
								valOfMove = performMinimax(board, 0, playerX, i,
										j, noOfNodes, countminus,
										evaluateFunctionNo);

							// setting the value to empty
							board.setValue(i, j, ' ');

							//getting the best move
							if (valOfMove.value < bestMove.score) {
								bestMove.x = i;
								bestMove.y = j;
								bestMove.score = valOfMove.value;
								bestMove.depth = valOfMove.depth;
							} else if (valOfMove.value == 10
									&& bestMove.score == 10) {
								if (valOfMove.depth > bestMove.depth) {
									bestMove.x = i;
									bestMove.y = j;
									bestMove.score = valOfMove.value;
									bestMove.depth = valOfMove.depth;
								}
							} else if (valOfMove.value == bestMove.score) {
								if (valOfMove.depth < bestMove.depth) {
									bestMove.x = i;
									bestMove.y = j;
									bestMove.score = valOfMove.value;
									bestMove.depth = valOfMove.depth;
								}
							}
						}
					}
				}
			}
		}
		return bestMove;
	}
}

