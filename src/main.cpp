#include <iostream>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <vector>

enum gamePiece {X_PIECE, O_PIECE, EMPTY_PIECE};
enum gameState {X_WINS, O_WINS, NOT_OVER, TIE};
char gamePieceChar[3] = {'X', 'O', ' '};

const int NUM_SLOTS = 9;

void displayRules();
void displayBoard(gamePiece gamePieces[]);
int getHumanMove(gamePiece gamePieces[]);
int getComputerMove(gamePiece gamePieces[]);

int main() {
    std::cout << "Welcome to the game of Tic-Tac-Toe!" << std::endl;

    displayRules();

    gamePiece gamePieces[NUM_SLOTS];
    std::fill_n(gamePieces, NUM_SLOTS, EMPTY_PIECE);

    int piece = getHumanMove(gamePieces);
    gamePieces[piece] = X_PIECE;

    piece = getComputerMove(gamePieces);
    gamePieces[piece] = O_PIECE;

    displayBoard(gamePieces);



#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

void displayBoard(gamePiece gamePieces[]) {

}

void displayRules() {
    std::cout << "\nAs per the board below, you will enter a number corresponding with the place you would like to fill." << std::endl;
    std::cout << std::endl;
    std::cout << "0|1|2" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "3|4|5" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "6|7|8" << std::endl;
}

int getHumanMove(gamePiece gamePieces[]) {
    int move;

    do {
        std::cout << "\nSelect a number to represent your move [0-8]: ";
        std::cin >> move;
    } while (move < 0 || move > 8);

    return move;
}

int getComputerMove(gamePiece gamePieces[]) {

    // Weird implementation, but it works...
    // Always tries to choose a corner, but if it can't,
    // it will choose a random square

    if ((gamePieces[0] == X_PIECE ||
         gamePieces[2] == X_PIECE ||
         gamePieces[6] == X_PIECE ||
         gamePieces[8] == X_PIECE) && gamePieces[4] == EMPTY_PIECE) {
        std::cout << "returning " << 4 << std::endl;
        return 4;
    }

    srand(time(0));
    std::vector<int> piecesLeft;
    for (int i = 0; i < NUM_SLOTS; i++) {
        if (gamePieces[i] == EMPTY_PIECE) {
            piecesLeft.push_back(i);
        }
    }

    for (int j = 0; j < piecesLeft.size(); j++) {
        if (piecesLeft[j] % 2 == 0 && piecesLeft[j] != 4) {
            std::cout << "returning " << piecesLeft[j] << std::endl;
            return piecesLeft[j];
        }
    }

    int random = rand() % piecesLeft.size();
    return piecesLeft[random];
}

void printSlots(gamePiece gamePieces) {
    for (int i = 0; i < NUM_SLOTS; i++) {

    }
}