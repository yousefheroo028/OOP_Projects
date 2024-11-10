#include <iostream>
#include "Headers.h"

using namespace std;

int main() {
    cout << "Hello user, welcome to using our program...\n";
    cout << "\nChoose reading from file or generate unique labels: \n1- From file.\n2- Generate unique labels.\n";
    char ope;
    cin >> ope;
    while (ope != '1' && ope != '2') {
        cout << "Please, enter a valid input: ";
        cin.ignore();
        cin.clear();
        cin >> ope;
    }
    if (ope == '1') {
        cin.ignore();
        cin.clear();
        cout << "Type the label you want: ";
        string label;
        getline(cin, label);
        cout << "\nType the beginning of the counter: ";
        int counter;
        cin >> counter;
        FileLabelGenerator fileLabelNumbers(label, counter, "file.txt");
        cout << fileLabelNumbers.nextLabel();
    } else if (ope == '2') {
        cin.ignore();
        cin.clear();
        cout << "Type the label you want: ";
        string label;
        getline(cin, label);
        cout << "\nType the beginning of the counter: ";
        int counter;
        cin >> counter;
        LabelGenerator labelNumbers(label, counter);
        cout << "\nEnter the number of labels you want: ";
        int number_of_labels;
        cin >> number_of_labels;
        for (int i = 0; i < number_of_labels; ++i) {
            cout << labelNumbers.nextLabel();
            if (i < number_of_labels - 1) cout << '\n';
        }
    }
    return 0;
}
