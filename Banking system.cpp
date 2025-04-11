#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string type;
    float amount;

    Transaction(string t, float a) {
        type = t;
        amount = a;
    }

    void display() {
        cout << "Transaction: " << type << ", Amount: $" << fixed << setprecision(2) << amount << endl;
    }
};


class Account {
private:
    static int nextAccountNumber;
    int accountNumber;
    float balance;
    vector<Transaction> transactions;

public:
    Account() {
        accountNumber = nextAccountNumber++;
        balance = 0.0;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    float getBalance() const {
        return balance;
    }

    void deposit(float amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
    }

    bool withdraw(float amount) {
        if (amount > balance)
            return false;
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        return true;
    }

    bool transfer(Account &toAccount, float amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            string msg = "Transfer to Account " + toString(toAccount.getAccountNumber());
            transactions.push_back(Transaction(msg, amount));
            return true;
        }
        return false;
    }

    string toString(int num) {
        
        char buf[20];
        sprintf(buf, "%d", num);
        return string(buf);
    }

    void displayAccount() {
        cout << "Account Number: " << accountNumber << ", Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void displayTransactions() {
        if (transactions.empty()) {
            cout << "No transactions found." << endl;
        } else {
            for (int i = 0; i < transactions.size(); i++) {
                transactions[i].display();
            }
        }
    }
};

int Account::nextAccountNumber = 1001;


class Customer {
private:
    string name;
    string email;
    Account account;

public:
    Customer(string n, string e) {
        name = n;
        email = e;
    }

    string getName() const {
        return name;
    }

    Account& getAccount() {
        return account;
    }

    void displayCustomer() {
        cout << "\nCustomer: " << name << ", Email: " << email << endl;
        account.displayAccount();
    }
};


class Bank {
private:
    vector<Customer> customers;

public:
    void createCustomer(string name, string email) {
        customers.push_back(Customer(name, email));
        cout << "Customer created successfully.\n";
    }

    void showAllCustomers() {
        for (int i = 0; i < customers.size(); i++) {
            customers[i].displayCustomer();
        }
    }

    Customer* findCustomer(string name) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getName() == name)
                return &customers[i];
        }
        return NULL;
    }

    void bankingMenu() {
        int choice;
        string name;
        float amount;

        while (true) {
            cout << "\n===== Bank Menu =====\n";
            cout << "1. Create Customer\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Transfer\n";
            cout << "5. View Account\n";
            cout << "6. View Transactions\n";
            cout << "7. Show All Customers\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    {
                        string cname, email;
                        cout << "Enter name: ";
                        cin >> cname;
                        cout << "Enter email: ";
                        cin >> email;
                        createCustomer(cname, email);
                        break;
                    }
                case 2:
                    {
                        cout << "Enter customer name: ";
                        cin >> name;
                        Customer *c = findCustomer(name);
                        if (c) {
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            c->getAccount().deposit(amount);
                            cout << "Deposit successful.\n";
                        } else {
                            cout << "Customer not found.\n";
                        }
                        break;
                    }
                case 3:
                    {
                        cout << "Enter customer name: ";
                        cin >> name;
                        Customer *c = findCustomer(name);
                        if (c) {
                            cout << "Enter amount to withdraw: ";
                            cin >> amount;
                            if (c->getAccount().withdraw(amount)) {
                                cout << "Withdrawal successful.\n";
                            } else {
                                cout << "Insufficient balance.\n";
                            }
                        } else {
                            cout << "Customer not found.\n";
                        }
                        break;
                    }
                case 4:
                    {
                        string toName;
                        cout << "Enter sender's name: ";
                        cin >> name;
                        cout << "Enter receiver's name: ";
                        cin >> toName;
                        Customer *from = findCustomer(name);
                        Customer *to = findCustomer(toName);
                        if (from && to) {
                            cout << "Enter amount to transfer: ";
                            cin >> amount;
                            if (from->getAccount().transfer(to->getAccount(), amount)) {
                                cout << "Transfer successful.\n";
                            } else {
                                cout << "Transfer failed. Insufficient funds.\n";
                            }
                        } else {
                            cout << "Sender or Receiver not found.\n";
                        }
                        break;
                    }
                case 5:
                    {
                        cout << "Enter customer name: ";
                        cin >> name;
                        Customer *c = findCustomer(name);
                        if (c) {
                            c->displayCustomer();
                        } else {
                            cout << "Customer not found.\n";
                        }
                        break;
                    }
                case 6:
                    {
                        cout << "Enter customer name: ";
                        cin >> name;
                        Customer *c = findCustomer(name);
                        if (c) {
                            c->getAccount().displayTransactions();
                        } else {
                            cout << "Customer not found.\n";
                        }
                        break;
                    }
                case 7:
                    showAllCustomers();
                    break;
                case 0:
                    cout << "Thank you for using the banking system!\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    Bank bank;
    bank.bankingMenu();
    return 0;
}

