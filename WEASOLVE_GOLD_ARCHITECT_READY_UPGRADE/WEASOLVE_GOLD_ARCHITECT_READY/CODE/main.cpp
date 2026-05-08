#include <iostream>
#include <fstream>
#include <string>
#include "FoodManager.h"
#include "InputValidator.h"
using namespace std;

/*
 * ASSIGNED MEMBER PRIORITY: Paulino, Eurie V. (Project Lead)
 *
 * GOLD/ARCHITECT VERSION ROLE:
 * main.cpp is the controller. It does not store all system logic. It displays the menu,
 * validates the user's chosen option, then calls FoodManager. This is modular design.
 *
 * Important defense line:
 * "main.cpp is intentionally clean because our system follows separation of concerns.
 * FoodManager handles data operations, InputValidator handles safe input, and the new
 * RecommendationEngine handles smart ranking through polymorphism."
 */

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void displayHeader() {
    cout << "\n==========================================\n";
    cout << "                  WEASOLVE                \n";
    cout << "  Weather-Based Food Recommendation System\n";
    cout << "       SDG 3 - Good Health and Well-Being \n";
    cout << "     Gold + Architect Candidate Version   \n";
    cout << "==========================================\n";
}

void displayMenu(const string& currentWeather) {
    cout << "Current Weather: " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n\n";
    cout << "[1] Enter Current Weather\n";
    cout << "[2] View Simple Weather Recommendations\n";
    cout << "[3] Save Favorite Food\n";
    cout << "[4] View Favorite Foods\n";
    cout << "[5] Smart Ranked Recommendation Engine\n";
    cout << "[6] View All Food Records\n";
    cout << "[7] Search Food Record\n";
    cout << "[8] Add New Food Record\n";
    cout << "[9] Update Food Record\n";
    cout << "[10] Delete Food Record\n";
    cout << "[11] Generate Summary Report\n";
    cout << "[12] Save and Exit\n";
}

int main() {
    FoodManager manager;
    string currentWeather = "";
    int choice;

    string databasePath = "INPUT_DATA/database.txt";
    if (!fileExists(databasePath)) {
        databasePath = "../INPUT_DATA/database.txt";
    }

    if (!manager.loadFromFile(databasePath)) {
        cout << "Warning: Program started without loaded database records.\n";
    }

    do {
        displayHeader();
        displayMenu(currentWeather);
        choice = InputValidator::getIntInRange("Enter choice: ", 1, 12);

        switch (choice) {
            case 1:
                currentWeather = InputValidator::getWeatherInput();
                cout << "Current weather set to: " << currentWeather << "\n";
                break;

            case 2:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.recommendByWeather(currentWeather);
                }
                break;

            case 3:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.saveFavoriteFood(currentWeather);
                }
                break;

            case 4:
                manager.viewFavorites();
                break;

            case 5:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.recommendSmartRanking(currentWeather);
                }
                break;

            case 6:
                manager.viewAllFoods();
                break;

            case 7:
                manager.searchFood();
                break;

            case 8:
                manager.addFood();
                break;

            case 9:
                manager.updateFood();
                break;

            case 10:
                manager.deleteFood();
                break;

            case 11:
                manager.generateSummaryReport(currentWeather);
                break;

            case 12:
                if (manager.saveToFile(databasePath)) {
                    cout << "Data saved successfully.\n";
                }
                cout << "Thank you for using WEASOLVE!\n";
                break;
        }
    } while (choice != 12);

    return 0;
}
