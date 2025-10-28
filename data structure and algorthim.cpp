#include <iostream>
#include <string>

using namespace std;

long long globalAccountNumberCounter = 1000;

struct UserAccount {
    string firstName;
    string lastName;
    string phoneNumber;
    string password;
    string accountNumber;
    double balance;
    UserAccount* next;
};

UserAccount* head = nullptr;

// Function to validate phone number (exactly 10 digits)
bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 10) return false;
    for (size_t i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    return true;
}

// Add user at the start of the list
void addUserAtStart(const string& firstName, const string& lastName, const string& phoneNumber,
                    const string& password, const string& accountNumber, double balance) {
    UserAccount* newUser = new UserAccount{firstName, lastName, phoneNumber, password, accountNumber, balance, nullptr};
    newUser->next = head;
    head = newUser;
    cout << "User added at the start successfully.\n";
}

// Add user at the end of the list
void addUserAtEnd(const string& firstName, const string& lastName, const string& phoneNumber,
                  const string& password, const string& accountNumber, double balance) {
    UserAccount* newUser = new UserAccount{firstName, lastName, phoneNumber, password, accountNumber, balance, nullptr};
    if (!head) {
        head = newUser;
    } else {
        UserAccount* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newUser;
    }
    cout << "User added at the end successfully.\n";
}

// Delete user at the start of the list
void deleteUserAtStart() {
    if (!head) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    UserAccount* temp = head;
    head = head->next;
    delete temp;
    cout << "User deleted at the start.\n";
}

// Delete user at the end of the list
void deleteUserAtEnd() {
    if (!head) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        cout << "User deleted at the end.\n";
        return;
    }
    UserAccount* temp = head;
    UserAccount* prev = nullptr;
    while (temp->next) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = nullptr;
    delete temp;
    cout << "User deleted at the end.\n";
}

// Delete all users from the list
void deleteAllUsers() {
    UserAccount* curr = head;
    while (curr) {
        UserAccount* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    cout << "All users deleted.\n";
}

// Helper function to compare two user accounts by name
bool compareUsersByName(UserAccount* a, UserAccount* b) {
    string nameA = a->firstName + " " + a->lastName;
    string nameB = b->firstName + " " + b->lastName;
    return nameA < nameB;
}

// Sort users by name (first name + last name)
void sortUsersByName() {
    if (!head || !head->next) {
        cout << "Not enough users to sort.\n";
        return;
    }

    // Count the number of users
    int count = 0;
    UserAccount* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    // Create an array of user pointers
    UserAccount** users = new UserAccount*[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        users[i] = temp;
        temp = temp->next;
    }

    // Bubble sort (since we can't use algorithm header)
    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (!compareUsersByName(users[j], users[j+1])) {
                UserAccount* temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }

    // Rebuild the linked list
    head = users[0];
    for (int i = 0; i < count-1; i++) {
        users[i]->next = users[i+1];
    }
    users[count-1]->next = nullptr;

    delete[] users;
    cout << "Users sorted by name successfully.\n";
}

// Display all users in the list
void displayAllUsers() {
    if (!head) {
        cout << "No users to display.\n";
        return;
    }
    UserAccount* curr = head;
    int i = 1;
    while (curr) {
        cout << "User " << i << ":\n";
        cout << "  First Name: " << curr->firstName << "\n";
        cout << "  Last Name: " << curr->lastName << "\n";
        cout << "  Phone Number: " << curr->phoneNumber << "\n";
        cout << "  Password: " << curr->password << "\n";
        cout << "  Account Number: " << curr->accountNumber << "\n";
        cout << "  Balance: $" << curr->balance << "\n";
        cout << "-------------------------\n";
        curr = curr->next;
        i++;
    }
}

// Welcome screen
void welcomePage() {
    cout << "*****************************************\n";
    cout << "*                                       *\n";
    cout << "*    Welcome to Bank Account Management *\n";
    cout << "*                System                 *\n";
    cout << "*                                       *\n";
    cout << "*****************************************\n\n";
}

// Display main menu options
void displayMainMenu() {
    cout << "--- Main Menu ---\n";
    cout << "1. Admin Login\n";
    cout << "2. User Login\n";
    cout << "3. User Registration\n";
    cout << "4. Exit\n";
}

// Generate unique account number string
string generateUniqueAccountNumber() {
    return "ACC" + to_string(globalAccountNumberCounter++);
}

// Forward declaration
void adminMenu();

// Admin login
void adminLogin() {
    string username, password;
    cout << "\n--- Admin Login ---\n";
    cout << "Enter Admin Username: "; getline(cin, username);
    cout << "Enter Admin Password (4 characters): "; getline(cin, password);

    if (username == "Asrat" && password == "1234") {
        adminMenu();
    } else {
        cout << "Invalid Admin credentials.\n";
    }
}

// Deposit money into user account
void userDeposit(UserAccount* user) {
    double amt;
    cout << "\n--- Deposit ---\nAmount: $"; cin >> amt; cin.ignore();
    if (amt > 0) {
        user->balance += amt;
        cout << "Deposited. New Balance: $" << user->balance << endl;
    } else cout << "Invalid amount.\n";
}

// Withdraw money from user account
void userWithdrawal(UserAccount* user) {
    double amt;
    cout << "\n--- Withdraw ---\nAmount: $"; cin >> amt; cin.ignore();
    if (amt <= 0) cout << "Invalid amount.\n";
    else if (user->balance >= amt) {
        user->balance -= amt;
        cout << "Withdrew. New Balance: $" << user->balance << endl;
    } else cout << "Insufficient balance.\n";
}

// Display details of logged-in user
void displayCurrentUserAccount(UserAccount* user) {
    cout << "\n--- Your Account ---\n";
    cout << "First Name: " << user->firstName << endl;
    cout << "Last Name: " << user->lastName << endl;
    cout << "Phone Number: " << user->phoneNumber << endl;
    cout << "Password: " << user->password << endl;
    cout << "Account Number: " << user->accountNumber << endl;
    cout << "Balance: $" << user->balance << endl;
}

// User login flow
void userLogin() {
    string username, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter First Name: "; getline(cin, username);
    cout << "Enter Password (4 characters): "; getline(cin, password);

    for (UserAccount* user = head; user; user = user->next) {
        if (user->firstName == username && user->password == password) {
            cout << "User login successful! Welcome, " << user->firstName << "!\n";
            int choice;
            do {
                cout << "\n--- User Menu (" << user->firstName << ") ---\n";
                cout << "1. Deposit Funds\n2. Withdraw Funds\n3. View Account Details\n4. Logout\nEnter your choice: ";
                cin >> choice; cin.ignore();
                switch (choice) {
                    case 1: userDeposit(user); break;
                    case 2: userWithdrawal(user); break;
                    case 3: displayCurrentUserAccount(user); break;
                    case 4: cout << "Logging out from your account.\n"; break;
                    default: cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 4);
            return;
        }
    }
    cout << "Invalid user credentials or account not found.\n";
}

// User registration flow (adds user at the end)
void userRegistration() {
    string firstName, lastName, phoneNumber, password;
    double balance;
    cout << "\n--- User Registration ---\n";
    cout << "Enter First Name: "; getline(cin, firstName);
    cout << "Enter Last Name: "; getline(cin, lastName);

    do {
        cout << "Enter Phone Number (10 digits): "; getline(cin, phoneNumber);
        if (!isValidPhoneNumber(phoneNumber)) {
            cout << "Invalid phone number. Please enter exactly 10 digits.\n";
        }
    } while (!isValidPhoneNumber(phoneNumber));

    do {
        cout << "Enter Password (exactly 4 characters): "; getline(cin, password);
    } while (password.length() != 4);

    cout << "Enter Initial Deposit Balance: $"; cin >> balance; cin.ignore();

    addUserAtEnd(firstName, lastName, phoneNumber, password, generateUniqueAccountNumber(), balance);
    cout << "User account registered successfully!\n";
}

// Admin adds a user with choice to add at start or end
void adminAddUser() {
    string firstName, lastName, phoneNumber, password;
    double balance;
    int addChoice;
    cout << "\n--- Admin Add User ---\n";
    cout << "Enter First Name: "; getline(cin, firstName);
    cout << "Enter Last Name: "; getline(cin, lastName);

    do {
        cout << "Enter Phone Number (10 digits): "; getline(cin, phoneNumber);
        if (!isValidPhoneNumber(phoneNumber)) {
            cout << "Invalid phone number. Please enter exactly 10 digits.\n";
        }
    } while (!isValidPhoneNumber(phoneNumber));

    do {
        cout << "Enter Password (exactly 4 characters): "; getline(cin, password);
    } while (password.length() != 4);

    cout << "Enter Initial Deposit Balance: $"; cin >> balance; cin.ignore();

    cout << "Add user at:\n1. Start\n2. End\nChoose: "; cin >> addChoice; cin.ignore();

    if (addChoice == 1)
        addUserAtStart(firstName, lastName, phoneNumber, password, generateUniqueAccountNumber(), balance);
    else if (addChoice == 2)
        addUserAtEnd(firstName, lastName, phoneNumber, password, generateUniqueAccountNumber(), balance);
    else
        cout << "Invalid choice. User not added.\n";
}

// Admin menu options
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add User (start or end)\n";
        cout << "2. Delete User at Start\n";
        cout << "3. Delete User at End\n";
        cout << "4. Delete All Users\n";
        cout << "5. Display All Users\n";
        cout << "6. Sort Users by Name\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice; cin.ignore();

        switch (choice) {
            case 1: adminAddUser(); break;
            case 2: deleteUserAtStart(); break;
            case 3: deleteUserAtEnd(); break;
            case 4: deleteAllUsers(); break;
            case 5: displayAllUsers(); break;
            case 6: sortUsersByName(); break;
            case 7: cout << "Logging out from Admin account.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}

// Main function driving the program
int main() {
    welcomePage();
    int choice;
    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice; cin.ignore();

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: userLogin(); break;
            case 3: userRegistration(); break;
            case 4: cout << "Exiting Bank Account Management System. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (choice != 4);

    // Clean up all users on exit
    deleteAllUsers();

    return 0;
}

