#include "FourInARowBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

int main() {

    int choice;
    connect4_Board<char>* board = new connect4_Board<char>();
    Player<char>* players[2];

    while (true) {
        // Display menu to the user
        cout << "Welcome to Connect 4 Game!" << endl;
        cout << "Choose the type of game:" << endl;
        cout << "1. Human vs Human" << endl;
        cout << "2. Human vs Computer Player" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        // Set up players based on the user's choice
        if (choice == 1) {
            // Human vs Human
            HumanPlayer<char>* player1 = new HumanPlayer<char>("Player 1", 'X');
            HumanPlayer<char>* player2 = new HumanPlayer<char>("Player 2", 'O');

            players[0] = player1;
            players[1] = player2;
            break;
        } else if (choice == 2) {
            // Human vs Random
            HumanPlayer<char>* player1 = new HumanPlayer<char>("Player 1", 'X');
            ComputerPlayer<char>* player2 = new ComputerPlayer<char>('O');

            players[0] = player1;
            players[1] = player2;
            break;
        } else {
            // Invalid choice
            cout << "Invalid choice! Please enter 1 or 2." << endl;
        }
    }

    players[0]->setBoard(board);
    players[1]->setBoard(board);

    GameManager<char> gameManager(board, players);
    gameManager.run();

    return 0;
}