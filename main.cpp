#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define EMPTY '-'
#define WINNER 1000
#define LOSER -1000
#define TIE 0
#define SIZE 3
#define PLAYER 'X'
#define COMPUTER 'O'
#define DEPTH 0

void printBoard(char board[SIZE][SIZE]);

bool isGameFinished(char board[SIZE][SIZE]);

bool isBoardFull(char board[SIZE][SIZE]);

vector<pair<int, int>> getEmptyPositions(char board[SIZE][SIZE]);

int getBoardState(char board[SIZE][SIZE], char marker);

vector<pair<int, int>> getOccupiedPositions(char board[3][3], char marker);

bool isGameWon(const vector<pair<int, int>>& occupiedPositions);

bool isOccupied(char board[3][3], pair<int, int> position);

pair<int, pair<int, int>> findBestMove(char board[3][3], char marker, int depth, int alpha, int beta);

string displayState(int state);

int main() {
    char board[SIZE][SIZE] = { EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY,
                               EMPTY, EMPTY, EMPTY };

    cout << "Welcome to Tic-Tac-Toe Game" << endl;
    cout << "The player is X" << endl;
    cout << "The computer is O" << endl;

    printBoard(board);

    while (!isGameFinished(board)) {
        int row, column;

        do {
            cout << "Enter column (0,2):" << endl;
            cin >> column;
            cout << "Enter row (0,2):" << endl;
            cin >> row;
        } while (isOccupied(board, make_pair(row, column)));

        board[row][column] = PLAYER;

        // Perform AI Move
        pair<int, pair<int, int>> pair = findBestMove(board, COMPUTER, DEPTH, LOSER, WINNER);
        board[pair.second.first][pair.second.second] = COMPUTER;
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

pair<int, pair<int, int>> findBestMove(char board[3][3], char marker, int depth, int alpha, int beta) {
    pair<int, int> bestMove = make_pair(-1, -1);
    int bestScore = marker == COMPUTER ? LOSER : WINNER;

    if (isGameFinished(board)) {
        bestScore = getBoardState(board, COMPUTER);
        return make_pair(bestScore, bestMove);
    }

    vector<pair<int, int>> emptyPositions = getEmptyPositions(board);

    for (auto position : emptyPositions) {
        board[position.first][position.second] = marker;

        if (marker == COMPUTER) {
            int score = findBestMove(board, PLAYER, depth + 1, alpha, beta).first;

            if (bestScore < score) {
                bestScore = score - depth * 10;
                bestMove = position;

                alpha = max(alpha, bestScore);
                board[position.first][position.second] = EMPTY;

                if (beta <= alpha) {
                    break;
                }
            }
        } else {
            int score = findBestMove(board, COMPUTER, depth + 1, alpha, beta).first;

            if (bestScore > score) {
                bestScore = score + depth * 10;
                bestMove = position;

                beta = min(beta, bestScore);
                board[position.first][position.second] = EMPTY;

                if (beta <= alpha) {
                    break;
                }
            }
        }
        board[position.first][position.second] = EMPTY;
    }
    return make_pair(bestScore, bestMove);
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

bool isGameWon(const vector<pair<int, int>>& occupiedPositions) {
    if (occupiedPositions.size() < 3) {
        return false;
    }

    // Check for horizontal win
    for (int i = 0; i < SIZE; i++) {
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            for (auto & occupiedPosition : occupiedPositions) {
                if (occupiedPosition.first == i && occupiedPosition.second == j) {
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
            for (auto & occupiedPosition : occupiedPositions) {
                if (occupiedPosition.first == j && occupiedPosition.second == i) {
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
        for (auto & occupiedPosition : occupiedPositions) {
            if (occupiedPosition.first == i && occupiedPosition.second == i) {
                count++;
            }
        }
    }
    if (count == SIZE) {
        return true;
    }

    count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (auto & occupiedPosition : occupiedPositions) {
            if (occupiedPosition.first == i && occupiedPosition.second == SIZE - i - 1) {
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
