#ifndef TASK_3_WORD_TIC_TAC_TOE_H
#define TASK_3_WORD_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <fstream>
#include <random>

// ---------- Headers ----------

template<class T>
class Word_Board : public Board<T> {
public:
    Word_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template<class T>
class Word_Player : public Player<T> {
public:
    Word_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template<class T>
class Word_Random_Player : public RandomPlayer<T> {
public:
    Word_Random_Player(T symbol);

    void getmove(int &x, int &y);
};

// ---------- Implementation ----------

template<class T>
Word_Board<T>::Word_Board() {
    this->rows = this->columns = 3;
    this->n_moves = 0;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = ' ';
        }
    }
}

template<class T>
void Word_Board<T>::display_board() {
    system("cls");
    for (int i = 0; i < this->rows; ++i) {
        cout << ' ';
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] != ' ') cout << "  " << this->board[i][j] << "   ";
            else cout << '(' << i << ", " << j << ')';
            if (j < this->columns - 1) cout << " | ";
        }
        if (i < this->rows - 1) cout << "\n--------------------------\n";
    }
    cout << '\n';
}

template<class T>
bool Word_Board<T>::game_is_over() {
    return this->is_win() || this->is_draw();
}

template<class T>
bool Word_Board<T>::is_draw() {
    return this->n_moves == 9 && !this->is_win();
}

template<class T>
bool Word_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == ' ') {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    } else return false;
}

template<class T>
bool Word_Board<T>::is_win() {
    ifstream dic("dic.txt");
    string temp, sol;
    if (dic.is_open()) {
        while (getline(dic, temp, '\n')) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    sol += this->board[i][j];
                }
                if (temp == sol) return true;
                sol.clear();
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    sol += this->board[j][i];
                }
                if (temp == sol) return true;
                sol.clear();
            }
            sol += this->board[0][0];
            sol += this->board[1][1];
            sol += this->board[2][2];
            if (temp == sol) return true;
            sol.clear();
            sol += this->board[0][2];
            sol += this->board[1][1];
            sol += this->board[2][0];
            if (temp == sol) return true;
        }
    }
    return false;
}

template<class T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<class T>
void Word_Player<T>::getmove(int &x, int &y) {
    cout << this->name << ", enter an alphabetical character: ";
    cin >> this->symbol;
    this->symbol = toupper(this->symbol);
    cout << this->name << ", enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template<class T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template<class T>
void Word_Random_Player<T>::getmove(int &x, int &y) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 3);
    x = distrib(gen);
    y = distrib(gen);
    uniform_int_distribution<> distrib2('A', 'Z');
    this->symbol = distrib2(gen);
}

#endif