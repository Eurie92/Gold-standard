#include "FoodManager.h"
#include "InputValidator.h"
#include "RecommendationEngine.h"
#include "UserPreference.h"
#include "RecommendationResult.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

/*
 * FoodManager.cpp
 *
 * Taglish big picture:
 * Ito ang pinakamalaking worker file ng WEASOLVE. Dito nangyayari ang database
 * loading, saving, CRUD, favorites, summary report, at connection sa bagong
 * RecommendationEngine. Main.cpp only controls the menu; FoodManager does the work.
 */

static string trim(const string& text) {
    size_t start = 0;
    while (start < text.size() && isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }
    size_t end = text.size();
    while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) {
        end--;
    }
    return text.substr(start, end - start);
}

static bool isValidWeather(const string& weather) {
    return weather == "sunny" || weather == "rainy" || weather == "cold";
}

static bool isValidBudget(const string& budget) {
    return budget == "low" || budget == "mid" || budget == "high";
}

int FoodManager::findIndexById(int id) const {
    for (int i = 0; i < static_cast<int>(foods.size()); i++) {
        if (foods[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

int FoodManager::generateNextId() const {
    int highestId = 0;
    for (const FoodItem& food : foods) {
        if (food.getId() > highestId) {
            highestId = food.getId();
        }
    }
    return highestId + 1;
}

const vector<FoodItem>& FoodManager::getFoods() const {
    return foods;
}

bool FoodManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open database file: " << filename << "\n";
        return false;
    }

    foods.clear();
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (trim(line).empty()) {
            continue;
        }

        stringstream ss(line);
        string idText, name, weather, budgetLevel, priceText, restaurant, healthNote;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, weather, '|');
        getline(ss, budgetLevel, '|');
        getline(ss, priceText, '|');
        getline(ss, restaurant, '|');
        getline(ss, healthNote);

        idText = trim(idText);
        name = trim(name);
        weather = InputValidator::toLowerCase(trim(weather));
        budgetLevel = InputValidator::toLowerCase(trim(budgetLevel));
        priceText = trim(priceText);
        restaurant = trim(restaurant);
        healthNote = trim(healthNote);

        if (idText.empty() || name.empty() || weather.empty() || budgetLevel.empty() ||
            priceText.empty() || restaurant.empty() || healthNote.empty()) {
            cout << "Warning: Skipping incomplete record at line " << lineNumber << ".\n";
            continue;
        }

        if (!isValidWeather(weather) || !isValidBudget(budgetLevel)) {
            cout << "Warning: Skipping invalid category at line " << lineNumber << ".\n";
            continue;
        }

        try {
            int id = stoi(idText);
            double price = stod(priceText);
            if (id <= 0 || price < 0.0) {
                cout << "Warning: Skipping invalid ID/price at line " << lineNumber << ".\n";
                continue;
            }
            foods.push_back(FoodItem(id, name, weather, budgetLevel, price, restaurant, healthNote));
        } catch (...) {
            cout << "Warning: Skipping invalid numeric field at line " << lineNumber << ".\n";
        }
    }

    file.close();
    cout << foods.size() << " food record/s loaded successfully.\n";
    return true;
}

bool FoodManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open database file for saving: " << filename << "\n";
        return false;
    }

    for (const FoodItem& food : foods) {
        file << food.toFileString() << "\n";
    }

    file.close();
    return true;
}

void FoodManager::viewAllFoods() const {
    if (foods.empty()) {
        cout << "\nNo food records found.\n";
        return;
    }

    cout << "\n========== ALL FOOD RECORDS ==========\n";
    for (const FoodItem& food : foods) {
        food.display();
    }
    cout << "Total records: " << foods.size() << "\n";
}

