#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LabelGenerator {
protected:
    string label;
    int counter;
public:
    explicit LabelGenerator(const string &text, int c = 1) {
        label = text;
        counter = c;
    }

    virtual string nextLabel() {
        return label + to_string(counter++);
    }
};

class FileLabelGenerator : public LabelGenerator {
private:
    ifstream file;
public:
    FileLabelGenerator(const string &text, int c, const string &fileName) : LabelGenerator(text, c) {
        file.open(fileName);
    }

    string nextLabel() override {
        string sentence;
        if (file) {
            while (getline(file, sentence, '\n')) {
                cout << LabelGenerator::nextLabel() << ' ' << sentence << '\n';
            }
        }
        return "";
    }
};

int main() {
    cout << "Hello user, welcome to using our program...\n";
    cout << "\nChoose reading from file or generate unique labels: \n1- From file.\n2- Generate unique labels.\n";
    string ope;
    cin >> ope;
    while (ope != "1" && ope != "2") {
        cout << "Please, enter a valid input: ";
        cin.ignore();
        cin.clear();
        cin >> ope;
    }
    if (ope == "1") {
        cin.ignore();
        cin.clear();
        cout << "Type the label you want: ";
        string label;
        getline(cin, label);
        cout << "\nType the beginning of the counter: ";
        int counter;
        cin >> counter;
        cin.ignore();
        cin.clear();
        cout << "\nType the name of the file: ";
        string fileName;
        getline(cin, fileName);
        FileLabelGenerator fileLabelNumbers(label, counter, fileName);
        cout << fileLabelNumbers.nextLabel();
    } else if (ope == "2") {
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
    cout << endl, system("pause");
    return 0;
}