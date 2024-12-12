#ifndef _CONNECT4_BOARD_H
#define _CONNECT4_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>

template<typename T>
class connect4_Board : public Board<T> {
private:
    vector<vector<T>> grid;

public:
    connect4_Board() {
        this->rows = 6;
        this->columns = 7;
        grid = vector<vector<T>>(this->rows, vector<T>(this->columns, '-')); // rows and columns filled with '-'
    }

    // placing the symbol in the lowest available row of the given column
    bool update_board(int x, int y, T symbol) override {
        // Check if column is valid (0-6)
        if (y < 0 || y >= this->columns) return false;

        // Find the lowest empty space in the column
        for (int row = this->rows - 1; row >= 0; --row) {
            if (grid[row][y] == '-') { // Empty space found
                grid[row][y] = symbol;
                return true;
            }
        }

        // full?
        return false;
    }

    void display_board() override {
        system("cls");
        for (int row = 0; row < this->rows; ++row) {
            for (int col = 0; col < this->columns; ++col) {
                std::cout << grid[row][col] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool is_win() override {
        // Check for horizontal, vertical, and diagonal wins
        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->columns; ++c) {
                if (grid[r][c] == '-') continue;

                // Check horizontal
                if (c + 3 < this->columns &&
                    grid[r][c] == grid[r][c + 1] &&
                    grid[r][c] == grid[r][c + 2] &&
                    grid[r][c] == grid[r][c + 3]) {
                    return true;
                }

                // Check vertical
                if (r + 3 < this->rows &&
                    grid[r][c] == grid[r + 1][c] &&
                    grid[r][c] == grid[r + 2][c] &&
                    grid[r][c] == grid[r + 3][c]) {
                    return true;
                }

                // Check diagonal (down-right)
                if (r + 3 < this->rows && c + 3 < this->columns &&
                    grid[r][c] == grid[r + 1][c + 1] &&
                    grid[r][c] == grid[r + 2][c + 2] &&
                    grid[r][c] == grid[r + 3][c + 3]) {
                    return true;
                }

                // Check diagonal (down-left)
                if (r + 3 < this->rows && c - 3 >= 0 &&
                    grid[r][c] == grid[r + 1][c - 1] &&
                    grid[r][c] == grid[r + 2][c - 2] &&
                    grid[r][c] == grid[r + 3][c - 3]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw() override {
        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->columns; ++c) {
                if (grid[r][c] == '-') {
                    return false; // There's at least one empty space
                }
            }
        }
        return true; // No empty spaces, it's a draw
    }

    // either a win or a draw
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template<typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        cout << this->getname() << " turn, enter your move (column number 0-6): ";
        cin >> y;
        // Ensure the move is within the valid range
        while (y < 0 || y >= 7) {
            cout << "Invalid column. Please enter a column number between 0 and 6: ";
            cin >> y;
        }
        x = -1; // There is no need for the row in this case
    }
};

template<typename T>
class ComputerPlayer : public RandomPlayer<T> {
public:
    // Constructor that initializes the symbol of the player
    ComputerPlayer(T symbol) : RandomPlayer<T>(symbol) {
        // Seed the random number generator
        srand(time(0));
    }

    void getmove(int &x, int &y) override {
        cout << "Now it's " << this->getname() << " turn" << endl;
        // Randomly select a column (0 to 6 for Connect Four)
        y = rand() % 7;  // Random column between 0 and 6

        // Find the lowest available row in the chosen column
        x = -1;  // The row will be autuomatically calculated
    }
};

#endif
