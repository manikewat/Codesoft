#include <iostream>
using namespace std;

// Function prototypes
void initializeBoard(char board[3][3]);
void displayBoard(const char board[3][3]);
bool placeMark(char board[3][3], int row, int col, char mark);
bool checkWin(const char board[3][3], char mark);
bool checkDraw(const char board[3][3]);
bool isMoveValid(int row, int col);
void playGame();

int main() {
    char playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}

// Function to initialize the game board
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the game board
void displayBoard(const char board[3][3]) {
    cout << "  0 1 2\n";
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  -----\n";
    }
}

// Function to place a mark on the board
bool placeMark(char board[3][3], int row, int col, char mark) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = mark;
        return true;
    }
    return false;
}

// Function to check if a player has won
bool checkWin(const char board[3][3], char mark) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)) {
        return true;
    }
    return false;
}

// Function to check if the game is a draw
bool checkDraw(const char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Function to check if a move is valid
bool isMoveValid(int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3;
}

// Main game function
void playGame() {
    char board[3][3];
    initializeBoard(board);
    char currentPlayer = 'X';
    bool gameWon = false;

    while (!checkDraw(board) && !gameWon) {
        int row, col;
        displayBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        if (isMoveValid(row, col) && placeMark(board, row, col, currentPlayer)) {
            gameWon = checkWin(board, currentPlayer);
            if (gameWon) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "The game is a draw!" << endl;
            }
            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}
