#include <iostream>
#include <string>
#include "picosha2.h"

using namespace std;

bool login() {
    const string correctPassword = "Smthn";
    const int maxAttempts = 3;
    string input;

    cout << "\033[36m🔐 Welcome to VaultCPP - Terminal Password Manager\033[0m\n";

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        cout << "\033[33mEnter master password (" << attempt << "/" << maxAttempts << "): \033[0m";
        getline(cin, input);
        
        if (input == correctPassword) {
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
    if (!login()) {
        return 1;
    }
}