void FoodManager::searchFood() const {
    if (foods.empty()) {
        cout << "\nNo food records available to search.\n";
        return;
    }

    cout << "\nSearch Food Record\n";
    cout << "[1] Search by ID\n";
    cout << "[2] Search by Name\n";
    int choice = InputValidator::getIntInRange("Enter choice: ", 1, 2);

    if (choice == 1) {
        int id = InputValidator::getIntInRange("Enter food ID: ", 1, 1000000);
        int index = findIndexById(id);
        if (index == -1) {
            cout << "Food record with ID " << id << " was not found.\n";
        } else {
            foods[index].display();
        }
    } else {
        string keyword = InputValidator::toLowerCase(InputValidator::getNonEmptyLine("Enter food keyword: "));
        bool found = false;
        for (const FoodItem& food : foods) {
            if (InputValidator::toLowerCase(food.getName()).find(keyword) != string::npos) {
                food.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No food record matched the keyword.\n";
        }
    }
}

void FoodManager::addFood() {
    cout << "\n========== ADD NEW FOOD RECORD ==========\n";
    int newId = generateNextId();
    string name = InputValidator::getNonEmptyLine("Enter food name: ");
    string weather = InputValidator::getWeatherInput();
    string budgetLevel = InputValidator::getBudgetInput();
    double price = InputValidator::getPositiveDouble("Enter estimated price: PHP ");
    string restaurant = InputValidator::getNonEmptyLine("Enter restaurant/source: ");
    string healthNote = InputValidator::getNonEmptyLine("Enter health note: ");

    foods.push_back(FoodItem(newId, name, weather, budgetLevel, price, restaurant, healthNote));
    cout << "Food record added successfully with ID " << newId << ".\n";
}

void FoodManager::updateFood() {
    if (foods.empty()) {
        cout << "\nNo food records available to update.\n";
        return;
    }

    cout << "\n========== UPDATE FOOD RECORD ==========\n";
    int id = InputValidator::getIntInRange("Enter food ID to update: ", 1, 1000000);
    int index = findIndexById(id);

    if (index == -1) {
        cout << "Food record with ID " << id << " was not found.\n";
        return;
    }

    foods[index].display();
    cout << "What do you want to update?\n";
    cout << "[1] Food Name\n[2] Weather\n[3] Budget Level\n[4] Price\n[5] Restaurant\n[6] Health Note\n[7] Cancel\n";
    int choice = InputValidator::getIntInRange("Enter choice: ", 1, 7);

    switch (choice) {
        case 1: foods[index].setName(InputValidator::getNonEmptyLine("Enter new food name: ")); break;
        case 2: foods[index].setWeather(InputValidator::getWeatherInput()); break;
        case 3: foods[index].setBudgetLevel(InputValidator::getBudgetInput()); break;
        case 4: foods[index].setPrice(InputValidator::getPositiveDouble("Enter new price: PHP ")); break;
        case 5: foods[index].setRestaurant(InputValidator::getNonEmptyLine("Enter new restaurant/source: ")); break;
        case 6: foods[index].setHealthNote(InputValidator::getNonEmptyLine("Enter new health note: ")); break;
        case 7: cout << "Update cancelled.\n"; return;
    }

    cout << "Food record updated successfully.\n";
}

void FoodManager::deleteFood() {
    if (foods.empty()) {
        cout << "\nNo food records available to delete.\n";
        return;
    }

    cout << "\n========== DELETE FOOD RECORD ==========\n";
    int id = InputValidator::getIntInRange("Enter food ID to delete: ", 1, 1000000);
    int index = findIndexById(id);

    if (index == -1) {
        cout << "Food record with ID " << id << " was not found.\n";
        return;
    }

    foods[index].display();
    string confirm = InputValidator::getYesNoInput("Are you sure you want to delete this record? (yes/no): ");
    if (confirm == "yes") {
        foods.erase(foods.begin() + index);
        favorites.erase(
            remove_if(favorites.begin(), favorites.end(), [id](const FoodItem& item) { return item.getId() == id; }),
            favorites.end()
        );
        cout << "Food record deleted successfully.\n";
    } else {
        cout << "Delete cancelled.\n";
    }
}

void FoodManager::recommendByWeather(const string& weather) const {
    if (foods.empty()) {
        cout << "\nNo food records available for recommendation.\n";
        return;
    }

    string selectedWeather = InputValidator::toLowerCase(weather);
    bool found = false;
    int count = 0;

    cout << "\n========== SIMPLE WEATHER RECOMMENDATIONS FOR " << selectedWeather << " ==========\n";
    for (const FoodItem& food : foods) {
        if (food.getWeather() == selectedWeather) {
            food.display();
            found = true;
            count++;
        }
    }

    if (!found) {
        cout << "No recommendations found for this weather.\n";
    } else {
        cout << "Total simple recommendation/s found: " << count << "\n";
        cout << "Tip: Use Option 5 for Gold Standard smart ranking with score and explanations.\n";
    }
}

void FoodManager::recommendSmartRanking(const string& weather) const {
    if (foods.empty()) {
        cout << "\nNo food records available for smart recommendation.\n";
        return;
    }

    UserPreference preference;
    preference.weather = InputValidator::toLowerCase(weather);
    preference.budgetLevel = InputValidator::getBudgetInput();
    preference.availableMoney = InputValidator::getPositiveDouble("Enter your available money: PHP ");

    RecommendationEngine engine;
    vector<RecommendationResult> results = engine.recommend(foods, preference);

    cout << "\n========== WEASOLVE SMART RANKED RECOMMENDATIONS ==========\n";
    cout << "Weather: " << preference.weather << "\n";
    cout << "Budget Level: " << preference.budgetLevel << "\n";
    cout << "Available Money: PHP " << fixed << setprecision(2) << preference.availableMoney << "\n";
    cout << "Scoring Formula: Weather 40 + Budget 25 + Affordability 25 + Health Suitability 10 = 100\n";

    if (results.empty()) {
        cout << "No strong recommendation found. Try increasing your money or changing budget level.\n";
        return;
    }

    int rank = 1;
    for (const RecommendationResult& result : results) {
        cout << "\nRank #" << rank << " | Score: " << result.score << "/100\n";
        result.food.display();
        cout << "Why recommended:\n" << result.explanation;
        rank++;
    }
}

void FoodManager::recommendByWeatherAndBudget(const string& weather) const {
    recommendSmartRanking(weather);
}

void FoodManager::saveFavoriteFood(const string& weather) {
    if (foods.empty()) {
        cout << "\nNo food records available to save as favorite.\n";
        return;
    }

    string selectedWeather = InputValidator::toLowerCase(weather);
    bool hasMatch = false;

    cout << "\n========== FOODS AVAILABLE FOR FAVORITES ==========\n";
    for (const FoodItem& food : foods) {
        if (food.getWeather() == selectedWeather) {
            cout << "ID " << food.getId() << " - " << food.getName()
                 << " (PHP " << fixed << setprecision(2) << food.getPrice() << ")\n";
            hasMatch = true;
        }
    }

    if (!hasMatch) {
        cout << "No foods are available for the current weather.\n";
        return;
    }

    int id = InputValidator::getIntInRange("Enter the ID of the food to save as favorite: ", 1, 1000000);
    int index = findIndexById(id);

    if (index == -1 || foods[index].getWeather() != selectedWeather) {
        cout << "Invalid ID. Please choose a food listed for the current weather.\n";
        return;
    }

    for (const FoodItem& favorite : favorites) {
        if (favorite.getId() == id) {
            cout << "This food is already in your favorites.\n";
            return;
        }
    }

    favorites.push_back(foods[index]);
    cout << foods[index].getName() << " was saved to favorites.\n";
}

void FoodManager::viewFavorites() const {
    if (favorites.empty()) {
        cout << "\nNo favorite foods saved yet.\n";
        return;
    }

    cout << "\n========== FAVORITE FOODS ==========\n";
    for (const FoodItem& food : favorites) {
        food.display();
    }
    cout << "Total favorite/s: " << favorites.size() << "\n";
}

void FoodManager::generateSummaryReport(const string& currentWeather) const {
    int sunnyCount = 0, rainyCount = 0, coldCount = 0;
    int lowCount = 0, midCount = 0, highCount = 0;
    double totalPrice = 0.0;
    const FoodItem* cheapest = nullptr;
    const FoodItem* mostExpensive = nullptr;

    for (const FoodItem& food : foods) {
        if (food.getWeather() == "sunny") sunnyCount++;
        else if (food.getWeather() == "rainy") rainyCount++;
        else if (food.getWeather() == "cold") coldCount++;

        if (food.getBudgetLevel() == "low") lowCount++;
        else if (food.getBudgetLevel() == "mid") midCount++;
        else if (food.getBudgetLevel() == "high") highCount++;

        totalPrice += food.getPrice();
        if (cheapest == nullptr || food.getPrice() < cheapest->getPrice()) cheapest = &food;
        if (mostExpensive == nullptr || food.getPrice() > mostExpensive->getPrice()) mostExpensive = &food;
    }

    cout << "\n========== WEASOLVE SUMMARY REPORT ==========\n";
    cout << "Current weather      : " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n";
    cout << "Total food records   : " << foods.size() << "\n";
    cout << "Total favorite foods : " << favorites.size() << "\n";
    cout << "\nWeather counts:\nSunny: " << sunnyCount << " | Rainy: " << rainyCount << " | Cold: " << coldCount << "\n";
    cout << "Budget counts:\nLow: " << lowCount << " | Mid: " << midCount << " | High: " << highCount << "\n";

    if (!foods.empty()) {
        cout << "Average food price   : PHP " << fixed << setprecision(2) << (totalPrice / foods.size()) << "\n";
    }
    if (cheapest != nullptr) {
        cout << "Cheapest food        : " << cheapest->getName() << " (PHP " << fixed << setprecision(2) << cheapest->getPrice() << ")\n";
    }
    if (mostExpensive != nullptr) {
        cout << "Most expensive food  : " << mostExpensive->getName() << " (PHP " << fixed << setprecision(2) << mostExpensive->getPrice() << ")\n";
    }
    cout << "============================================\n";
}
