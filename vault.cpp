#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include "picosha2.h"

using namespace std;



string hashPassword(const string& password) { 
    return picosha2::hash256_hex_string(password);
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void setupPassword(const string& filename) {
    string password1, password2;

    cout << "\033[36m🔐 First-time setup: Create a master password\033[0m\n";
    cout << "Enter new password: ";
    getline(cin, password1);
    cout << "Confirm password :";
    getline(cin, password2);
    if (password1 != password2 || password1.empty()) {
        cout << "\033[31m❌ Passwords do not match or are empty. Try again.\033[0m\n";
        exit(1);
    }

    string hashed = hashPassword(password1);
    ofstream out(filename);
    out << hashed;
    out.close();

    cout << "\033[32m✅ Password saved securely.\033[0m\n";
}

bool login(const string& filename) {
    if (!fileExists(filename)) {
        setupPassword(filename);
    }

    string storedHash;
    ifstream in(filename);
    getline(in, storedHash);
    in.close();


    const int maxAttempts = 3;
    string input;

    cout << "\033[36m🔐 Welcome to VaultCPP - Terminal Password Manager\033[0m\n";

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        cout << "\033[33mEnter master password (" << attempt << "/" << maxAttempts << "): \033[0m";
        getline(cin, input);
        
        if (hashPassword(input) == storedHash) {
            cout << "\033[32m✅ Access granted.\033[0m\n";
            return true;
        } else {
            cout << "\033[31m❌ Incorrect password.\033[0m\n";
        }
    }

    cout << "\033[31m🚫 Too many failed attempts. Exiting...\033[0m\n";
    return false;
}

int main() {
    const string passwordFile = "vault.pass";

    if (!login(passwordFile)) {
        return 1;
    }
}