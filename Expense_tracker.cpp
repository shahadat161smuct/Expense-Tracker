#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

struct Expense {
    string person;
    string category;
    double amount;
    string description;
};

vector<Expense> expenses;

void saveExpense(const Expense &e) {
    ofstream file("expenses.txt", ios::app);
    file << e.person << " " << e.category << " " << e.amount << " " << e.description << "\n";
    file.close();
}

void addExpense() {
    Expense e;
    cout << "Enter person's name: ";
    cin >> e.person;
    cout << "Enter category: ";
    cin >> e.category;
    cout << "Enter amount: ";
    cin >> e.amount;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, e.description);
    expenses.push_back(e);
    saveExpense(e);
    cout << "Expense added successfully!\n";
}

void showExpenses() {
    cout << "\nAll Expenses:\n";
    cout << left << setw(15) << "Person" << setw(15) << "Category" << setw(10) << "Amount" << "Description" << endl;
    cout << "------------------------------------------------------\n";
    for (const auto &e : expenses) {
        cout << left << setw(15) << e.person << setw(15) << e.category << setw(10) << e.amount << e.description << endl;
    }
}

void loadExpenses() {
    ifstream file("expenses.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Expense e;
        ss >> e.person >> e.category >> e.amount;
        ss.ignore();
        getline(ss, e.description);
        expenses.push_back(e);
    }
    file.close();
}

void showTotalExpense() {
    double total = 0;
    for (const auto &e : expenses) {
        total += e.amount;
    }
    cout << "\nTotal Expense: " << total << "\n";
}

void showPersonExpense() {
    string name;
    cout << "Enter person's name: ";
    cin >> name;
    double total = 0;
    cout << "\nExpenses for " << name << ":\n";
    cout << left << setw(15) << "Category" << setw(10) << "Amount" << "Description" << endl;
    cout << "---------------------------------------------\n";
    for (const auto &e : expenses) {
        if (e.person == name) {
            cout << left << setw(15) << e.category << setw(10) << e.amount << e.description << endl;
            total += e.amount;
        }
    }
    cout << "Total Expense for " << name << ": " << total << "\n";
}

void clearAllExpenses() {
    ofstream file("expenses.txt", ios::trunc);
    file.close();
    expenses.clear();
    cout << "All expenses have been deleted successfully!\n";
}

int main() {
    loadExpenses();
    int choice;
    do {
        cout << "\nExpense Tracker\n";
        cout << "1. Add Expense\n2. Show Expenses\n3. Show Total Expense\n4. Show Person's Expense\n5. Clear All Expenses\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: showExpenses(); break;
            case 3: showTotalExpense(); break;
            case 4: showPersonExpense(); break;
            case 5: clearAllExpenses(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again!\n";
        }
    } while (choice != 6);

    return 0;
}
