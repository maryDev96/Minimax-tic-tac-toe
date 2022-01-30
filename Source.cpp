#include <iostream>
#include <vector>
using namespace std;

void makeMove(char* positions, int position, char symbol) {
    positions[position] = symbol;
}

int testAiMove(char positions[]) {
    for (int i = 0; i < 9; i++)
        if (positions[i] == '-') {
            return i;
        }
    return 0;
}

int playerMove(char positions[]) {
    while (true) {
        cout << "Select[";
        for (int i = 0; i < 9; i++)
            if (positions[i] == '-') {
                cout << i + 1;
                if (i < 8)
                    cout << ',';
            }

        cout << "]: ";

        int playerPosition;
        cin >> playerPosition;
        if (positions[playerPosition - 1] == '-') {
            return playerPosition - 1;
        }
        else {
            cout << "The position " << playerPosition << " is occupied. Choose another one" << endl;
        }
    }
}

void printBoard(char positions[]) {
    for (int i = 0; i < 9; i++) {
        cout << positions[i] << ' ';
        if (i % 3 == 2) {
            cout << endl;
        }
    }
    cout << endl;
}



bool checkVictory(char* positions, char c, bool write) {

    char winningChar;

    if (c == 'x')
        winningChar = 'X';
    else
        winningChar = 'O';


    if (positions[0] == c && positions[1] == c && positions[2] == c) {
        if (write) {
            positions[0] = winningChar;
            positions[1] = winningChar;
            positions[2] = winningChar;
        }

        return true;
    }
    else if (positions[3] == c && positions[4] == c && positions[5] == c) {
        if (write) {
            positions[3] = winningChar;
            positions[4] = winningChar;
            positions[5] = winningChar;
        }

        return true;
    }
    else if (positions[6] == c && positions[7] == c && positions[8] == c) {
        if (write) {
            positions[6] = winningChar;
            positions[7] = winningChar;
            positions[8] = winningChar;
        }

        return true;
    }
    else if (positions[0] == c && positions[3] == c && positions[6] == c) {
        if (write) {
            positions[0] = winningChar;
            positions[3] = winningChar;
            positions[6] = winningChar;
        }

        return true;
    }
    else if (positions[1] == c && positions[4] == c && positions[7] == c) {
        if (write) {
            positions[1] = winningChar;
            positions[4] = winningChar;
            positions[7] = winningChar;
        }

        return true;
    }
    else if (positions[2] == c && positions[5] == c && positions[8] == c) {
        if (write) {
            positions[2] = winningChar;
            positions[5] = winningChar;
            positions[8] = winningChar;
        }

        return true;
    }

    else if (positions[0] == c && positions[4] == c && positions[8] == c) {
        if (write) {
            positions[0] = winningChar;
            positions[4] = winningChar;
            positions[8] = winningChar;
        }

        return true;
    }

    else if (positions[2] == c && positions[4] == c && positions[6] == c) {
        if (write) {
            positions[2] = winningChar;
            positions[4] = winningChar;
            positions[6] = winningChar;
        }

        return true;
    }

    return false;

}

int minimax(char board[], char ch, bool isMaximizing, int depth, int maximumDepth) {

    char oppChar;
    if (ch == 'x') {
        oppChar = 'o';
    }
    else {
        oppChar = 'x';
    }

    if (checkVictory(board, ch, false)) {
        return 100 - depth;
    }
    else if (checkVictory(board, oppChar, false)) {
        return -100 - depth;
    }

    int emptySpots = 0;
    for (int i = 0; i < 9; i++) {
        if ((board)[i] == '-')
            emptySpots++;
    }

    if (emptySpots == 0) {
        return 0;
    }


    if (depth > maximumDepth) {
        return 0;
    }

    int bestResult;

    if (isMaximizing) {
        bestResult = -100000;
        int score = 0;

        for (int i = 0; i < 9; i++) {
            if (board[i] == '-') {
                makeMove(board, i, ch);
                score = minimax(board, ch, !isMaximizing, depth + 1, maximumDepth);
                makeMove(board, i, '-');

                if (score > bestResult) {
                    bestResult = score;
                }
            }
        }
    }
    else {
        bestResult = 100000;
        int score = 0;

        for (int i = 0; i < 9; i++) {
            if (board[i] == '-') {
                makeMove(board, i, oppChar);
                score = minimax(board, ch, !isMaximizing, depth + 1, maximumDepth);
                makeMove(board, i, '-');

                if (score < bestResult) {
                    bestResult = score;
                }
            }
        }
    }

    return bestResult;

}


int minimaxMove(char board[], char ch) {
    int bestResult = -9999;
    int bestMove = 10;
    char oppChar;

    if (ch == 'x') {
        oppChar = 'o';
    }
    else {
        oppChar = 'x';
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') {
            makeMove(board, i, ch);
            int score = minimax(board, ch, false, 1, 100);
            makeMove(board, i, '-');

            if (score > bestResult) {
                bestResult = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int game(bool player) {
    char playerChar = 'x';
    char aiChar = 'o';
    bool isPlayerTurn = true;

    cout << "A human will play with " << playerChar << endl;
    cout << "AI will play as " << aiChar << endl;


    char gameBoard[] = { '-','-','-','-','-','-','-','-','-' };
    int emptySpots = 9;



    while (emptySpots > 0) {
        printBoard(gameBoard);

        int move;
        char ch;

        if (isPlayerTurn) {
            if (player)
                move = playerMove(gameBoard);
            else
                move = minimaxMove(gameBoard, playerChar);

            ch = playerChar;
        }
        else {
            move = minimaxMove(gameBoard, aiChar);
            ch = aiChar;

        }
        makeMove(gameBoard, move, ch);
        emptySpots--;
        isPlayerTurn = !isPlayerTurn;

        if (checkVictory(gameBoard, playerChar, true)) {
           printBoard(gameBoard);
           cout << "Human won!" << endl;

           return 1;
        }
        else if (checkVictory(gameBoard, aiChar, true)) {
            printBoard(gameBoard);
            cout << "AI won!" << endl;

            return 2;
        }

    }
    printBoard(gameBoard);
    cout << "Tie!";
    return 0;
}

int main() {

    game(true);
    return 0;
}
