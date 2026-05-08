#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
using namespace std;

/*
 * ASSIGNED MEMBER PRIORITY: Beli, Jhon Rey B.
 *
 * FILE ROLE (Taglish):
 * FoodItem.h ang blueprint ng isang food record. Isipin mo na ang bawat pagkain
 * ay isang index card. Sa card na iyon, nakasulat ang ID, pangalan, weather,
 * budget level, price, restaurant, at health note. Dito natin dinideclare kung
 * ano ang laman at kaya gawin ng isang FoodItem object.
 *
 * WHY THIS SUPPORTS THE RUBRIC:
 * - Gumagamit tayo ng class, private attributes, constructors, getters, setters,
 *   at behavior methods. Ito ang OOP requirement.
 * - Private ang data para maipakita ang encapsulation: hindi basta-basta gagalawin
 *   ng ibang files ang laman ng object.
 * - Public getters/setters ang legal na daan para basahin at baguhin ang data.
 */
class FoodItem {
private:
    int id;                 // Unique identifier. Ginagamit sa search/update/delete.
    string name;            // Food name, e.g., "Sinigang".
    string weather;         // Official categories: sunny, rainy, cold.
    string budgetLevel;     // Official categories: low, mid, high.
    double price;           // Price uses double because money can have decimals.
    string restaurant;      // Suggested restaurant/source.
    string healthNote;      // Human explanation why the food fits the weather/well-being need.

public:
    /*
     * Default constructor.
     * Purpose: Gumawa ng safe blank FoodItem.
     * Bakit kailangan: May ibang situations na kailangan muna ng empty object bago punuan.
     */
    FoodItem();

    /*
     * Full constructor.
     * Purpose: Gumawa agad ng complete food object in one line.
     * Approach: Lahat ng required fields pinapasa as parameters.
     */
    FoodItem(int id, string name, string weather, string budgetLevel,
             double price, string restaurant, string healthNote);

    // GETTERS: Read-only access. const means hindi babaguhin ng function ang object.
    int getId() const;
    string getName() const;
    string getWeather() const;
    string getBudgetLevel() const;
    double getPrice() const;
    string getRestaurant() const;
    string getHealthNote() const;

    // SETTERS: Controlled update. Used by FoodManager::updateFood().
    void setId(int id);
    void setName(string name);
    void setWeather(string weather);
    void setBudgetLevel(string budgetLevel);
    void setPrice(double price);
    void setRestaurant(string restaurant);
    void setHealthNote(string healthNote);

    /*
     * display()
     * Purpose: Ipakita ang isang record sa readable console format.
     * Important: FoodItem prints itself, so FoodManager does not need to know the formatting details.
     */
    void display() const;

    /*
     * toFileString()
     * Purpose: Convert object back to database.txt format.
     * Format: ID|Name|Weather|Budget|Price|Restaurant|HealthNote
     * Why important: Ito ang bridge from object memory back to persistent file storage.
     */
    string toFileString() const;
};

#endif
