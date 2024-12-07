#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

template<class T>
class Set {
private:
    vector<T> data;
    vector<T>::iterator first;
    vector<T>::iterator last;
public:
    Set() {
        data = vector<T>(0);
        first = data.begin();
        last = data.end();
    }

    explicit Set(vector<T> d) {
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
        data = d;
        first = data.begin();
        last = data.end();
    }

    explicit Set(const int &dSize, vector<T> d) {
        sort(d.begin(), d.end());
        d.erase(unique(d.begin(), d.end()), d.end());
        data = d;
        first = data.begin();
        last = data.end();
    }

    void add(T item) {
        for (int i = 0; i < data.size(); ++i) {
            if (data.at(i) == item) return;
        }
        data.push_back(item);
        sort(data.begin(), data.end());
        first = data.begin();
        last = data.end();
    }

    void remove(T item) {
        for (int i = 0; i < data.size(); ++i) {
            if (data.at(i) == item) {
                data.erase(first + i);
                sort(data.begin(), data.end());
                first = data.begin();
                last = data.end();
                return;
            }
        }
    }

    int get_size() {
        return data.size();
    }

    bool is_exist(T item) {
        for (const T &i: data) {
            if (item == i) return true;
        }
        return false;
    }

    vector<T>::iterator begin() {
        return first;
    }

    vector<T>::iterator end() {
        return last;
    }

    friend ostream &operator<<(ostream &print, Set<T> d) {
        print << "[ ";
        if (d.data.size()) {
            cout << fixed << d.data.front();
            for (int i = 1; i < d.data.size(); ++i) {
                print << ", " << fixed << d.data.at(i);
            }
        }
        print << " ]" << '\n';
        return print;
    }

    friend bool operator==(Set<T> a, Set<T> b) {
        if (a.data.size() != b.data.size()) return false;
        else {
            for (int i = 0; i < a.data.size(); ++i) {
                if (a.data.at(i) != b.data.at(i)) return false;
            }
        }
        return true;
    }

    friend bool operator!=(Set<T> a, Set<T> b) {
        if (a.data.size() != b.data.size()) return true;
        else {
            for (int i = 0; i < a.data.size(); ++i) {
                if (a.data.at(i) == b.data.at(i)) return true;
            }
        }
        return false;
    }

    void clear() {
        data.clear();
    }
};

void enter_data_int(Set<int> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) {
                data.add(stoi(temp));
                temp.clear();
            }
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(stoi(temp));
    }
}

void enter_data_float(Set<float> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) data.add(stof(temp));
            temp.clear();
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(stof(temp));
    }
}

void enter_data_double(Set<double> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) data.add(stod(temp));
            temp.clear();
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(stod(temp));
    }
}

void enter_data_long_double(Set<long double> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) data.add(stold(temp));
            temp.clear();
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(stold(temp));
    }
}

void enter_data_long_long(Set<long long> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) data.add(stoll(temp));
            temp.clear();
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(stoll(temp));
    }
}

void enter_data_string(Set<string> &data) {
    string items, temp;
    cin.ignore();
    getline(cin, items);
    for (int i = 0; i < items.size(); ++i) {
        if (isspace(items[i])) {
            if (temp.size()) data.add(temp);
            temp.clear();
        } else {
            temp += items[i];
        }
        if (i == items.size() - 1)
            if (temp.size()) data.add(temp);
    }
}

