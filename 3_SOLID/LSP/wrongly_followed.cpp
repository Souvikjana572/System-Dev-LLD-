// This code demonstrates a violation of the Liskov Substitution Principle (LSP) in C++. The FixedTermAccount class does not adhere to the LSP because it throws an exception when the withdraw method is called, which is not expected behavior for an Account. This means that if we substitute a FixedTermAccount for an Account, it will break the functionality of the BankClient class, which expects all accounts to support withdrawals. In contrast, the SavingAccount and CurrentAccount classes adhere to LSP by allowing withdrawals without throwing exceptions.
#include <iostream>
#include <vector>
#include <typeinfo>
#include <stdexcept>

using namespace std;

class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account {
private:
    double balance;

public:
    SavingAccount() { 
        balance = 0; 
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Savings Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Savings Account. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Savings Account!\n";
        }
    }
};

class CurrentAccount : public Account {
private:
    double balance;

public:
    CurrentAccount() { 
        balance = 0; 
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Current Account. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Current Account!\n";
        }
    }
};

class FixedTermAccount : public Account {
private:
    double balance;

public:
    FixedTermAccount() { 
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " in Fixed Term Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

//Client class
class BankClient {
private:
    vector<Account*> accounts;

public:
    BankClient(vector<Account*> accounts) { 
        this->accounts = accounts; 
    }

    void processTransactions() {
        for (Account* acc : accounts) {
            acc->deposit(1000);

            //Checking account type explicitly
            if (typeid(*acc) == typeid(FixedTermAccount)) {
                cout << "Skipping withdrawal for Fixed Term Account.\n";
            } else {
                try {
                    acc->withdraw(500);
                } catch (const logic_error& e) {
                    cout << "Exception: " << e.what() << endl;
                }
            }
        }
    }
};

int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions();

    return 0;
}