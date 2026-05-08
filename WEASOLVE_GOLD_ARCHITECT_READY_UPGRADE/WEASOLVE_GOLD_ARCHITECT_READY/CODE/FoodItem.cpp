#include "FoodItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

/*
 * Default constructor.
 * We give safe starter values so the object never contains random garbage data.
 */
FoodItem::FoodItem() {
    this->id = 0;
    this->name = "";
    this->weather = "";
    this->budgetLevel = "";
    this->price = 0.0;
    this->restaurant = "";
    this->healthNote = "";
}

/*
 * Full constructor.
 * this-> means "attribute of this object".
 * Example: this->name = name means ilalagay natin ang parameter value sa private attribute.
 */
FoodItem::FoodItem(int id, string name, string weather, string budgetLevel,
                   double price, string restaurant, string healthNote) {
    this->id = id;
    this->name = name;
    this->weather = weather;
    this->budgetLevel = budgetLevel;
    this->price = price;
    this->restaurant = restaurant;
    this->healthNote = healthNote;
}

int FoodItem::getId() const { return id; }
string FoodItem::getName() const { return name; }
string FoodItem::getWeather() const { return weather; }
string FoodItem::getBudgetLevel() const { return budgetLevel; }
double FoodItem::getPrice() const { return price; }
string FoodItem::getRestaurant() const { return restaurant; }
string FoodItem::getHealthNote() const { return healthNote; }

void FoodItem::setId(int id) { this->id = id; }
void FoodItem::setName(string name) { this->name = name; }
void FoodItem::setWeather(string weather) { this->weather = weather; }
void FoodItem::setBudgetLevel(string budgetLevel) { this->budgetLevel = budgetLevel; }
void FoodItem::setPrice(double price) { this->price = price; }
void FoodItem::setRestaurant(string restaurant) { this->restaurant = restaurant; }
void FoodItem::setHealthNote(string healthNote) { this->healthNote = healthNote; }

void FoodItem::display() const {
    cout << "----------------------------------------\n";
    cout << "ID          : " << id << "\n";
    cout << "Food Name   : " << name << "\n";
    cout << "Weather     : " << weather << "\n";
    cout << "Budget      : " << budgetLevel << "\n";
    cout << "Price       : PHP " << fixed << setprecision(2) << price << "\n";
    cout << "Restaurant  : " << restaurant << "\n";
    cout << "Health Note : " << healthNote << "\n";
}

string FoodItem::toFileString() const {
    stringstream ss;
    ss << id << "|" << name << "|" << weather << "|" << budgetLevel << "|"
       << fixed << setprecision(2) << price << "|" << restaurant << "|" << healthNote;
    return ss.str();
}
