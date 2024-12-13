#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

template <class T>
class ultimate_tic_tac_toe_board : public Board<T>
{
protected:
    vector<vector<T>> final_board;

public:
    ultimate_tic_tac_toe_board();

    bool update_board(int x, int y, T symbol) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;
};

template <class T>
class ultimate_tic_tac_toe_player : public Player<T>
{
public:
    ultimate_tic_tac_toe_player(string n, T symbol);

    void getmove(int& x, int& y) override;
};

template <class T>
class ultimate_tic_tac_toe_random_player : public RandomPlayer<T>
{
public:
    ultimate_tic_tac_toe_random_player(T symbol);

    void getmove(int& x, int& y) override;
};

template <class T>
ultimate_tic_tac_toe_board<T>::ultimate_tic_tac_toe_board()
{
    final_board = vector<vector<T>>(3, vector<T>(3, ' '));
    this->columns = this->rows = 9;
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }
}

template <class T>
void ultimate_tic_tac_toe_board<T>::display_board()
{
    system("cls");
    for (int i = 0; i < this->rows; ++i)
    {
        if (!(i % 3))
            cout << "\n";
        cout << ' ';
        for (int j = 0; j < this->columns; ++j)
        {
            if (!(j % 3))
                cout << ' ';
            if (this->board[i][j] != ' ')
                cout << "  " << this->board[i][j] << "   ";
            else
                cout << '(' << i << ", " << j << ')';
            if (j < this->columns - 1)
            {
                if ((j + 1) % 3)
                    cout << " | ";
                else
                    cout << "      ";
            }
        }
        if (i < this->rows - 1)
        {
            if ((i + 1) % 3)
                cout << "\n----------------------------   ---------------------------- "
                    "  ----------------------------\n";
            else
                cout << "\n\n";
        }
    }
    cout << '\n';
    cout << "\nThe result...\n";
    for (int j = 0; j < 3; j++)
    {
        cout << ' ' << this->final_board[j][0];
        for (int i = 1; i < 3; ++i) cout << " | " << this->final_board[j][i];
        if (j < 2) cout << "\n-----------\n";
    }
    cout << '\n';
}

template <class T>
bool ultimate_tic_tac_toe_board<T>::is_draw()
{
    return this->n_moves == 81 && !this->is_win();
}

template <class T>
bool ultimate_tic_tac_toe_board<T>::game_is_over()
{
    return this->is_draw() || this->is_win();
}

template <class T>
bool ultimate_tic_tac_toe_board<T>::is_win()
{
    // Check rows and columns of final_board
    for (int i = 0; i < 3; i++)
    {
        if ((this->final_board[i][0] == this->final_board[i][1] &&
                this->final_board[i][1] == this->final_board[i][2] &&
                this->final_board[i][0] != ' ') ||
            (this->final_board[0][i] == this->final_board[1][i] &&
                this->final_board[1][i] == this->final_board[2][i] &&
                this->final_board[0][i] != ' '))
        {
            return true;
        }
    }

    // Check diagonals of final_board
    if ((this->final_board[0][0] == this->final_board[1][1] &&
            this->final_board[1][1] == this->final_board[2][2] &&
            this->final_board[0][0] != ' ')
        ||
        (this->final_board[0][2] == this->final_board[1][1] &&
            this->final_board[1][1] == this->final_board[2][0] &&
            this->final_board[0][2] != ' '))
    {
        return true;
    }
    return false;
}

template <class T>
bool ultimate_tic_tac_toe_board<T>::update_board(int x, int y, T symbol)
{
    if (this->final_board[x / 3][y / 3] != ' ')
    {
        cout << "You can't play here again.\n";
        return false;
    }
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns)
    {
        cout << "\r\rYou're going outside the board.\n";
        return false;
    }
    if (this->board[x][y] != ' ')
    {
        cout << "\r\rYou can't play on a played cell.\n";
        return false;
    }
    ++this->n_moves;
    this->board[x][y] = symbol;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                // Check rows
                if (this->board[k + 3 * i][3 * j] == this->board[k + 3 * i][1 + 3 * j] &&
                    this->board[k + 3 * i][1 + 3 * j] == this->board[k + 3 * i][2 + 3 * j] &&
                    this->board[k + 3 * i][3 * j] != ' ')
                {
                    if (this->final_board[i][j] == ' ') this->final_board[i][j] = this->board[k + 3 * i][3 * j];
                }

                // Check columns
                if (this->board[3 * j][k + 3 * i] == this->board[1 + 3 * j][k + 3 * i] &&
                    this->board[1 + 3 * j][k + 3 * i] == this->board[2 + 3 * j][k + 3 * i] &&
                    this->board[3 * j][k + 3 * i] != ' ')
                {
                    if (this->final_board[j][i] == ' ') this->final_board[j][i] = this->board[3 * j][k + 3 * i];
                }

                // Check diagonals
                if (this->board[3 * i][3 * j] == this->board[3 * i + 1][3 * j + 1] &&
                    this->board[3 * i + 1][3 * j + 1] == this->board[3 * i + 2][3 * j + 2] &&
                    this->board[3 * i][3 * j] != ' ')
                {
                    if (this->final_board[i][j] == ' ') this->final_board[i][j] = this->board[3 * i][3 * j];
                }

                if (this->board[3 * i][3 * j + 2] == this->board[3 * i + 1][3 * j + 1] &&
                    this->board[3 * i + 1][3 * j + 1] == this->board[3 * i + 2][3 * j] &&
                    this->board[3 * i][3 * j + 2] != ' ')
                {
                    if (this->final_board[i][j] == ' ') this->final_board[i][j] = this->board[3 * i][3 * j + 2];
                }
            }
        }
    }
    return true;
}

template <class T>
ultimate_tic_tac_toe_player<T>::ultimate_tic_tac_toe_player(string n, T symbol)
    : Player<T>(n, symbol)
{
}

template <class T>
void ultimate_tic_tac_toe_player<T>::getmove(int& x, int& y)
{
    char a, b;
    cout << this->name << ", enter the coordinates of the cell containing \'"
        << this->symbol << "\' [0 - 8]: ";
    while (cin >> a >> b)
    {
        if (isdigit(a) && isdigit(b))
        {
            x = a - '0', y = b - '0';
            break;
        }
        else
        {
            cout << "Enter integers: ";
        }
    }
}

template <class T>
ultimate_tic_tac_toe_random_player<T>::ultimate_tic_tac_toe_random_player(T symbol)
    : RandomPlayer<T>(symbol)
{
    this->name = this->symbol;
}

template <class T>
void ultimate_tic_tac_toe_random_player<T>::getmove(int& x, int& y)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution coordinates(0, 8);
    x = coordinates(gen);
    y = coordinates(gen);
}

#endif
