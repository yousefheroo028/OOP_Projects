#ifndef INC_4X4_TIC_TAC_TOE_H
#define INC_4X4_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <random>

template <class T>
class fourBoard : public Board<T>
{
public:
    fourBoard();

    bool update_board(int x, int y, T symbol) override;

    void display_board() override;

    bool is_win() override;

    bool is_draw() override;

    bool game_is_over() override;
};

template <class T>
class fourPlayer : public Player<T>
{
public:
    fourPlayer(string n, T symbol);

    void getmove(int& x, int& y) override;
};

template <class T>
class random_fourPlayer : public RandomPlayer<T>
{
public:
    random_fourPlayer(T symbol);

    void getmove(int& x, int& y) override;
};

template <class T>
fourBoard<T>::fourBoard()
{
    this->rows = this->columns = 4;
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j)
        {
            this->board[i][j] = ' ';
        }
    }
    this->board[0][1] = 'X';
    this->board[0][3] = 'X';
    this->board[3][0] = 'X';
    this->board[3][2] = 'X';
    this->board[0][0] = 'O';
    this->board[0][2] = 'O';
    this->board[3][1] = 'O';
    this->board[3][3] = 'O';
}

template <class T>
void fourBoard<T>::display_board()
{
    system("cls");
    for (int i = 0; i < this->rows; ++i)
    {
        cout << ' ';
        for (int j = 0; j < this->columns; ++j)
        {
            if (this->board[i][j] != ' ') cout << "  " << this->board[i][j] << "   ";
            else cout << '(' << i << ", " << j << ')';
            if (j < this->columns - 1) cout << " | ";
        }
        if (i < this->rows - 1) cout << "\n-----------------------------------\n";
    }
    cout << '\n';
}

template <class T>
bool fourBoard<T>::update_board(int x, int y, T symbol)
{
    if (this->board[x][y] != symbol)
    {
        cout << "Choose a cell containing \'" << symbol << "\'\n";
        return false;
    }
    if (x >= 0 && y >= 0 && x < this->rows && y < this->columns)
    {
        char dir;
        cout << "Enter the direction:"
            "\n1. Up"
            "\n2. Down"
            "\n3. Left"
            "\n4. Right"
            "\n=> ";
        cin >> dir;
        while (dir != '1' && dir != '2' && dir != '3' && dir != '4')
        {
            cout << "Enter a valid input: ";
            cin.ignore();
            cin.clear();
            cin >> dir;
        }
        while (dir == '1' && x - 1 < 0 || dir == '2' && x + 1 >= this->rows || dir == '3' && y - 1 < 0 || dir == '4' &&
            y + 1 >= this->columns)
        {
            cout << "You're going outside the board.\nEnter another direction: ";
            cin >> dir;
        }
        while (
            dir == '4' && this->board[x][y + 1] != ' ' ||
            dir == '3' && this->board[x][y - 1] != ' ' ||
            dir == '2' && this->board[x + 1][y] != ' ' ||
            dir == '1' && this->board[x - 1][y] != ' ')
        {
            cout << "You can't step into a played cell.\nEnter another direction: ";
            cin >> dir;
        }
        if (dir == '4')
        {
            this->board[x][y] = ' ';
            y++;
        }
        else if (dir == '3')
        {
            this->board[x][y] = ' ';
            y--;
        }
        else if (dir == '1')
        {
            this->board[x][y] = ' ';
            x--;
        }
        else if (dir == '2')
        {
            this->board[x][y] = ' ';
            x++;
        }
        this->board[x][y] = symbol;
    }
    return true;
}

template <class T>
bool fourBoard<T>::is_draw()
{
    return false;
}

template <class T>
bool fourBoard<T>::is_win()
{
    for (int i = 0; i < this->rows; ++i)
    {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' '
            ||
            this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][1] != ' '
            ||
            this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' '
            ||
            this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[1][i] !=
            ' ')
        {
            return true;
        }
    }

    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ' ||
        this->board[1][1] == this->board[2][2] && this->board[2][2] == this->board[3][3] && this->board[1][1] != ' ' ||
        this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != ' ' ||
        this->board[1][2] == this->board[2][1] && this->board[2][1] == this->board[3][0] && this->board[1][2] != ' ')
    {
        return true;
    }
    return false;
}

template <class T>
bool fourBoard<T>::game_is_over()
{
    return this->is_win();
}

template <class T>
fourPlayer<T>::fourPlayer(string n, T symbol): Player<T>(n, symbol)
{
}

template <class T>
void fourPlayer<T>::getmove(int& x, int& y)
{
    char a, b;
    cout << this->name << ", enter the coordinates of the cell containing \'" << this->symbol << "\' [0 - 3]: ";
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
random_fourPlayer<T>::random_fourPlayer(T symbol): RandomPlayer<T>(symbol)
{
}

template <class T>
void random_fourPlayer<T>::getmove(int& x, int& y)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution coordinates(0, 3);
    x = coordinates(gen);
    y = coordinates(gen);
    cout << '(' << x << ", " << y << ')' << '\n';
}

#endif
