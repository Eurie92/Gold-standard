#include "InputValidator.h" // Kinukuha natin ang declarations ng InputValidator functions.
#include <iostream> // Needed for cout and cin.
#include <limits> // Needed for numeric_limits, used in cin.ignore() to clean bad input.
#include <algorithm> // Needed for transform() used in toLowerCase().
#include <cctype> // Needed for tolower().
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Paulino, Eurie V.
 *
 * BIG PICTURE:
 * This file prevents user-input bugs. Kapag wala ito, madaling mag-crash or mag-infinite loop
 * ang program kapag mali ang input. Example: menu asks for int, user types "hello".
 * cin will fail. Kaya kailangan i-clear ang error and itapon ang bad text.
 */

int InputValidator::getIntInRange(const string& prompt, int min, int max) { // Function that returns a safe integer within allowed range.
    int value; // Temporary storage for user number.
    while (true) { // Infinite validation loop. Lalabas lang kapag valid ang input.
        cout << prompt; // Show instruction/question to user.
        if (cin >> value && value >= min && value <= max) { // Check 1: number ba? Check 2: nasa allowed range ba?
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove leftover enter/newline para hindi makaapekto sa getline later.
            return value; // Valid na, ibalik ang value sa caller.
        } // End valid check.
        cout << "Invalid input. Please enter a number from " << min << " to " << max << ".\n"; // Friendly error message.
        cin.clear(); // Reset cin error state kapag nag-type ng letters instead of number.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Throw away bad input from keyboard buffer.
    } // Loop repeats until user gives valid input.
} // End getIntInRange.

double InputValidator::getPositiveDouble(const string& prompt) { // Function that returns a safe positive decimal/money value.
    double value; // Temporary storage for money/price.
    while (true) { // Repeat until valid.
        cout << prompt; // Ask user.
        if (cin >> value && value >= 0.0) { // Must be numeric and not negative.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean leftover newline.
            return value; // Return safe value.
        } // End valid check.
        cout << "Invalid input. Please enter a positive number.\n"; // Explain mistake.
        cin.clear(); // Fix failed cin state.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove bad input.
    } // Repeat until safe.
} // End getPositiveDouble.

string InputValidator::getNonEmptyLine(const string& prompt) { // Gets a line of text that cannot be empty.
    string text; // Storage for user's text.
    while (true) { // Repeat until non-empty.
        cout << prompt; // Ask user.
        getline(cin, text); // Read full line, including spaces. Better than cin >> for names like "Chicken Sopas".
        if (!text.empty()) { // If the user typed something, accept it.
            return text; // Return valid text.
        } // End check.
        cout << "Input cannot be empty. Please try again.\n"; // Error message for blank input.
    } // Repeat until valid.
} // End getNonEmptyLine.

string InputValidator::getWeatherInput() { // Gets weather and only accepts official categories.
    while (true) { // Repeat until sunny/rainy/cold.
        string weather = toLowerCase(getNonEmptyLine("Enter weather (sunny/rainy/cold): ")); // Ask and normalize text to lowercase.
        if (weather == "sunny" || weather == "rainy" || weather == "cold") { // Exact category check.
            return weather; // Return valid weather.
        } // End valid check.
        cout << "Invalid weather. Allowed values: sunny, rainy, cold.\n"; // Tell user what is allowed.
    } // Repeat until correct.
} // End getWeatherInput.

string InputValidator::getBudgetInput() { // Gets budget and only accepts official categories.
    while (true) { // Repeat until low/mid/high.
        string budget = toLowerCase(getNonEmptyLine("Enter budget level (low/mid/high): ")); // Ask and normalize.
        if (budget == "low" || budget == "mid" || budget == "high") { // Validate category.
            return budget; // Return valid budget.
        } // End valid check.
        cout << "Invalid budget level. Allowed values: low, mid, high.\n"; // Explain allowed values.
    } // Repeat until valid.
} // End getBudgetInput.

string InputValidator::getYesNoInput(const string& prompt) { // Gets yes/no answer safely.
    while (true) { // Repeat until yes or no.
        string answer = toLowerCase(getNonEmptyLine(prompt)); // Ask and normalize.
        if (answer == "yes" || answer == "no") { // Accept only yes/no.
            return answer; // Return valid answer.
        } // End valid check.
        cout << "Please answer only yes or no.\n"; // Explain allowed answers.
    } // Repeat until valid.
} // End getYesNoInput.

string InputValidator::toLowerCase(string text) { // Converts any string to lowercase.
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { // Visit every character and replace it with lowercase version.
        return static_cast<char>(tolower(c)); // tolower returns lowercase version; static_cast keeps type clean.
    }); // End transform.
    return text; // Return normalized text.
} // End toLowerCase.
