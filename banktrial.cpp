#include <iostream>
#include <string>
using namespace std;

// Base class
class Account {
protected:
    string accountHolder;
    string accountNumber;
    double balance;

public:
    Account(string name, string accNum, double initialBalance = 0.0) {
        accountHolder = name;
        accountNumber = accNum;
        balance = initialBalance;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nDeposited $" << amount;
            cout << "\nNew balance: $" << balance << endl;
        } else {
            cout << "\nInvalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "\nWithdrawn $" << amount;
            cout << "\nNew balance: $" << balance << endl;
        } else {
            cout << "\nInvalid withdrawal amount or insufficient funds!" << endl;
        }
    }

    virtual void checkBalance() {
        cout << "\nAccount Details:";
        cout << "\nHolder: " << accountHolder;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nCurrent Balance: $" << balance << endl;
    }
};

// First derived class
class SavingsAccount : public Account {
protected:
    double interestRate;

public:
    SavingsAccount(string name, string accNum, double initialBalance = 0.0, double rate = 0.05)
        : Account(name, accNum, initialBalance) {
        interestRate = rate;
    }

    void addInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "\nInterest added: $" << interest;
        cout << "\nNew balance: $" << balance << endl;
    }

    void checkBalance() override {
        Account::checkBalance();
        cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
    }
};

// Second derived class (multilevel inheritance)
class FixedDepositAccount : public SavingsAccount {
private:
    int lockPeriod; // in months
    bool isLocked;

public:
    FixedDepositAccount(string name, string accNum, double initialBalance, 
                       double rate = 0.08, int period = 12)
        : SavingsAccount(name, accNum, initialBalance, rate) {
        lockPeriod = period;
        isLocked = true;
    }

    void withdraw(double amount) override {
        if (isLocked) {
            cout << "\nCannot withdraw from Fixed Deposit before lock period!" << endl;
            return;
        }
        SavingsAccount::withdraw(amount);
    }

    void checkBalance() override {
        SavingsAccount::checkBalance();
        cout << "Lock Period: " << lockPeriod << " months" << endl;
        cout << "Status: " << (isLocked ? "Locked" : "Unlocked") << endl;
    }

    void unlock() {
        isLocked = false;
        cout << "\nAccount unlocked for withdrawals" << endl;
    }
};

int main() {
    string name, accountNum;
    double initialBalance;
    int accountType;

    cout << "Enter account holder name: ";
    getline(cin, name);
    cout << "Enter account number: ";
    getline(cin, accountNum);
    cout << "Enter initial balance: $";
    cin >> initialBalance;
    
    cout << "\nSelect Account Type:";
    cout << "\n1. Basic Account";
    cout << "\n2. Savings Account";
    cout << "\n3. Fixed Deposit Account";
    cout << "\nEnter choice (1-3): ";
    cin >> accountType;

    Account* account;
    switch(accountType) {
        case 1:
            account = new Account(name, accountNum, initialBalance);
            break;
        case 2:
            account = new SavingsAccount(name, accountNum, initialBalance);
            break;
        case 3:
            account = new FixedDepositAccount(name, accountNum, initialBalance);
            break;
        default:
            cout << "Invalid choice! Creating basic account.\n";
            account = new Account(name, accountNum, initialBalance);
    }

    int choice;
    double amount;

    do {
        cout << "\n=== Banking Menu ===";
        cout << "\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Check Balance";
        cout << "\n4. Add Interest (Savings/Fixed Deposit Only)";
        cout << "\n5. Unlock Fixed Deposit";
        cout << "\n6. Exit";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter deposit amount: $";
                cin >> amount;
                account->deposit(amount);
                break;
            case 2:
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                account->withdraw(amount);
                break;
            case 3:
                account->checkBalance();
                break;
            case 4:
                if (SavingsAccount* sav = dynamic_cast<SavingsAccount*>(account)) {
                    sav->addInterest();
                } else {
                    cout << "\nNot a savings account!" << endl;
                }
                break;
            case 5:
                if (FixedDepositAccount* fd = dynamic_cast<FixedDepositAccount*>(account)) {
                    fd->unlock();
                } else {
                    cout << "\nNot a fixed deposit account!" << endl;
                }
                break;
            case 6:
                cout << "\nThank you for using our banking system!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 6);

    delete account;
    return 0;
}