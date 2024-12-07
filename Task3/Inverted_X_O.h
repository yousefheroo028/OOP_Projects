#ifndef TASK_3_INVERTED_X_O_H
#define TASK_3_INVERTED_X_O_H

#include "BoardGame_Classes.h"

template<typename T>
class Inverted_X_O_Board : public Board<T> {
public:
    Inverted_X_O_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();

};

template<typename T>
class Inverted_X_O_Player : public Player<T> {
public:
    Inverted_X_O_Player(string name, T symbol);

    void getmove(int &x, int &y);

};

template<typename T>
class Inverted_X_O_Random_Player : public RandomPlayer<T> {
public:
    Inverted_X_O_Random_Player(T symbol);

    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template<typename T>
Inverted_X_O_Board<T>::Inverted_X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Inverted_X_O_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template<typename T>
void Inverted_X_O_Board<T>::display_board() {
    system("cls");
    for (int i = 0; i < this->rows; ++i) {
        cout << ' ';
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] != 0) cout << "  " << this->board[i][j] << "   ";
            else cout << '(' << i << ", " << j << ')';
            if (j < this->columns - 1) cout << " | ";
        }
        if (i < this->rows - 1) cout << "\n--------------------------\n";
    }
    cout << '\n';
}

template<typename T>
bool Inverted_X_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
             this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
             this->board[0][i] != 0)) {
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool Inverted_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Inverted_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
Inverted_X_O_Player<T>::Inverted_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Inverted_X_O_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template<typename T>
Inverted_X_O_Random_Player<T>::Inverted_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += (symbol == 'X' ? 'O' : 'X');
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void Inverted_X_O_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif
