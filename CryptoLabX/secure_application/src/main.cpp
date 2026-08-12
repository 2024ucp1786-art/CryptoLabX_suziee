#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// -----------------------------
// Data Structures
// -----------------------------

struct Beneficiary {
    string name;
    string accountNumber;
};

struct User {
    int id;
    string username;
    string password;
    double balance;
    vector<Beneficiary> beneficiaries;
};

// -----------------------------
// Function Declarations
// -----------------------------

int login(vector<User>& users);
void bankingMenu(User& currentUser, vector<User>& users);

void checkBalance(const User& user);
void transferFunds(User& user);
void manageBeneficiaries(User& user);

void addBeneficiary(User& user);
void viewBeneficiaries(const User& user);
void deleteBeneficiary(User& user);

// -----------------------------
// Main
// -----------------------------

int main() {

    // Sample users
    vector<User> users = {
        {
            1,
            "alice",
            "alice123",
            10000.00,
            {}
        },
        {
            2,
            "bob",
            "bob123",
            5000.00,
            {}
        }
    };

    cout << "=====================================\n";
    cout << "       ONLINE BANKING SYSTEM\n";
    cout << "=====================================\n";

    int loggedInUser = login(users);

    if (loggedInUser == -1) {
        cout << "\nLogin failed. Exiting application.\n";
        return 0;
    }

    bankingMenu(users[loggedInUser], users);

    cout << "\nThank you for using Online Banking.\n";

    return 0;
}

// -----------------------------
// Login
// -----------------------------

int login(vector<User>& users) {

    string username;
    string password;

    cout << "\n========== LOGIN ==========\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < users.size(); i++) {

        if (users[i].username == username &&
            users[i].password == password) {

            cout << "\nLogin successful!\n";
            cout << "Welcome, " << users[i].username << "!\n";

            return i;
        }
    }

    cout << "\nInvalid username or password.\n";

    return -1;
}

// -----------------------------
// Banking Menu
// -----------------------------

void bankingMenu(User& currentUser, vector<User>& users) {

    int choice;

    do {

        cout << "\n=====================================\n";
        cout << "           BANKING MENU\n";
        cout << "=====================================\n";

        cout << "1. Check Balance\n";
        cout << "2. Transfer Funds\n";
        cout << "3. Manage Beneficiaries\n";
        cout << "4. Switch Accounts\n";
        cout << "5. Logout\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                checkBalance(currentUser);
                break;

            case 2:
                transferFunds(currentUser);
                break;

            case 3:
                manageBeneficiaries(currentUser);
                break;
            //Added switch accpount without auth - Broken Access Control
            case 4:
                int accid;

                cout<<"enter acc id to view: ";
                cin>>accid;

                if(accid<1 || accid>users.size()){
                    cout<<"Invalid account ID.\n";
                    break;
                }

                User& tarUser=users[accid-1];

                cout<<"\n=======ACCOUNT DETAILS=======";
                cout<<"Account holder: "<<tarUser.username<<"\n";
                cout<<"Balance: Rs. "<<fixed<<setprecision(2)<<tarUser.balance<<"\n";

                break;

            case 5:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 5);
}

// -----------------------------
// Check Balance
// -----------------------------

void checkBalance(const User& user) {

    cout << "\n========== BALANCE ==========\n";

    cout << "Account Holder: "
         << user.username << "\n";

    cout << fixed << setprecision(2);

    cout << "Current Balance: Rs. "
         << user.balance << "\n";
}

// -----------------------------
// Transfer Funds
// -----------------------------

void transferFunds(User& user) {

    string accountNumber;
    double amount;

    cout << "\n========== TRANSFER FUNDS ==========\n";

    if (user.beneficiaries.empty()) {

        cout << "No beneficiaries available.\n";
        cout << "Please add a beneficiary first.\n";

        return;
    }

    cout << "Enter beneficiary account number: ";
    cin >> accountNumber;

    bool beneficiaryFound = false;

    for (const auto& beneficiary : user.beneficiaries) {

        if (beneficiary.accountNumber == accountNumber) {
            beneficiaryFound = true;
            break;
        }
    }

    if (!beneficiaryFound) {

        cout << "Beneficiary not found.\n";

        return;
    }

    cout << "Enter amount: Rs. ";
    cin >> amount;

    //Negative numbers arent checked before transfers - Insufficient Input Validation
    // if (amount <= 0) {

    //     cout << "Invalid amount.\n";

    //     return;
    // }

    if (amount > user.balance) {

        cout << "Insufficient balance.\n";

        return;
    }

    user.balance -= amount;

    cout << "\nTransfer successful!\n";

    cout << "Transferred: Rs. "
         << fixed << setprecision(2)
         << amount << "\n";

    cout << "Remaining Balance: Rs. "
         << user.balance << "\n";
}

// -----------------------------
// Manage Beneficiaries
// -----------------------------

void manageBeneficiaries(User& user) {

    int choice;

    do {

        cout << "\n========== BENEFICIARIES ==========\n";

        cout << "1. Add Beneficiary\n";
        cout << "2. View Beneficiaries\n";
        cout << "3. Delete Beneficiary\n";
        cout << "4. Back\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addBeneficiary(user);
                break;

            case 2:
                viewBeneficiaries(user);
                break;

            case 3:
                deleteBeneficiary(user);
                break;

            case 4:
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}

// -----------------------------
// Add Beneficiary
// -----------------------------

void addBeneficiary(User& user) {

    Beneficiary beneficiary;

    cout << "\n========== ADD BENEFICIARY ==========\n";

    cout << "Beneficiary name: ";
    cin >> beneficiary.name;

    cout << "Account number: ";
    cin >> beneficiary.accountNumber;

    user.beneficiaries.push_back(beneficiary);

    cout << "\nBeneficiary added successfully.\n";
}

// -----------------------------
// View Beneficiaries
// -----------------------------

void viewBeneficiaries(const User& user) {

    cout << "\n========== BENEFICIARY LIST ==========\n";

    if (user.beneficiaries.empty()) {

        cout << "No beneficiaries found.\n";

        return;
    }

    for (int i = 0; i < user.beneficiaries.size(); i++) {

        cout << i + 1 << ". "
             << user.beneficiaries[i].name
             << " - "
             << user.beneficiaries[i].accountNumber
             << "\n";
    }
}

// -----------------------------
// Delete Beneficiary
// -----------------------------

void deleteBeneficiary(User& user) {

    if (user.beneficiaries.empty()) {

        cout << "\nNo beneficiaries to delete.\n";

        return;
    }

    viewBeneficiaries(user);

    int choice;

    cout << "\nEnter beneficiary number to delete: ";
    cin >> choice;

    if (choice < 1 || choice > user.beneficiaries.size()) {

        cout << "Invalid beneficiary number.\n";

        return;
    }

    user.beneficiaries.erase(
        user.beneficiaries.begin() + (choice - 1)
    );

    cout << "Beneficiary deleted successfully.\n";
}


//vulnerabilities

