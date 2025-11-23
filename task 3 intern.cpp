#include <iostream>
using namespace std;

const int MAX_ACCOUNTS = 10;
const int MAX_TRANSACTIONS = 20;
const int MAX_CUSTOMERS = 10;

class Transaction {
public:
    int transactionID;
    string type;
    float amount;
    string dateTime;
    int fromAcc;
    int toAcc;

    Transaction() {
        transactionID = 0;
        type = "";
        amount = 0;
        dateTime = "";
        fromAcc = -1;
        toAcc = -1;
    }

    void show() {
        cout << "Transaction ID: " << transactionID << endl;
        cout << "Type: " << type << endl;
        cout << "Amount: " << amount << endl;
        cout << "Date: " << dateTime << endl;
        if (type == "Transfer") {
            cout << "From Account: " << fromAcc 
                 << " To Account: " << toAcc << endl;
        }
        cout << "-----------------------\n";
    }
};

class Account {
public:
    int accountNumber;
    int customerID;
    float balance;

    Transaction history[MAX_TRANSACTIONS];
    int transactionCount;

    Account() {
        accountNumber = -1;
        customerID = -1;
        balance = 0;
        transactionCount = 0;
    }

    void addTransaction(string type, float amt, int fromA = -1, int toA = -1) {
        if (transactionCount < MAX_TRANSACTIONS) {
            history[transactionCount].transactionID = transactionCount + 1;
            history[transactionCount].type = type;
            history[transactionCount].amount = amt;
            history[transactionCount].dateTime = "Today";
            history[transactionCount].fromAcc = fromA;
            history[transactionCount].toAcc = toA;

            transactionCount++;
        }
    }

    void deposit(float amount) {
        balance += amount;
        addTransaction("Deposit", amount);
        cout << "Deposited " << amount << " successfully.\n";
    }

    void withdraw(float amount) {
        if (amount <= balance) {
            balance -= amount;
            addTransaction("Withdrawal", amount);
            cout << "Withdrawn " << amount << " successfully.\n";
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    void showBalance() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl << endl;
    }

    void viewTransactions() {
        cout << "\n--- Transaction History for Account " 
             << accountNumber << " ---\n";

        for (int i = 0; i < transactionCount; i++) {
            history[i].show();
        }
    }
};

class Customer {
public:
    int customerID;
    string name;
    string phone;

    Account accounts[MAX_ACCOUNTS];
    int accountCount;

    Customer() {
        customerID = 0;
        name = "";
        phone = "";
        accountCount = 0;
    }

    void createCustomer(int id, string n, string p) {
        customerID = id;
        name = n;
        phone = p;
    }

    void addAccount(int accNo) {
        if (accountCount < MAX_ACCOUNTS) {
            accounts[accountCount].accountNumber = accNo;
            accounts[accountCount].customerID = customerID;
            accounts[accountCount].balance = 0;
            accountCount++;
        }
    }

    Account* getAccount(int accNo) {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].accountNumber == accNo)
                return &accounts[i];
        }
        return nullptr;
    }

    void showInfo() {
        cout << "\n=== Customer Information ===\n";
        cout << "Customer ID: " << customerID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Accounts: " << accountCount << endl;
    }
};

void transferMoney(Account* fromAcc, Account* toAcc, float amount) {
    if (fromAcc->balance >= amount) {
        fromAcc->withdraw(amount);
        toAcc->deposit(amount);

        fromAcc->addTransaction("Transfer", amount, fromAcc->accountNumber, toAcc->accountNumber);
        toAcc->addTransaction("Transfer", amount, fromAcc->accountNumber, toAcc->accountNumber);

        cout << "Transfer successful!\n";
    } else {
        cout << "Not enough balance for transfer!\n";
    }
}

int main() {
    Customer customers[MAX_CUSTOMERS];
    int customerCount = 0;

    cout << "Welcome to the Bank System!\n";

    // User enters their details
    string name, phone;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your phone number: ";
    getline(cin, phone);

    customers[customerCount].createCustomer(customerCount + 1, name, phone);

    // Create two accounts
    int acc1No, acc2No;
    cout << "Enter first account number: ";
    cin >> acc1No;
    cout << "Enter second account number: ";
    cin >> acc2No;

    customers[customerCount].addAccount(acc1No);
    customers[customerCount].addAccount(acc2No);

    Account* acc1 = customers[customerCount].getAccount(acc1No);
    Account* acc2 = customers[customerCount].getAccount(acc2No);

    int choice;
    do {
        cout << "\n--- Bank Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. Show Balance\n5. View Transactions\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int accNo;
            float amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            Account* acc = customers[customerCount].getAccount(accNo);
            if (acc) acc->deposit(amount);
            else cout << "Account not found!\n";
            break;
        }
        case 2: {
            int accNo;
            float amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            Account* acc = customers[customerCount].getAccount(accNo);
            if (acc) acc->withdraw(amount);
            else cout << "Account not found!\n";
            break;
        }
        case 3: {
            int from, to;
            float amount;
            cout << "Enter FROM account number: ";
            cin >> from;
            cout << "Enter TO account number: ";
            cin >> to;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            Account* fromAcc = customers[customerCount].getAccount(from);
            Account* toAcc = customers[customerCount].getAccount(to);
            if (fromAcc && toAcc) transferMoney(fromAcc, toAcc, amount);
            else cout << "Invalid account number!\n";
            break;
        }
        case 4: {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;
            Account* acc = customers[customerCount].getAccount(accNo);
            if (acc) acc->showBalance();
            else cout << "Account not found!\n";
            break;
        }
        case 5: {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;
            Account* acc = customers[customerCount].getAccount(accNo);
            if (acc) acc->viewTransactions();
            else cout << "Account not found!\n";
            break;
        }
        case 0:
            cout << "Thank you for using the Bank System.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
