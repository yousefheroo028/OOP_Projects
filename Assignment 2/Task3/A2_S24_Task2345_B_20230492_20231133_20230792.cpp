#include <iostream>
#include <random>
#include "4x4_Tic_Tac_Toe.h"
#include "Pyramid_Tic_Tac_Toe.h"
#include "Word_Tic-Tac-Toe.h"
#include "Inverted_X_O.h"
#include "Connect_4.h"

using namespace std;

int main()
{
    Player<char>* players[2];
    Board<char>* Board;
    while (true)
    {
        system("cls");
        cout << "Choose the game you want to play:\n"
            "0. Exit\n"
            "1. Pyramid Tic-Tac_Toe\n"
            "2. Four-in-a-row\n"
            "3. 5x5 Tic-Tac-Toe\n"
            "4. Word Tic-Tac-Toe\n"
            "5. Numerical Tic-Tac-Toe\n"
            "6. Misere Tic Tac Toe\n"
            "7. 4x4 Tic-Tac-Toe\n"
            "8. Ultimate Tic-Tac-Toe\n";
        char gameOPT, type, symbol;
        cin >> gameOPT;
        while (gameOPT != '0' && gameOPT != '1' && gameOPT != '2' && gameOPT != '3' &&
            gameOPT != '4' && gameOPT != '5' && gameOPT != '6' &&
            gameOPT != '7' && gameOPT != '8')
        {
            cout << "Enter a valid input: ";
            cin.ignore();
            cin.clear();
            cin >> gameOPT;
        }
        string player1, player2;
        switch (gameOPT)
        {
        case '0':
            cout << "Thanks for choosing our games.";
            cout << endl, system("pause");
            free(Board);
            free(players[0]);
            free(players[1]);
            return 0;
        case '1':
            Board = new Pyramid_Board<char>();
            Board->display_board();
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            while (type != '1' && type != '2')
            {
                cout << "Enter a valid input: ";
                cin.ignore();
                cin.clear();
                cin >> type;
            }
            switch (type)
            {
            case '1':
                cout << "Enter player 1's name: ";
                cin.ignore();
                getline(cin, player1);
                cout << player1 << ", choose the symbol (X or O): ";
                cin >> symbol;
                symbol = toupper(symbol);
                while (symbol != 'X' && symbol != 'O')
                {
                    cin.ignore();
                    cin.clear();
                    cout << player1 << ", enter X or O: ";
                    cin >> symbol;
                    symbol = toupper(symbol);
                }
                players[0] = new Pyramid_Player<char>(player1, symbol);
                break;
            case '2':
                symbol = (rand() % 2 ? 'X' : 'O');
                players[0] = new Pyramid_Random_Player<char>(symbol);
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            switch (type)
            {
            case '1':
                cout << "Enter player 2's name: ";
                cin.ignore();
                getline(cin, player2);
                players[1] = new Pyramid_Player<char>(player2, symbol == 'X' ? 'O' : 'X');
                break;
            case '2':
                players[1] = new Pyramid_Random_Player<char>(symbol == 'X' ? 'O' : 'X');
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            break;
        case '2':
            Board = new connect4_Board<char>();
            Board->display_board();
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            while (type != '1' && type != '2')
            {
                cout << "Enter a valid input: ";
                cin.ignore();
                cin.clear();
                cin >> type;
            }
            switch (type)
            {
            case '1':
                cout << "Enter player 1's name: ";
                cin.ignore();
                getline(cin, player1);
                cout << player1 << ", choose the symbol (X or O): ";
                cin >> symbol;
                symbol = toupper(symbol);
                while (symbol != 'X' && symbol != 'O')
                {
                    cin.ignore();
                    cin.clear();
                    cout << player1 << ", enter X or O: ";
                    cin >> symbol;
                    symbol = toupper(symbol);
                }
                players[0] = new HumanPlayer<char>(player1, symbol);
                break;
            case '2':
                symbol = (rand() % 2 ? 'X' : 'O');
                players[0] = new ComputerPlayer<char>(symbol);
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            switch (type)
            {
            case '1':
                cout << "Enter player 2's name: ";
                cin.ignore();
                getline(cin, player2);
                players[1] = new HumanPlayer<char>(player2, symbol == 'X' ? 'O' : 'X');
                break;
            case '2':
                players[1] = new ComputerPlayer<char>(symbol == 'X' ? 'O' : 'X');
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            break;
        case '4':
            Board = new Word_Board<char>();
            Board->display_board();
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            while (type != '1' && type != '2')
            {
                cout << "Enter a valid input: ";
                cin.ignore();
                cin.clear();
                cin >> type;
            }
            if (type == '1')
            {
                cout << "Enter player 1's name: ";
                cin.ignore();
                getline(cin, player1);
                players[0] = new Word_Player<char>(player1, ' ');
            }
            else if (type == '2')
            {
                players[0] = new Word_Random_Player<char>(' ');
            }
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            if (type == '1')
            {
                cout << "Enter player 2's name: ";
                cin.ignore();
                getline(cin, player2);
                players[1] = new Word_Player<char>(player2, ' ');
            }
            else if (type == '2')
            {
                players[1] = new Word_Random_Player<char>(' ');
            }
            break;
        case '6':
            Board = new Inverted_X_O_Board<char>();
            Board->display_board();
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            while (type != '1' && type != '2')
            {
                cout << "Enter a valid input: ";
                cin.ignore();
                cin.clear();
                cin >> type;
            }
            switch (type)
            {
            case '1':
                cout << "Enter player 1's name: ";
                cin.ignore();
                getline(cin, player1);
                cout << player1 << ", choose the symbol (X or O): ";
                cin >> symbol;
                symbol = toupper(symbol);
                while (symbol != 'X' && symbol != 'O')
                {
                    cin.ignore();
                    cin.clear();
                    cout << player1 << ", enter X or O: ";
                    cin >> symbol;
                    symbol = toupper(symbol);
                }
                players[1] = new Inverted_X_O_Player<char>(player1, symbol);
                break;
            case '2':
                symbol = (rand() % 2 ? 'X' : 'O');
                players[1] = new Inverted_X_O_Random_Player<char>(symbol);
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            switch (type)
            {
            case '1':
                cout << "Enter player 2's name: ";
                cin.ignore();
                getline(cin, player2);
                players[0] = new Inverted_X_O_Player<char>(player2, symbol == 'X' ? 'O' : 'X');
                break;
            case '2':
                players[0] = new Inverted_X_O_Random_Player<char>(symbol == 'X' ? 'O' : 'X');
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            break;
        case '7':
            Board = new fourBoard<char>();
            Board->display_board();
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            while (type != '1' && type != '2')
            {
                cout << "Enter a valid input: ";
                cin.ignore();
                cin.clear();
                cin >> type;
            }
            switch (type)
            {
            case '1':
                cout << "Enter player 1's name: ";
                cin.ignore();
                getline(cin, player1);
                cout << player1 << ", choose the symbol (X or O): ";
                cin >> symbol;
                symbol = toupper(symbol);
                while (symbol != 'X' && symbol != 'O')
                {
                    cin.ignore();
                    cin.clear();
                    cout << player1 << ", enter X or O: ";
                    cin >> symbol;
                    symbol = toupper(symbol);
                }
                players[0] = new fourPlayer<char>(player1, symbol);
                break;
            case '2':
                symbol = (rand() % 2 ? 'X' : 'O');
                players[0] = new random_fourPlayer<char>(symbol);
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            cout << "Choose type: \n1. Human\n2. Random Player\n=> ";
            cin >> type;
            switch (type)
            {
            case '1':
                cout << "Enter player 2's name: ";
                cin.ignore();
                getline(cin, player2);
                players[1] = new fourPlayer<char>(player2, symbol == 'X' ? 'O' : 'X');
                break;
            case '2':
                players[1] = new random_fourPlayer<char>(symbol == 'X' ? 'O' : 'X');
                break;
            default:
                cout << "Enter a valid input (1 or 2).";
            }
            break;
        case '3':
        case '5':
        case '8':
            Board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
            cout << "In progress...";
            break;
        default:
            break;
        }
        if (Board != nullptr && players[0] != nullptr && players[1] != nullptr)
        {
            GameManager<char> Game(Board, players);
            Game.run();
        }
        cout << endl, system("pause");
    }
}
