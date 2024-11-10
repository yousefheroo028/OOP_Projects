#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LabelGenerator {
protected:
    string label;
    int counter;
public:
    LabelGenerator(const string &text, int c) {
        label = text;
        counter = c;
    }

    virtual string nextLabel() {
        return label + to_string(counter++);
    }
};

class FileLabelGenerator : public LabelGenerator {
private:
    fstream file;
public:
    FileLabelGenerator(const string &text, int c, const string &fileName) : LabelGenerator(text, c) {
        label = text;
        counter = c;
        file.open(fileName, ios::in);
    }

    string nextLabel() override {
        string sentence;
        if (file) {
            while (getline(file, sentence, '\n')) {
                cout << label << to_string(counter++) << ' ' << sentence << '\n';
            }
        }
        return "";
    }
};