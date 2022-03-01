#include <iostream>
#include <cstdlib>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

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

bool isWon(char, char[][3]) {
	return true;
}

bool isDraw(char[][3]) {
	return true;
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

void makeAMove(char[][3], char) {
	
}