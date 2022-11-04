#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define EMPTY '-'
#define WINNER 1
#define LOSER (-1)
#define TIE 0
#define SIZE 3
#define PLAYER 'X'
#define COMPUTER 'O'

void printBoard(char board[SIZE][SIZE]);

bool isGameFinished(char board[SIZE][SIZE]);

bool isBoardFull(char board[SIZE][SIZE]);

vector<pair<int, int>> getEmptyPositions(char board[SIZE][SIZE]);

int getBoardState(char board[SIZE][SIZE], char marker);

vector<pair<int, int>> getOccupiedPositions(char board[3][3], char marker);

bool isGameWon(vector<pair<int, int>> occupiedPositions);

bool isOccupied(char board[3][3], pair<int, int> position);

pair<int, int> getAIMove(char board[3][3]);

string displayState(int state);

int main() {
    char board[SIZE][SIZE] = { EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY };

    printBoard(board);

    while (!isGameFinished(board)) {
        int row, column;
        cout << "Enter column (0,2):" << endl;
        cin >> column;
        cout << "Enter row (0,2):" << endl;
        cin >> row;

        pair<int, int> pair = make_pair(row, column);

        if (isOccupied(board, pair)) {
            cout << "That position is already occupied" << endl;
        } else {
            board[row][column] = PLAYER;
        }

        // Perform AI Move
        pair = getAIMove(board);
        board[pair.first][pair.second] = COMPUTER;
        printBoard(board);
    }

    // Implement the rest of the game logic here (check for winner, etc.)

    cout << "The game is finished" << endl;

    int state = getBoardState(board, PLAYER);

    cout << "The player has " << displayState(state) << endl;

    return 0;
}

string displayState(int state) {
    if (state == WINNER) {
        return "won";
    } else if (state == LOSER) {
        return "lost";
    } else {
        return "tied";
    }
}

pair<int, int> getAIMove(char board[3][3]) {
    // implement minmax algorithm here
}

bool isOccupied(char board[3][3], pair<int, int> position) {
    return board[position.first][position.second] != EMPTY;
}

bool isGameFinished(char board[SIZE][SIZE]) {
    if (isBoardFull(board) || getBoardState(board, COMPUTER) != TIE) {
        return true;
    }
    return false;
}

int getBoardState(char board[SIZE][SIZE], char marker) {
    char opponent = marker == PLAYER ? COMPUTER : PLAYER;

    vector<pair<int, int>> occupiedPositions = getOccupiedPositions(board, marker);
    bool hasWon = isGameWon(occupiedPositions);

    if (hasWon) {
        return WINNER;
    }

    occupiedPositions = getOccupiedPositions(board, opponent);
    bool hasLost = isGameWon(occupiedPositions);

    if (hasLost) {
        return LOSER;
    }

    return TIE;
}

bool isGameWon(vector<pair<int, int>> occupiedPositions) {
    if (occupiedPositions.size() < 3) {
        return false;
    }

    // Check for horizontal win
    for (int i = 0; i < SIZE; i++) {
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < occupiedPositions.size(); k++) {
                if (occupiedPositions[k].first == i && occupiedPositions[k].second == j) {
                    count++;
                }
            }
        }
        if (count == SIZE) {
            return true;
        }
    }

    // Check for vertical win
    for (int i = 0; i < SIZE; i++) {
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < occupiedPositions.size(); k++) {
                if (occupiedPositions[k].first == j && occupiedPositions[k].second == i) {
                    count++;
                }
            }
        }
        if (count == SIZE) {
            return true;
        }
    }

    // Check for diagonal win
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < occupiedPositions.size(); j++) {
            if (occupiedPositions[j].first == i && occupiedPositions[j].second == i) {
                count++;
            }
        }
    }
    if (count == SIZE) {
        return true;
    }

    count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < occupiedPositions.size(); j++) {
            if (occupiedPositions[j].first == i && occupiedPositions[j].second == SIZE - i - 1) {
                count++;
            }
        }
    }
    if (count == SIZE) {
        return true;
    }

    return false;
}

vector<pair<int, int>> getOccupiedPositions(char board[3][3], char marker) {
    vector<pair<int, int>> occupiedPositions;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == marker) {
                occupiedPositions.emplace_back(i, j);
            }
        }
    }
    return occupiedPositions;
}

bool isBoardFull(char board[SIZE][SIZE]) {
    vector<pair<int, int>> emptyPositions = getEmptyPositions(board);

    if (emptyPositions.empty()) {
        return true;
    }
    return false;
}

vector<pair<int, int>> getEmptyPositions(char board[SIZE][SIZE]) {
    vector<pair<int, int>> emptyPositions;
    for(int i=0 ; i<SIZE ; i++) {
        for (int j=0 ; j<SIZE ; j++) {
            if (board[i][j] == EMPTY) {
                emptyPositions.emplace_back(i, j);
            }
        }
    }
    return emptyPositions;
}

void printBoard(char board[SIZE][SIZE]) {
    for (int i=0 ; i<SIZE ; i++) {
        cout << "|";
        for (int j=0 ; j<SIZE ; j++) {
            cout << board[i][j] << "|";
        }
        cout << endl;
        cout << "-------" << endl;
    }
}
