#ifndef FOODITEM_H // Header guard: pinipigilan nito na ma-include nang paulit-ulit ang FoodItem.h, kasi kapag naulit ang class definition, mag-e-error ang compiler.
#define FOODITEM_H // Kapag hindi pa nade-define ang FOODITEM_H, ide-define natin siya para alam ng compiler na nabasa na ang file na ito.

#include <string> // Kailangan natin ang string dahil halos lahat ng food details ay words, tulad ng name, weather, budget, restaurant, at health note.
using namespace std; // Para hindi na natin kailangan isulat ang std::string, std::cout, etc. Sa school projects okay ito, pero sa malaking industry code minsan iniiwasan ito.

/*
 * ASSIGNED MEMBER PRIORITY: Beli, Jhon Rey B.
 *
 * FILE ROLE IN SIMPLE TAGLISH:
 * This file is a blueprint. Imagine may blank form ka para sa isang food record.
 * Hindi pa ito actual food; template pa lang siya kung ano ang dapat laman ng bawat food.
 * Kapag gumawa tayo ng FoodItem object, doon na magiging actual record tulad ng:
 * ID 8, Sinigang, rainy, mid, 130, Karinderya, Warm sour soup.
 *
 * WHY THIS FILE EXISTS:
 * Sa modular programming, hindi dapat lahat nasa main.cpp. Ang FoodItem.h ay interface
 * or declaration file. Dito nakasulat kung anong data and functions meron ang FoodItem.
 * Yung actual instructions kung paano gagana ang functions ay nasa FoodItem.cpp.
 * This follows separation of interface and implementation from your function/modular design lessons.
 *
 * OOP CONCEPT USED:
 * Encapsulation. Private ang attributes para hindi sila direktang mabago ng ibang file.
 * Public getters and setters ang safe doorway para basahin or baguhin ang data.
 */
class FoodItem { // Class means blueprint for an object. Dito natin dine-define kung ano ang isang pagkain sa system.
private: // Private means hindi direktang maa-access outside the class. This protects the data from accidental wrong changes.
    int id; // Unique number ng food. Ginagamit ito sa search, update, delete, at favorite selection.
    string name; // Pangalan ng pagkain, example: "Sinigang" or "Halo-Halo".
    string weather; // Weather category kung saan bagay ang food. Allowed values: sunny, rainy, cold.
    string budgetLevel; // Budget category ng food. Allowed values: low, mid, high.
    double price; // Estimated price. double ang gamit kasi money can have decimals like 75.50.
    string restaurant; // Suggested restaurant or source kung saan pwedeng bilhin or kainin ang food.
    string healthNote; // Explanation kung bakit bagay ang food sa weather/well-being need.

public: // Public means ito ang allowed gamitin ng ibang files tulad ng FoodManager.cpp.
    FoodItem(); // Default constructor: gumagawa ng blank/safe food item para walang garbage values.

    FoodItem(int id, string name, string weather, string budgetLevel,
             double price, string restaurant, string healthNote); // Full constructor: gumagawa agad ng complete FoodItem using given values.

    int getId() const; // Getter: ibinabalik ang ID. const means hindi nito babaguhin ang object.
    string getName() const; // Getter: ibinabalik ang food name.
    string getWeather() const; // Getter: ibinabalik ang weather category.
    string getBudgetLevel() const; // Getter: ibinabalik ang budget category.
    double getPrice() const; // Getter: ibinabalik ang price.
    string getRestaurant() const; // Getter: ibinabalik ang restaurant/source.
    string getHealthNote() const; // Getter: ibinabalik ang health note.

    void setId(int id); // Setter: controlled way para baguhin ang ID kapag kailangan.
    void setName(string name); // Setter: controlled way para baguhin ang food name.
    void setWeather(string weather); // Setter: controlled way para baguhin ang weather category.
    void setBudgetLevel(string budgetLevel); // Setter: controlled way para baguhin ang budget level.
    void setPrice(double price); // Setter: controlled way para baguhin ang price.
    void setRestaurant(string restaurant); // Setter: controlled way para baguhin ang restaurant/source.
    void setHealthNote(string healthNote); // Setter: controlled way para baguhin ang health note.

    void display() const; // Behavior/function: pinapakita ang isang food record in readable format sa console.

    string toFileString() const; // Behavior/function: kino-convert ang object pabalik sa database.txt line format using | separators.
}; // End ng FoodItem class. Semicolon is required after class definition in C++.

#endif // End ng header guard. Kapag tapos na, safe na ang file from duplicate inclusion.
