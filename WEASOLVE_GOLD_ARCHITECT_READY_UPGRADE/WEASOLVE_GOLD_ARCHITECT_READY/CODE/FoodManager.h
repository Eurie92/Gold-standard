#ifndef FOODMANAGER_H
#define FOODMANAGER_H

#include <vector>
#include <string>
#include "FoodItem.h"
using namespace std;

/*
 * ASSIGNED MEMBER PRIORITY:
 * - Domingo, Quirc Edrian P.: CRUD functions.
 * - Malabanan, Justine Lyle R.: loadFromFile() and saveToFile().
 * - Paulino, Eurie V.: system integration, main.cpp connection, validation checking.
 * - Alvarez, Jerome Oliver P.: upgraded smart recommendation engine and presentation demo support.
 *
 * FILE ROLE:
 * FoodManager is the organizer of all FoodItem records. It owns the vector<FoodItem>,
 * performs CRUD, loads/saves database.txt, calls the smart recommendation engine,
 * manages favorites, and generates reports.
 */
class FoodManager {
private:
    vector<FoodItem> foods;
    vector<FoodItem> favorites;

    int findIndexById(int id) const;
    int generateNextId() const;

public:
    bool loadFromFile(const string& filename);
    bool saveToFile(const string& filename) const;

    void viewAllFoods() const;
    void searchFood() const;
    void addFood();
    void updateFood();
    void deleteFood();

    void recommendByWeather(const string& weather) const;
    void recommendByWeatherAndBudget(const string& weather) const;
    void recommendSmartRanking(const string& weather) const;

    void saveFavoriteFood(const string& weather);
    void viewFavorites() const;
    void generateSummaryReport(const string& currentWeather) const;

    const vector<FoodItem>& getFoods() const;
};

#endif
