#ifndef USERPREFERENCE_H // Header guard para hindi maulit ang definition ng UserPreference.
#define USERPREFERENCE_H // Define guard.

#include <string> // Needed because weather and budget are text.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P. (Smart Recommendation Study Support)
 *
 * PURPOSE:
 * UserPreference is a small data container. Para siyang maliit na form kung saan nilalagay
 * ang sagot ng user: weather, budget level, and available money.
 *
 * WHY STRUCT?
 * Gumamit tayo ng struct dahil simple grouped data lang ito. Wala siyang complicated behavior.
 * Mas malinis ito kaysa ipasa ang weather, budget, money separately sa maraming functions.
 */
struct UserPreference { // struct groups related variables into one package.
    string weather; // User's current weather choice, e.g., rainy.
    string budgetLevel; // User's chosen budget level, e.g., low.
    double availableMoney; // User's actual available money, e.g., 100.00.
}; // End struct. Semicolon is required.

#endif // End header guard.
