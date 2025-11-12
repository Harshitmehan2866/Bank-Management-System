#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
private:
    string name;
    int accountNumber;
    int id;
    double balance;

public:
    // Constructor
    Customer(string n, int accNo, int ID, double bal = 0.0)
        : name(n), accountNumber(accNo), id(ID), balance(bal) {}

    // Getters
    int getID() const { return id; }
    string getName() const { return name; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    // Deposit Function
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "✅ Amount deposited successfully! New balance: " << balance << endl;
        } else {
            cout << "❌ Invalid amount entered!" << endl;
        }
    }

    // Withdraw Function
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "✅ Withdrawal successful! Remaining balance: " << balance << endl;
        } else {
            cout << "❌ Invalid or insufficient balance!" << endl;
        }
    }

    // Display Function
    void display() const {
        cout << "\n--- Customer Details ---";
        cout << "\nName: " << name
             << "\nAccount Number: " << accountNumber
             << "\nCustomer ID: " << id
             << "\nBalance: " << balance << endl;
    }
};

class Bank {
private:
    vector<Customer> customers;

public:
    // Add new customer
    void addCustomer() {
        string name;
        int accNo, id;
        double initialBalance;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter Customer Name: ";
        getline(cin, name);

        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Unique Customer ID: ";
        cin >> id;

        cout << "Enter Initial Balance: ";
        cin >> initialBalance;

        customers.emplace_back(name, accNo, id, initialBalance);
        cout << "✅ Customer added successfully!\n";
    }

    // Login existing customer
    Customer* login() {
        string name;
        int id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n--- Customer Login ---\n";
        cout << "Enter Your Name: ";
        getline(cin, name);

        cout << "Enter Your Customer ID: ";
        cin >> id;

        for (auto &cust : customers) {
            if (cust.getID() == id && cust.getName() == name) {
                cout << "\n✅ Login Successful! Welcome, " << name << "!\n";
                return &cust;
            }
        }
        cout << "❌ Invalid Name or ID!\n";
        return nullptr;
    }

    // Display all customers (Admin view)
    void displayAll() const {
        if (customers.empty()) {
            cout << "\nNo customers found!\n";
            return;
        }

        cout << "\n--- All Customer Details ---\n";
        for (const auto &cust : customers)
            cust.display();
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Add New Customer";
        cout << "\n2. Customer Login";
        cout << "\n3. Display All Customers (Admin)";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            bank.addCustomer();
        } 
        else if (choice == 2) {
            Customer* loggedIn = bank.login();
            if (loggedIn != nullptr) {
                int subChoice;
                do {
                    cout << "\n--- Customer Menu ---";
                    cout << "\n1. Check Balance";
                    cout << "\n2. Deposit Money";
                    cout << "\n3. Withdraw Money";
                    cout << "\n4. Display Account Details";
                    cout << "\n5. Logout";
                    cout << "\nEnter your choice: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Your Balance: " << loggedIn->getBalance() << endl;
                            break;
                        case 2: {
                            double amt;
                            cout << "Enter amount to deposit: ";
                            cin >> amt;
                            loggedIn->deposit(amt);
                            break;
                        }
                        case 3: {
                            double amt;
                            cout << "Enter amount to withdraw: ";
                            cin >> amt;
                            loggedIn->withdraw(amt);
                            break;
                        }
                        case 4:
                            loggedIn->display();
                            break;
                        case 5:
                            cout << "Logging out...\n";
                            break;
                        default:
                            cout << "❌ Invalid choice! Try again.\n";
                    }
                } while (subChoice != 5);
            }
        } 
        else if (choice == 3) {
            bank.displayAll();
        } 
        else if (choice == 4) {
            cout << "🙏 Thank you for using the system!\n";
            break;
        } 
        else {
            cout << "❌ Invalid choice! Try again.\n";
        }
    }

    return 0;
}
