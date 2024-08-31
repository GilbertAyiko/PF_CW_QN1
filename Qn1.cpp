#include <iostream>
#include <unordered_map>
#include <limits>
#include <iomanip>

using namespace std;

// Struct to hold account information
struct Account {
    string password;
    double balance;
};

// Global variable to store accounts
unordered_map<string, Account> accounts;

// Function prototypes
void displayIntroMenu();
void createAccount();
bool login(string &userId);
void displayMainMenu(const string &userId);
void withdrawMoney(const string &userId);
void depositMoney(const string &userId);
void requestBalance(const string &userId);

int main() {
    char choice;
    string userId;

    cout << "Hi! Welcome to the ATM Machine!" << endl;

    do {
        displayIntroMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 'l': {
                if (login(userId)) {
                    char mainChoice;
                    do {
                        displayMainMenu(userId);
                        cin >> mainChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

                        switch (mainChoice) {
                            case 'd':
                                depositMoney(userId);
                                break;
                            case 'w':
                                withdrawMoney(userId);
                                break;
                            case 'r':
                                requestBalance(userId);
                                break;
                            case 'q':
                                cout << "Logging out..." << endl;
                                break;
                            default:
                                cout << "Invalid option. Please try again." << endl;
                        }
                    } while (mainChoice != 'q');
                } else {
                    cout << "* LOGIN FAILED! *" << endl;
                }
                break;
            }
            case 'c':
                createAccount();
                break;
            case 'q':
                cout << "Thank you for using the ATM Machine. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }

    } while (choice != 'q');

    return 0;
}

void displayIntroMenu() {
    cout << "Please select an option from the menu below:" << endl;
    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
}

void createAccount() {
    string userId, password;

    cout << "Please enter your user id: ";
    cin >> userId;
    cout << "Please enter your password: ";
    cin >> password;

    if (accounts.find(userId) != accounts.end()) {
        cout << "Account with this ID already exists. Please try logging in." << endl;
        return;
    }

    accounts[userId] = Account{password, 0.0}; // Initial balance is 0.0
    cout << "Thank You! Your account has been created!" << endl;
}

bool login(string &userId) {
    string password;

    cout << "Please enter your user id: ";
    cin >> userId;
    cout << "Please enter your password: ";
    cin >> password;

    if (accounts.find(userId) != accounts.end() && accounts[userId].password == password) {
        cout << "Access Granted!" << endl;
        return true;
    } else {
        return false;
    }
}

void displayMainMenu(const string &userId) {
    cout << "d -> Deposit Money" << endl;
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
}

void depositMoney(const string &userId) {
    double amount;

    cout << "Amount of deposit: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please try again." << endl;
        return;
    }

    accounts[userId].balance += amount;
    cout << "Deposit successful." << endl;
}

void withdrawMoney(const string &userId) {
    double amount;

    cout << "Amount of withdrawal: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please try again." << endl;
        return;
    }

    if (accounts[userId].balance >= amount) {
        accounts[userId].balance -= amount;
        cout << "Withdrawal successful." << endl;
    } else {
        cout << "Insufficient balance. Please try again." << endl;
    }
}

void requestBalance(const string &userId) {
    cout << "Your balance is $" << fixed << setprecision(2) << accounts[userId].balance << "." << endl;

}