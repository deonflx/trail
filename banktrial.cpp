#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;
    string accountNumber;

public:
    BankAccount(string name, string accNum, double initialBalance = 0.0) {
        accountHolder = name;
        accountNumber = accNum;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nSuccessfully deposited $" << amount;
            cout << "\nNew balance: $" << balance << endl;
        } else {
            cout << "\nInvalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "\nSuccessfully withdrawn $" << amount;
            cout << "\nNew balance: $" << balance << endl;
        } else {
            cout << "\nInvalid withdrawal amount or insufficient funds!" << endl;
        }
    }

    void checkBalance() {
        cout << "\nAccount Details:";
        cout << "\nHolder: " << accountHolder;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nCurrent Balance: $" << balance << endl;
    }
};

int main() {
    string name, accountNum;
    double initialBalance;
    
    cout << "Enter account holder name: ";
    getline(cin, name);
    cout << "Enter account number: ";
    getline(cin, accountNum);
    cout << "Enter initial balance: $";
    cin >> initialBalance;

    BankAccount account(name, accountNum, initialBalance);
    
    int choice;
    double amount;

    do {
        cout << "\n=== Banking Menu ===";
        cout << "\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Check Balance";
        cout << "\n4. Exit";
        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter deposit amount: $";
                cin >> amount;
                account.deposit(amount);
                break;
            case 2:
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                account.withdraw(amount);
                break;
            case 3:
                account.checkBalance();
                break;
            case 4:
                cout << "\nThank you for using our banking system!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}