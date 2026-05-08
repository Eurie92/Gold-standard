#include "FoodItem.h" // Kinukuha natin ang FoodItem blueprint para ma-define natin dito ang actual behavior ng functions.
#include <iostream> // Kailangan ito para sa cout, which is used by display().
#include <iomanip> // Kailangan ito para sa fixed and setprecision(2), para two decimal places ang price.
#include <sstream> // Kailangan ito para sa stringstream, ginagamit sa toFileString() para buuin ang database line.
using namespace std; // Para mas maikli ang syntax sa school-level code.

/*
 * ASSIGNED MEMBER PRIORITY: Beli, Jhon Rey B.
 *
 * FILE ROLE:
 * FoodItem.cpp is the implementation file. Kung FoodItem.h ay parang table of contents,
 * ito naman ang actual chapter. Dito nakasulat kung ano talaga ang ginagawa ng constructors,
 * getters, setters, display, and toFileString.
 */

FoodItem::FoodItem() { // Default constructor: automatically called kapag gumawa ka ng FoodItem without values.
    this->id = 0; // Safe starting ID. 0 means wala pang real database ID.
    this->name = ""; // Empty name para hindi random memory ang laman.
    this->weather = ""; // Empty weather muna dahil wala pang assigned category.
    this->budgetLevel = ""; // Empty budget muna dahil wala pang assigned level.
    this->price = 0.0; // Zero price as safe default.
    this->restaurant = ""; // Empty restaurant as safe default.
    this->healthNote = ""; // Empty health note as safe default.
} // End ng default constructor.

FoodItem::FoodItem(int id, string name, string weather, string budgetLevel,
                   double price, string restaurant, string healthNote) { // Full constructor: ginagamit kapag complete na ang data galing database or user input.
    this->id = id; // this->id is the private attribute; id is the parameter. Nililipat natin ang parameter value sa object.
    this->name = name; // Store the food name inside the object.
    this->weather = weather; // Store the weather category inside the object.
    this->budgetLevel = budgetLevel; // Store the budget level inside the object.
    this->price = price; // Store the price inside the object.
    this->restaurant = restaurant; // Store the restaurant/source inside the object.
    this->healthNote = healthNote; // Store the health note inside the object.
} // End ng full constructor.

int FoodItem::getId() const { return id; } // Return ID only. Hindi binabago ang object, kaya const.
string FoodItem::getName() const { return name; } // Return name only.
string FoodItem::getWeather() const { return weather; } // Return weather category only.
string FoodItem::getBudgetLevel() const { return budgetLevel; } // Return budget category only.
double FoodItem::getPrice() const { return price; } // Return price only.
string FoodItem::getRestaurant() const { return restaurant; } // Return restaurant/source only.
string FoodItem::getHealthNote() const { return healthNote; } // Return health note only.

void FoodItem::setId(int id) { this->id = id; } // Change ID through controlled setter.
void FoodItem::setName(string name) { this->name = name; } // Change name through controlled setter.
void FoodItem::setWeather(string weather) { this->weather = weather; } // Change weather through controlled setter.
void FoodItem::setBudgetLevel(string budgetLevel) { this->budgetLevel = budgetLevel; } // Change budget through controlled setter.
void FoodItem::setPrice(double price) { this->price = price; } // Change price through controlled setter.
void FoodItem::setRestaurant(string restaurant) { this->restaurant = restaurant; } // Change restaurant through controlled setter.
void FoodItem::setHealthNote(string healthNote) { this->healthNote = healthNote; } // Change health note through controlled setter.

void FoodItem::display() const { // This function prints one food record. const because printing should not edit the object.
    cout << "----------------------------------------\n"; // Separator line para hindi dikit-dikit ang records.
    cout << "ID          : " << id << "\n"; // Print unique ID.
    cout << "Food Name   : " << name << "\n"; // Print food name.
    cout << "Weather     : " << weather << "\n"; // Print weather category.
    cout << "Budget      : " << budgetLevel << "\n"; // Print budget category.
    cout << "Price       : PHP " << fixed << setprecision(2) << price << "\n"; // Print price with 2 decimals for money format.
    cout << "Restaurant  : " << restaurant << "\n"; // Print restaurant/source.
    cout << "Health Note : " << healthNote << "\n"; // Print explanation for SDG/well-being connection.
} // End ng display function.

string FoodItem::toFileString() const { // Converts object to one database.txt line.
    stringstream ss; // stringstream is like a small text builder. Mas malinis siya kaysa maraming string + string.
    ss << id << "|" << name << "|" << weather << "|" << budgetLevel << "|" // Add first fields separated by pipe symbol.
       << fixed << setprecision(2) << price << "|" << restaurant << "|" << healthNote; // Add price and remaining fields.
    return ss.str(); // Convert the built stream into normal string and return it to caller.
} // End ng toFileString function.
