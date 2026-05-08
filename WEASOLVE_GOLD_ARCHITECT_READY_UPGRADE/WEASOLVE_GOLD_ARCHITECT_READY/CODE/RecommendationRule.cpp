#include "RecommendationRule.h"
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

static string lowerCopy(string text) {
    for (char& ch : text) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return text;
}

int WeatherMatchRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getWeather() == preference.weather ? 40 : 0;
}

string WeatherMatchRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getWeather() == preference.weather) {
        return "- Weather Match (+40): Tugma ang food sa current weather ng user.\n";
    }
    return "";
}

int BudgetMatchRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getBudgetLevel() == preference.budgetLevel ? 25 : 0;
}

string BudgetMatchRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getBudgetLevel() == preference.budgetLevel) {
        return "- Budget Match (+25): Tugma ang food sa selected budget level.\n";
    }
    return "";
}

int AffordabilityRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getPrice() <= preference.availableMoney ? 25 : 0;
}

string AffordabilityRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getPrice() <= preference.availableMoney) {
        ostringstream out;
        out << "- Affordable (+25): Price is PHP " << food.getPrice()
            << ", which fits the user's available money of PHP " << preference.availableMoney << ".\n";
        return out.str();
    }
    return "";
}

int HealthSuitabilityRule::score(const FoodItem& food, const UserPreference& preference) const {
    string note = lowerCopy(food.getHealthNote());
    if (preference.weather == "sunny" &&
        (note.find("refresh") != string::npos || note.find("cold") != string::npos || note.find("light") != string::npos)) {
        return 10;
    }
    if ((preference.weather == "rainy" || preference.weather == "cold") &&
        (note.find("warm") != string::npos || note.find("soup") != string::npos || note.find("comfort") != string::npos)) {
        return 10;
    }
    return 5;
}

string HealthSuitabilityRule::explain(const FoodItem& food, const UserPreference& preference) const {
    int points = score(food, preference);
    if (points == 10) {
        return "- Health/Weather Suitability (+10): Health note strongly supports the weather situation.\n";
    }
    return "- Health/Weather Suitability (+5): Food has a health note, but it is a general match only.\n";
}
