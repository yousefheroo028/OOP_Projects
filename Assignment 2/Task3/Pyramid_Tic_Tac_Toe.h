#ifndef TASK_3_PYRAMID_TIC_TAC_TOE_H
#define TASK_3_PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iomanip>
#include <random>

// --------- Headers ---------

template <class T>
class Pyramid_Board : public Board<T>
{
public:
    Pyramid_Board();

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template <class T>
class Pyramid_Player : public Player<T>
{
public:
    Pyramid_Player(string n, T symbol);

    void getmove(int& x, int& y);
};

template <class T>
class Pyramid_Random_Player : public RandomPlayer<T>
{
public:
    explicit Pyramid_Random_Player(T symbol);

    void getmove(int& x, int& y);
};

// -------- Implementation --------

template <class T>
Pyramid_Board<T>::Pyramid_Board()
{
    this->rows = 3;
    this->columns = 5;
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j)
        {
            this->board[i][j] = ' ';
        }
        cout << '\n';
    }
}

template <class T>
bool Pyramid_Board<T>::update_board(int x, int y, T symbol)
{
    if (x == 0)
    {
        if (y == 2)
        {
            if (this->board[x][y] == ' ')
            {
                this->board[x][y] = symbol;
                ++this->n_moves;
                return true;
            }
        }
    }
    else if (x == 1)
    {
        if (y >= 1 && y < 4)
        {
            if (this->board[x][y] == ' ')
            {
                this->board[x][y] = symbol;
                ++this->n_moves;
                return true;
            }
        }
    }
    else if (x == 2)
    {
        if (y >= 0 && y < 5)
        {
            if (this->board[x][y] == ' ')
            {
                this->board[x][y] = symbol;
                ++this->n_moves;
                return true;
            }
        }
    }
    return false;
}

template <class T>
void Pyramid_Board<T>::display_board()
{
    system("cls");
    for (int i = 0; i < this->rows; ++i)
    {
        cout << ' ';
        for (int j = 0; j < this->columns; ++j)
        {
            if (this->board[i][j] == 'X' || this->board[i][j] == 'O') cout << "  " << this->board[i][j] << "   ";
            else if ((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || (i == 2 && j >= 0 && j <= 4))
                cout << '(' << i << ", " << j << ')';
            else cout << "      ";
            if (j < this->columns - 1) cout << " | ";
        }
        if (i < this->rows - 1) cout << "\n--------------------------------------------\n";
    }
    cout << '\n';
}

template <class T>
bool Pyramid_Board<T>::is_draw()
{
    return this->n_moves == 9 && !this->is_win();
}

template <class T>
bool Pyramid_Board<T>::is_win()
{
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ' ||
        this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != ' ' ||
        this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != ' ' ||
        this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != ' ' ||
        this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != ' ' ||
        this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != ' ' ||
        this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != ' '
    )
    {
        return true;
    }
    return false;
}

template <class T>
bool Pyramid_Board<T>::game_is_over()
{
    return this->is_win() || this->is_draw();
}

template <class T>
Pyramid_Player<T>::Pyramid_Player(std::string n, T symbol) : Player<T>(n, symbol)
{
}

template <class T>
void Pyramid_Player<T>::getmove(int& x, int& y)
{
    cout << this->name << ", enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <class T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol): RandomPlayer<T>(symbol)
{
    this->name += ' ';
    this->name += this->symbol;
}

template <class T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 5);
    x = distrib(gen);
    y = distrib(gen);
}

#endif
