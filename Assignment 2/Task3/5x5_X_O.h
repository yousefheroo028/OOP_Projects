#ifndef INC_5X5_X_O_H
#define INC_5X5_X_O_H

#define _3X3X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class five_X_O_Board : public Board<T>
{
private:
    int counterX = 0;
    int counterO = 0;

public:
    five_X_O_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int countSequence(T symbol);
    int checkBounds(T symbol);
    int checkDiagonals(T symbol);
};

template <typename T>
class five_X_O_Player : public Player<T>
{
public:
    five_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class five_X_O_Random_Player : public RandomPlayer<T>
{
public:
    five_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// ------------------- IMPLEMENTATION -------------------

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
five_X_O_Board<T>::five_X_O_Board()
{
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
int five_X_O_Board<T>::countSequence(T symbol)
{
    return checkBounds(symbol) + checkDiagonals(symbol);
}

template <typename T>
int five_X_O_Board<T>::checkBounds(T symbol)
{
    int count = 0;
    for (int i = 0; i < this->rows; i++)
    {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] ==
            symbol && this->board[i][0] != 0)
            count++;
        if (this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][1] ==
            symbol && this->board[i][1] != 0)
            count++;
        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] ==
            symbol && this->board[0][i] != 0)
            count++;
        if (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[1][i] ==
            symbol && this->board[1][i] != 0)
            count++;
        if (this->board[2][i] == this->board[3][i] && this->board[3][i] == this->board[4][i] && this->board[2][i] ==
            symbol && this->board[2][i] != 0)
            count++;
    }
    return count;
}

template <typename T>
int five_X_O_Board<T>::checkDiagonals(T symbol)
{
    int count = 0;
    for (int i = 0; i <= this->rows - 3; i++)
    {
        for (int j = 0; j <= this->columns - 3; j++)
        {
            if (this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2]
                && this->board[i][j] == symbol && this->board[i][j] != 0)
            {
                count++;
            }
        }
    }
    for (int i = 0; i < this->rows - 3; i++)
    {
        for (int j = 2; j <= this->columns; j++)
        {
            if (this->board[i][j] == this->board[i + 1][j - 1] && this->board[i + 1][j - 1] == this->board[i + 2][j - 2]
                && this->board[i][j] == symbol && this->board[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
bool five_X_O_Board<T>::update_board(int x, int y, T mark)
{
    // Only update if move is valid
    system("cls");
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
    {
        if (x == 0 && y == 4)
        {
            return false;
        }
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        if (mark == 'X')counterX = countSequence('X');
        else if (mark == 'O')counterO = countSequence('O');
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void five_X_O_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool five_X_O_Board<T>::is_win()
{
    if (this->counterX > this->counterO && this->n_moves == 24)
    {
        return true;
    }
    return false;
}

// Return true if 25 moves are done and no winner
template <typename T>
bool five_X_O_Board<T>::is_draw()
{
    if (this->counterX == this->counterO && this->n_moves == 24)
    {
        return true;
    }
    return false;
}

template <typename T>
bool five_X_O_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
five_X_O_Player<T>::five_X_O_Player(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
void five_X_O_Player<T>::getmove(int& x, int& y)
{
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for five_X_O_Random_Player
template <typename T>
five_X_O_Random_Player<T>::five_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void five_X_O_Random_Player<T>::getmove(int& x, int& y)
{
    x = rand() % this->dimension; // Random number between 0 and 4
    y = rand() % this->dimension;
}

#endif
