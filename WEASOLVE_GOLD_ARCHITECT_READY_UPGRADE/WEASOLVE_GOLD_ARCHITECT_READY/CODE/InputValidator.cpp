#include "InputValidator.h"
#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

string InputValidator::toLowerCase(string text) {
    for (char& ch : text) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return text;
}

int InputValidator::getIntInRange(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a whole number from " << min << " to " << max << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double InputValidator::getPositiveDouble(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter zero or a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string InputValidator::getNonEmptyLine(string prompt) {
    string text;
    while (true) {
        cout << prompt;
        getline(cin, text);
        if (!text.empty()) {
            return text;
        }
        cout << "Input cannot be empty. Please type a value.\n";
    }
}

string InputValidator::getWeatherInput() {
    while (true) {
        string weather = toLowerCase(getNonEmptyLine("Enter weather (sunny/rainy/cold): "));
        if (weather == "sunny" || weather == "rainy" || weather == "cold") {
            return weather;
        }
        cout << "Invalid weather. Allowed weather only: sunny, rainy, cold.\n";
    }
}

string InputValidator::getBudgetInput() {
    while (true) {
        string budget = toLowerCase(getNonEmptyLine("Enter budget level (low/mid/high): "));
        if (budget == "low" || budget == "mid" || budget == "high") {
            return budget;
        }
        cout << "Invalid budget. Allowed budget only: low, mid, high.\n";
    }
}

string InputValidator::getYesNoInput(string prompt) {
    while (true) {
        string answer = toLowerCase(getNonEmptyLine(prompt));
        if (answer == "yes" || answer == "y") return "yes";
        if (answer == "no" || answer == "n") return "no";
        cout << "Please answer yes or no only.\n";
    }
}
