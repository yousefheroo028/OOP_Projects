#ifndef NUMERICALTICTACTOEBOARD_H
#define NUMERICALTICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <algorithm>
#include <ctime>

template <typename T>
class numericalTicTacToeBoard : public Board<T> {
public:
    numericalTicTacToeBoard() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = 0;
            }
        }
    }

    ~numericalTicTacToeBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] == 0) {
                    cout << " . ";
                } else {
                    cout << " " << this->board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            // Row check
            if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15)
                return true;
            // Column check
            if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)
                return true;
        }

        // Check diagonals
        if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15)
            return true;
        if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)
            return true;

        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class humanPlayer : public Player<T> {
private:
    vector<T> availableNumbers;
    T currentNumber;

public:
    // Taking the player's name and their set of available numbers
    humanPlayer(string name, const vector<T>& numbers)
        : Player<T>(name, 0), availableNumbers(numbers), currentNumber(0) {}

    // Let the user select a number and a position to place it
    void getmove(int &x, int &y) override {
        cout << "\n" << this->getname() << "'s turn.\n";
        cout << "Available numbers: ";
        for(auto num : availableNumbers){
            cout << num << " ";
        }
        cout << endl;

        bool validNumber = false;
        while(!validNumber){
            cout << "Choose a number to place: ";
            int num;
            cin >> num;
            if(find(availableNumbers.begin(), availableNumbers.end(), num) != availableNumbers.end()){
                currentNumber = num;
                this->symbol = num; // Update the symbol to the chosen number
                availableNumbers.erase(remove(availableNumbers.begin(), availableNumbers.end(), num), availableNumbers.end()); // Remove the number from availableNumbers
                validNumber = true;
            }
            else{
                cout << "Invalid number. Please choose from the available numbers." << endl;
            }
        }

        // Choose a position
        bool validPosition = false;
        while(!validPosition){
            cout << "Enter row and column position from 0-2 seperated by space: ";
            cin >> x >> y;
            if(x >=0 && x <3 && y >=0 && y <3){
                validPosition = true;
            }
            else{
                cout << "Invalid position. Please enter row and column between 0 and 2." << endl;
            }
        }
    }

};

template <typename T>
class randomPlayer : public RandomPlayer<T> {
private:
    vector<T> availableNumbers;
    T currentNumber;

public:
    // Taking the player's name and their set of available numbers
    randomPlayer(string name, const vector<T>& numbers)
        : RandomPlayer<T>(0), availableNumbers(numbers), currentNumber(0) {
        this->name = name;
        srand(static_cast<unsigned>(::time(nullptr)));
    }

    // Randomly select a number and a position to place it
    void getmove(int& x, int& y) override {
        // Choose a random number from availableNumbers if not empty
        if(availableNumbers.empty()){
            cout << this->getname() << " has no available numbers to place." << endl;
            x = -1;
            y = -1;
            return;
        }

        int randomIndex = rand() % availableNumbers.size();
        T chosenNumber = availableNumbers[randomIndex];
        availableNumbers.erase(availableNumbers.begin() + randomIndex);

        this->symbol = chosenNumber;

        // Choose a random position on the 3x3 board
        x = rand() % 3;
        y = rand() % 3;

        cout << this->getname() << " chose number " << chosenNumber << " at (" << x << ", " << y << ")." << endl;
    }

};

#endif