int main() {
    cout << "Welcome to using my program.\n";
    cout
            << "Enter the type of data: \n0. Exit\n1. int\n2. float\n3. double\n4. long double\n5. long long\n6. string\n=> ";
    string type;
    cin >> type;

    while (type != "0" && type != "1" && type != "2" && type != "3" && type != "4" && type != "5" && type != "6") {
        system("cls");
        cin.ignore();
        cin.clear();
        cout << "Enter a valid input: ";
        cin >> type;
    }

    if (type == "0") {
        cout << '\n', system("pause");
        exit(0);
    } else if (type == "1") {
        system("cls");
        Set<int> data;
        cout << "Enter the data: ";
        int member;
        enter_data_int(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        string opt;
        while (cin >> opt) {
            system("cls");
            if (opt == "0") break;
            else if (opt == "1") {
                cout << "Enter the element you want to add: ";
                cin >> member;
                data.add(member);
            } else if (opt == "2") {
                cout << "Enter the element you want to remove: ";
                cin >> member;
                data.remove(member);
            } else if (opt == "3") cout << data;
            else if (opt == "4") {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> member;
                cout << (data.is_exist(member) ? "Exists" : "Not exist");
            } else if (opt == "5") cout << "Number of elements = " << data.get_size();
            else if (opt == "6") {
                data.clear();
                cout << "Enter the data: ";
                enter_data_int(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }

    } else if (type == "2") {
        system("cls");
        Set<float> data;
        cout << "Enter the data: ";
        float member;
        enter_data_float(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        string opt;
        while (cin >> opt) {
            system("cls");
            if (opt == "0") break;
            else if (opt == "1") {
                cout << "Enter the element you want to add: ";
                cin >> member;
                data.add(member);
            } else if (opt == "2") {
                cout << "Enter the element you want to remove: ";
                cin >> member;
                data.remove(member);
            } else if (opt == "3") cout << data;
            else if (opt == "4") {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> member;
                cout << (data.is_exist(member) ? "Exists" : "Not exist");
            } else if (opt == "5") cout << "Number of elements = " << data.get_size();
            else if (opt == "6") {
                data.clear();
                cout << "Enter the data: ";
                enter_data_float(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }
    } else if (type == "3") {
        system("cls");

        Set<double> data;
        cout << "Enter the data: ";
        string item;
        double member;
        enter_data_double(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        string opt;
        while (cin >> opt) {
            system("cls");

            if (opt == "0") break;
            else if (opt == "1") {
                cout << "Enter the element you want to add: ";
                cin >> member;
                data.add(member);
            } else if (opt == "2") {
                cout << "Enter the element you want to remove: ";
                cin >> member;
                data.remove(member);
            } else if (opt == "3") cout << data;
            else if (opt == "4") {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> member;
                cout << (data.is_exist(member) ? "Exists" : "Not exist");
            } else if (opt == "5") cout << "Number of elements = " << data.get_size();
            else if (opt == "6") {
                data.clear();
                cout << "Enter the data: ";
                enter_data_double(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }
    } else if (type == "4") {
        system("cls");

        Set<long double> data;
        cout << "Enter the data: ";
        string item;
        long double member;
        enter_data_long_double(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        string opt;
        while (cin >> opt) {
            system("cls");

            if (opt == "0") break;
            else if (opt == "1") {
                cout << "Enter the element you want to add: ";
                cin >> member;
                data.add(member);
            } else if (opt == "2") {
                cout << "Enter the element you want to remove: ";
                cin >> member;
                data.remove(member);
            } else if (opt == "3") cout << data;
            else if (opt == "4") {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> member;
                cout << (data.is_exist(member) ? "Exists" : "Not exist");
            } else if (opt == "5") cout << "Number of elements = " << data.get_size();
            else if (opt == "6") {
                data.clear();
                cout << "Enter the data: ";
                enter_data_long_double(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }

    } else if (type == "5") {
        system("cls");

        Set<long long> data;
        cout << "Enter the data: ";
        string item;
        long long member;
        enter_data_long_long(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        string opt;
        while (cin >> opt) {
            system("cls");

            if (opt == "0") break;
            else if (opt == "1") {
                cout << "Enter the element you want to add: ";
                cin >> member;
                data.add(member);
            } else if (opt == "2") {
                cout << "Enter the element you want to remove: ";
                cin >> member;
                data.remove(member);
            } else if (opt == "3") cout << data;
            else if (opt == "4") {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> member;
                cout << (data.is_exist(member) ? "Exists" : "Not exist");
            } else if (opt == "5") cout << "Number of elements = " << data.get_size();
            else if (opt == "6") {
                data.clear();
                cout << "Enter the data: ";
                enter_data_long_long(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }

    } else if (type == "6") {
        system("cls");

        Set<string> data;
        cout << "Enter the data: ";
        string item;
        enter_data_string(data);
        cout << "Choose the operation you want: \n"
                "0. Exit\n1. Add an element\n2. Remove an element\n"
             << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        char opt;
        while (cin >> opt) {
            system("cls");
            if (opt == '0') break;
            else if (opt == '1') {
                cout << "Enter the element you want to add: ";
                cin >> item;
                data.add(item);
            } else if (opt == '2') {
                cout << "Enter the element you want to remove: ";
                cin >> item;
                data.remove(item);
            } else if (opt == '3') cout << data;
            else if (opt == '4') {
                cout << "Enter the element you want to Check if it is exist or not: ";
                cin >> item;
                cout << (data.is_exist(item) ? "Exists" : "Not exist");
            } else if (opt == '5') cout << "Number of elements = " << data.get_size();
            else if (opt == '6') {
                data.clear();
                cout << "Enter the data: ";
                enter_data_string(data);
            } else {
                cout << "Enter a valid input.";
            }
            cout << "\nChoose the operation you want: \n"
                    "0. Exit\n1. Add an element\n2. Remove an element\n"
                 << "3. Print the data\n4. Check if an element is exist\n5. Print the number of elements\n6. Modify the data\n=> ";
        }
    }

    main();

    cout << '\n', system("pause");
    return 0;
}