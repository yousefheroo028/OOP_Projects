#ifndef NUMERICALTICTACTOEBOARD_H
#define NUMERICALTICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <algorithm>
#include <random>

inline bool turn_flipper = true;
inline vector<int> available_odd_numbers;
inline vector<int> available_even_numbers;
inline vector<int>* available_numbers;

template <typename T>
class numericalTicTacToeBoard : public Board<T>
{
public:
    numericalTicTacToeBoard()
    {
        turn_flipper = true;
        available_odd_numbers = {1, 3, 5, 7, 9};
        available_even_numbers = {2, 4, 6, 8};
        available_numbers = nullptr;
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i)
        {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j)
            {
                this->board[i][j] = 0;
            }
        }
    }

    bool update_board(int x, int y, T symbol) override
    {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0)
        {
            available_numbers = !turn_flipper ? &available_even_numbers : &available_odd_numbers;
            this->board[x][y] = symbol;
            available_numbers->erase(ranges::find(*available_numbers, symbol - '0'));
            ++this->n_moves;
            turn_flipper = !turn_flipper;
            return true;
        }
        return false;
    }

    void display_board() override
    {
        // system("cls");
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->columns; ++j)
            {
                if (this->board[i][j] == 0)
                {
                    cout << " . ";
                }
                else
                {
                    cout << " " << this->board[i][j] << " ";
                }
            }
            cout << '\n';
        }
    }

    bool is_win() override
    {
        // Check rows and columns
        for (int i = 0; i < 3; i++)
        {
            // Row check
            if (-3 * '0' + this->board[i][0] + this->board[i][1] + this->board[i][2] == 15)
                return true;
            // Column check
            if (-3 * '0' + this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)
                return true;
        }

        // Check diagonals
        if (-3 * '0' + this->board[0][0] + this->board[1][1] + this->board[2][2] == 15)
            return true;
        if (-3 * '0' + this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)
            return true;

        return false;
    }

    bool is_draw() override
    {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};

template <typename T>
class humanPlayer : public Player<T>
{
public:
    // Taking the player's name and their set of available numbers
    humanPlayer(string name, T symbol) : Player<T>(name, symbol)
    {
    }

    // Let the user select a number and a position to place it
    void getmove(int& x, int& y) override
    {
        available_numbers = turn_flipper ? &available_odd_numbers : &available_even_numbers;
        bool validNumber = false;
        while (!validNumber)
        {
            cout << "\nAvailable numbers: ";
            for (const auto n : *available_numbers)
            {
                if (n) cout << n << " ";
            }
            cout << '\n';
            cout << "Choose an existing number: ";
            int num;
            cin >> num;
            if (ranges::find(*available_numbers, num) != available_numbers->end())
            {
                // Remove the number from available_numbers
                this->symbol = num + '0';
                validNumber = true;
            }
            else
            {
                cout << "Invalid number. Please choose from the available numbers.\n";
            }
            validNumber = validNumber && available_numbers->size();
        }
        cout << this->name << ", enter the coordinates of the cell [0, 2]: ";
        cin >> x >> y;
    }
};

template <typename T>
class randomPlayer : public RandomPlayer<T>
{
public:
    // Taking the player's name and their set of available numbers
    randomPlayer(T symbol): RandomPlayer<T>(symbol)
    {
    }

    // Randomly select a number and a position to place it
    void getmove(int& x, int& y) override
    {
        available_numbers = turn_flipper ? &available_odd_numbers : &available_even_numbers;

        // Choose a random position on the 3x3 board
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> coordinates(0, 2);
        x = coordinates(gen);
        y = coordinates(gen);
        if (available_numbers->size())
        {
            uniform_int_distribution<> index(0, available_numbers->size() - 1);
            int i = index(gen);
            if (ranges::find(*available_numbers, available_numbers->at(i)) != available_numbers->end())
                this->symbol = available_numbers->at(i) + '0';
        }
    }
};

#endif
