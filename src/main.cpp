/*
 * Parker Brown
 * 08/17/2018
 * Programming Fundamentals 2
 * Tic Tac Toe
 */

#include <iostream>
#include <algorithm>

enum gamePiece {X_PIECE, O_PIECE, EMPTY_PIECE};
enum gameState {X_WINS, O_WINS, NOT_OVER, TIE};
char gamePieceChar[3] = {'X', 'O', ' '};

const int NUM_SLOTS = 9;
const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const int WINNING_MOVES[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
};

void displayRules();
void displayBoard(gamePiece gamePieces[]);
int getHumanMove(gamePiece player, gamePiece gamePieces[]);
int getComputerMove(gamePiece turn, gamePiece human, gamePiece gamePieces[]);
bool validMove(int slot, gamePiece gamePieces[]);
bool checkTie(gamePiece gamePieces[]);
bool willWin(int slot, gamePiece player, gamePiece gamePieces[]);

bool gameOver = false;

int main() {
    std::cout << "Welcome to the game of Tic-Tac-Toe!" << std::endl;

    displayRules();

    gamePiece gamePieces[NUM_SLOTS];
    std::fill_n(gamePieces, NUM_SLOTS, EMPTY_PIECE);

    gameState state = NOT_OVER;
    gamePiece turn = X_PIECE;
    gamePiece human;
    gamePiece computer;

    char goFirst;
    std::cout << "\nWould you like to go first [Y/N]? ";
    std::cin >> goFirst;

    while (tolower(goFirst) != 'y' && tolower(goFirst) != 'n') {
        std::cout << "\nPlease enter a valid character: ";
        std::cin.clear();
        std::cin.ignore(80, '\n');
        std::cin >> goFirst;
    }

    if (tolower(goFirst) == 'n') {
        human = O_PIECE;
        computer = X_PIECE;
        std::cout << "\nThe computer will go first! It is letter " << gamePieceChar[static_cast<int>(computer)] << std::endl;
        std::cout << "\nYou are letter " << gamePieceChar[static_cast<int>(human)] << std::endl << std::endl;
        turn = computer;
        int move = getComputerMove(turn, human, gamePieces);
        gamePieces[move] = turn;
        displayBoard(gamePieces);
    } else {
        human = X_PIECE;
        computer = O_PIECE;
    }

    do {
        turn = human;

        int move = getHumanMove(human, gamePieces);
        gamePieces[move] = turn;

        displayBoard(gamePieces);

        if (checkTie(gamePieces)) {
            state = TIE;
            break;
        }

        if (gameOver) {
            state = static_cast<gameState>(human);
            break;
        }

        turn = computer;

        move = getComputerMove(turn, human, gamePieces);
        gamePieces[move] = turn;

        displayBoard(gamePieces);

        if (checkTie(gamePieces)) {
            state = TIE;
            break;
        }

        if (gameOver) {
            state = static_cast<gameState>(computer);
            break;
        }
    } while(!gameOver);

    if (state == TIE) {
        std::cout << "Game over! Looks like we have a tie!" << std::endl;
    } else {
        std::cout << "Game over! " << gamePieceChar[static_cast<int>(state)] << " wins the game!" << std::endl;
    }

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

bool checkTie(gamePiece gamePieces[]) {
    bool isFull = true;
    for (int i = 0; i < NUM_SLOTS; i++) {
        if (gamePieces[i] == EMPTY_PIECE) {
            isFull = false;
            break;
        }
    }

    return isFull;
}

bool willWin(int slot, gamePiece player, gamePiece gamePieces[]) {
    // Dynamically allocate an array so we can copy gamePieces
    gamePiece *copy = new gamePiece[NUM_SLOTS];

    // Fill the array with copied values
    for (int n = 0; n < NUM_SLOTS; n++) {
        copy[n] = gamePieces[n];
    }

    // Assign the theoretical move to the copied array
    copy[slot] = player;

    for (int i = 0; i < 8; i++) {
        bool winner = true;
        for (int j = 0; j < 3; j++) {
            if (copy[WINNING_MOVES[i][j]] != player) {
                winner = false;
                break;
            }
        }

        if (winner) {
            delete[] copy;
            return true;
        }
    }

    // Deallocate the copied array
    delete[] copy;

    return false;
}

void displayBoard(gamePiece gamePieces[]) {
    std::cout << gamePieceChar[gamePieces[0]] << "|" << gamePieceChar[gamePieces[1]] << "|" << gamePieceChar[gamePieces[2]] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << gamePieceChar[gamePieces[3]] << "|" << gamePieceChar[gamePieces[4]] << "|" << gamePieceChar[gamePieces[5]] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << gamePieceChar[gamePieces[6]] << "|" << gamePieceChar[gamePieces[7]] << "|" << gamePieceChar[gamePieces[8]] << std::endl;
    std::cout << std::endl;
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

int getHumanMove(gamePiece player, gamePiece gamePieces[]) {
    std::cout << "It's your turn!" << std::endl;

    int move;

    std::cout << "\nSelect a number to represent your move [0-8]: ";
    std::cin >> move;

    while (!validMove(move, gamePieces)) {
        std::cin.clear();
        std::cin.ignore(80, '\n');
        std::cout << "\nPlease try again [0-8]: ";
        std::cin >> move;
    }

    if (willWin(move, player, gamePieces)) {
        gameOver = true;
    }

    return move;
}

bool validMove(int slot, gamePiece gamePieces[]) {
    if (std::cin.fail())
        return false;

    if (slot < 0 || slot > 8)
        return false;

    if (gamePieces[slot] != EMPTY_PIECE)
        return false;

    return true;
}

int getComputerMove(gamePiece turn, gamePiece human, gamePiece gamePieces[]) {
    std::cout << "It's the computer's turn!" << std::endl << std::endl;

    for (int i = 0; i < NUM_SLOTS; i++) {
        if (gamePieces[i] == EMPTY_PIECE) {
            if (willWin(i, turn, gamePieces)) {
                gameOver = true;
                return i;
            }
        }
    }

    for (int j = 0; j < NUM_SLOTS; j++) {
        if (gamePieces[j] == EMPTY_PIECE) {
            if (willWin(j, human, gamePieces)) {
                return j;
            }
        }
    }

    for (int k = 0; k < NUM_SLOTS; k++) {
        if (gamePieces[BEST_MOVES[k]] == EMPTY_PIECE) {
            return BEST_MOVES[k];
        }
    }
}