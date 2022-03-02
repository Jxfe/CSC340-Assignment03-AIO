#include <iostream>
#include <cstdlib>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int const maxMoves = 9;
int totalMoves = 0;

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
} 

bool isWon(char token, char board[][3]) { //Checks every row, col, and diagnal for winning patterns
	if(board[0][0] == token && board[0][1] == token && board[0][2]) {
		return true;
	}
	if(board[1][0] == token && board[1][1] == token && board[1][2]) {
		return true;
	}
	if(board[2][0] == token && board[2][1] == token && board[2][2]) {
		return true;
	}
	if(board[0][0] == token && board[1][0] == token && board[2][0]) {
		return true;
	}
	if(board[0][1] == token && board[1][1] == token && board[2][1]) {
		return true;
	}
	if(board[0][2] == token && board[1][2] == token && board[2][2]) {
		return true;
	}
	if(board[0][0] == token && board[1][1] == token && board[2][2]) {
		return true;
	}
	if(board[2][0] == token && board[1][1] == token && board[0][2]) {
		return true;
	}
	return false;
}

bool isDraw(char board[][3]) {
	if(totalMoves == maxMoves) {
		return true;
	}
	return false;
}

void displayBoard(char board[][3]) {
	cout << endl;
	for(int row = 0; row < 3; row++) {
		cout << "-------------" << endl;
		for(int col = 0; col < 3; col++) {
			cout << "| " << board[row][col] << " ";
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;
}

void makeAMove(char board[][3], char token) {
	totalMoves++;
	int row = 0;
	int col = 0;
	bool tokenPlaced = false;

	while(tokenPlaced == false) {
		cout << "Enter a row (0, 1, 2) for player " << token << " : ";
		cin >> row;
		cout << "Enter a column (0, 1, 2) for player " << token << " : ";
		cin >> col;

		if(board[row][col] == ' ') {
			board[row][col] == token;
			tokenPlaced = true;
		}
		else {
			cout << "This cell is already occupied. Try a different cell" << endl;
		}
	}
}