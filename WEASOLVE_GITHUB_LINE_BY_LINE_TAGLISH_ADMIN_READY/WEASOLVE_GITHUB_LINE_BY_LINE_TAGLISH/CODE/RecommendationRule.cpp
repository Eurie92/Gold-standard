#include "RecommendationRule.h" // Gives us the class declarations from RecommendationRule.h.
#include "InputValidator.h" // Needed so we can use toLowerCase for safer text comparison.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P.
 *
 * FILE ROLE:
 * This file contains the actual logic of each recommendation rule.
 * Bawat rule ay parang separate judge. Each judge gives points and reason.
 * This is why our system is stronger than simple filtering: may ranked explanation.
 */

int WeatherMatchRule::score(const FoodItem& food, const UserPreference& preference) const { // Weather rule scoring function.
    return food.getWeather() == preference.weather ? 40 : 0; // If weather matches, give 40 points; otherwise 0. Ternary operator ito: condition ? value_if_true : value_if_false.
} // End weather score.

string WeatherMatchRule::explain(const FoodItem& food, const UserPreference& preference) const { // Weather rule explanation.
    if (food.getWeather() == preference.weather) { // Only explain if the rule gave points.
        return "- Weather match: This food is tagged for the user's current weather. (+40)\n"; // Explanation shown in output.
    } // End if.
    return ""; // Empty string means no explanation because no points were given.
} // End weather explanation.

int BudgetMatchRule::score(const FoodItem& food, const UserPreference& preference) const { // Budget rule scoring function.
    return food.getBudgetLevel() == preference.budgetLevel ? 25 : 0; // If budget category matches, give 25 points.
} // End budget score.

string BudgetMatchRule::explain(const FoodItem& food, const UserPreference& preference) const { // Budget rule explanation.
    if (food.getBudgetLevel() == preference.budgetLevel) { // Explain only if matching.
        return "- Budget match: This food matches the user's selected budget level. (+25)\n"; // Explanation text.
    } // End if.
    return ""; // No points, no explanation.
} // End budget explanation.

int AffordabilityRule::score(const FoodItem& food, const UserPreference& preference) const { // Affordability rule scoring function.
    return food.getPrice() <= preference.availableMoney ? 25 : 0; // If price fits user's money, give 25 points.
} // End affordability score.

string AffordabilityRule::explain(const FoodItem& food, const UserPreference& preference) const { // Affordability rule explanation.
    if (food.getPrice() <= preference.availableMoney) { // Check if user can afford the food.
        return "- Affordable: The price is within the user's available money. (+25)\n"; // Explanation shown in output.
    } // End if.
    return ""; // No points if not affordable.
} // End affordability explanation.

int HealthSuitabilityRule::score(const FoodItem& food, const UserPreference& preference) const { // Health/well-being rule scoring.
    string note = InputValidator::toLowerCase(food.getHealthNote()); // Convert health note to lowercase so matching is easier and case-insensitive.
    if (preference.weather == "rainy" && (note.find("warm") != string::npos || note.find("soup") != string::npos)) { // Rainy days usually fit warm/soup comfort foods.
        return 10; // Give full health suitability points.
    } // End rainy check.
    if (preference.weather == "cold" && (note.find("warm") != string::npos || note.find("hot") != string::npos)) { // Cold weather fits warm/hot foods.
        return 10; // Full points.
    } // End cold check.
    if (preference.weather == "sunny" && (note.find("refreshing") != string::npos || note.find("light") != string::npos || note.find("cold") != string::npos)) { // Sunny weather fits refreshing/light/cold foods.
        return 10; // Full points.
    } // End sunny check.
    return 5; // Small points because every record still has a health note, but not perfect keyword match.
} // End health score.

string HealthSuitabilityRule::explain(const FoodItem& food, const UserPreference& preference) const { // Health explanation function.
    string note = InputValidator::toLowerCase(food.getHealthNote()); // Lowercase again for the same reason as scoring.
    if (preference.weather == "rainy" && (note.find("warm") != string::npos || note.find("soup") != string::npos)) { // Rainy perfect match.
        return "- Health suitability: Warm/soup note fits rainy weather comfort. (+10)\n"; // Explanation.
    } // End rainy explanation.
    if (preference.weather == "cold" && (note.find("warm") != string::npos || note.find("hot") != string::npos)) { // Cold perfect match.
        return "- Health suitability: Warm/hot note fits cold weather. (+10)\n"; // Explanation.
    } // End cold explanation.
    if (preference.weather == "sunny" && (note.find("refreshing") != string::npos || note.find("light") != string::npos || note.find("cold") != string::npos)) { // Sunny perfect match.
        return "- Health suitability: Refreshing/light note fits sunny weather. (+10)\n"; // Explanation.
    } // End sunny explanation.
    return "- Health note available: The record includes a basic wellness explanation. (+5)\n"; // Default explanation for partial points.
} // End health explanation.
