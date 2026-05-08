#ifndef FOODMANAGER_H // Header guard: prevents duplicate FoodManager class definition.
#define FOODMANAGER_H // Define guard name.

#include <vector> // Needed because FoodManager stores many FoodItem objects in vector.
#include <string> // Needed for filenames, weather text, and other string values.
#include "FoodItem.h" // Needed because FoodManager manages FoodItem objects.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY:
 * - Domingo, Quirc Edrian P.: CRUD functions: view/search/add/update/delete.
 * - Malabanan, Justine Lyle R.: File handling: loadFromFile() and saveToFile().
 * - Paulino, Eurie V.: Integration with main.cpp, admin routing, validation flow.
 * - Alvarez, Jerome Oliver P.: Smart recommendation engine demo and explanation.
 *
 * FILE ROLE IN SIMPLE TAGLISH:
 * FoodManager is the system organizer. Kung FoodItem ay isang index card,
 * FoodManager ang box/folder na naglalaman ng lahat ng index cards.
 * Siya ang marunong mag-load, mag-save, maghanap, magdagdag, mag-update, mag-delete,
 * mag-recommend, mag-save ng favorites, at gumawa ng summary report.
 *
 * WHY THIS SUPPORTS GOLD STANDARD:
 * main.cpp stays clean. FoodManager does the heavy work. This follows modular design.
 */
class FoodManager { // Class that manages the whole collection of food records.
private: // Private because outside files should not directly edit the vector without rules.
    vector<FoodItem> foods; // Main database in memory. Loaded from INPUT_DATA/database.txt.
    vector<FoodItem> favorites; // Temporary favorite list during runtime.

    int findIndexById(int id) const; // Helper: returns vector index of matching ID, or -1 if not found.
    int generateNextId() const; // Helper: finds highest existing ID and returns next available ID.

public: // Public functions are the official actions that main.cpp can call.
    bool loadFromFile(const string& filename); // Loads database.txt into foods vector.
    bool saveToFile(const string& filename) const; // Saves foods vector back into database.txt.

    void viewAllFoods() const; // READ operation: shows all records.
    void searchFood() const; // READ operation: searches by ID or name.
    void addFood(); // CREATE operation: admin-only from menu, adds new record.
    void updateFood(); // UPDATE operation: admin-only from menu, updates existing record.
    void deleteFood(); // DELETE operation: admin-only from menu, removes existing record.

    void recommendByWeather(const string& weather) const; // Simple recommendation based on weather only.
    void recommendByWeatherAndBudget(const string& weather) const; // Compatibility wrapper that calls smart ranking.
    void recommendSmartRanking(const string& weather) const; // Gold/Architect smart ranking engine.

    void saveFavoriteFood(const string& weather); // Saves selected weather-matched food to favorites.
    void viewFavorites() const; // Shows saved favorite foods.
    void generateSummaryReport(const string& currentWeather) const; // Shows analytics/report counts.

    const vector<FoodItem>& getFoods() const; // Allows safe read-only access to foods if needed by other modules.
}; // End FoodManager class.

#endif // End header guard.
