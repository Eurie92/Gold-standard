#include <iostream> // Needed for cout/cin, the basic console input/output tools.
#include <fstream> // Needed for ifstream in fileExists(), so we can check if database.txt exists.
#include <string> // Needed because currentWeather, paths, and admin password are text.
#include "FoodManager.h" // Connects main.cpp to the FoodManager class, which handles records and system operations.
#include "InputValidator.h" // Connects main.cpp to safe input functions, preventing crashes from bad user input.
using namespace std; // Shortcut so beginners do not need to write std::cout and std::string every time.

/*
 * ASSIGNED MEMBER PRIORITY: Paulino, Eurie V. (Project Lead)
 *
 * FILE ROLE EXPLAINED LIKE YOU ARE 10:
 * main.cpp is like the remote control of the whole WEASOLVE system.
 * The remote control does not contain the whole TV inside it. It only sends commands.
 * Same here: main.cpp shows menus, accepts choices, then tells FoodManager what to do.
 *
 * IMPORTANT UPGRADE REQUEST:
 * Add/Update/Delete are now inside the Admin Panel only.
 * This means normal users can recommend/search/view, while admin can change database records.
 * For a school console project, this is a simple access-control simulation.
 * It is not bank-level security, but it is enough to show role-based logic.
 *
 * LESSON BASIS:
 * - switch-case is used because menu options are exact numbers.
 * - do-while is used because menu must appear at least once.
 * - guard clauses are used when weather is required before recommending.
 * - modular design is used because FoodManager and InputValidator are separate workers.
 */

bool fileExists(const string& filename) { // Small helper function that checks if a file path exists.
    ifstream file(filename); // Try opening the file for reading.
    return file.good(); // file.good() returns true if the file was opened successfully.
} // End fileExists.

void displayHeader() { // Prints the title/header of the system.
    cout << "\n==========================================\n"; // Top border for clean UI.
    cout << "                  WEASOLVE                \n"; // Project name.
    cout << "  Weather-Based Food Recommendation System\n"; // Project description.
    cout << "       SDG 3 - Good Health and Well-Being \n"; // SDG connection.
    cout << "     Gold + Architect Candidate Version   \n"; // Shows upgraded version for presentation.
    cout << "==========================================\n"; // Bottom border.
} // End displayHeader.

void displayMainMenu(const string& currentWeather) { // Shows the normal user menu.
    cout << "Current Weather: " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n\n"; // Ternary operator: if weather empty, show NOT SET; otherwise show weather.
    cout << "[1] Enter Current Weather\n"; // User sets weather first.
    cout << "[2] View Simple Weather Recommendations\n"; // Simple recommendation based on weather.
    cout << "[3] Save Favorite Food\n"; // Save a food to favorite list.
    cout << "[4] View Favorite Foods\n"; // View favorites.
    cout << "[5] Smart Ranked Recommendation Engine\n"; // Gold/Architect smart scoring feature.
    cout << "[6] View All Food Records\n"; // Read all records.
    cout << "[7] Search Food Record\n"; // Search record.
    cout << "[8] Admin Panel\n"; // Admin-only area for Add/Update/Delete.
    cout << "[9] Generate Summary Report\n"; // Show report/analytics.
    cout << "[10] Save and Exit\n"; // Save database and close program.
} // End displayMainMenu.

void displayAdminMenu() { // Shows admin-only options.
    cout << "\n========== ADMIN PANEL ==========\n"; // Section title.
    cout << "[1] Add New Food Record\n"; // CREATE operation.
    cout << "[2] Update Food Record\n"; // UPDATE operation.
    cout << "[3] Delete Food Record\n"; // DELETE operation.
    cout << "[4] Return to Main Menu\n"; // Exit admin panel.
} // End displayAdminMenu.

bool verifyAdminAccess() { // Simple admin access check before showing Admin Panel.
    const string ADMIN_PIN = "1234"; // Demo PIN. For presentation, explain this is simple role-based simulation only.
    string enteredPin = InputValidator::getNonEmptyLine("Enter admin PIN: "); // Ask user to enter PIN safely.
    if (enteredPin == ADMIN_PIN) { // Compare typed PIN to official PIN.
        cout << "Admin access granted.\n"; // Tell user access is accepted.
        return true; // Return true so admin panel can open.
    } // End correct PIN.
    cout << "Admin access denied. Returning to main menu.\n"; // Wrong PIN message.
    return false; // Return false so admin panel will not open.
} // End verifyAdminAccess.

void runAdminPanel(FoodManager& manager) { // Runs admin submenu and receives FoodManager by reference so it can modify actual records.
    if (!verifyAdminAccess()) { // Guard clause: if PIN wrong, stop immediately.
        return; // Exit admin panel.
    } // End access check.

    int adminChoice; // Stores admin menu choice.
    do { // do-while because admin menu should display at least once after successful login.
        displayAdminMenu(); // Show admin options.
        adminChoice = InputValidator::getIntInRange("Enter admin choice: ", 1, 4); // Safe admin choice input.

        switch (adminChoice) { // switch because choices are exact values 1-4.
            case 1: // Admin chooses Add.
                manager.addFood(); // Call FoodManager CREATE function.
                break; // Stop this case to avoid fall-through.
            case 2: // Admin chooses Update.
                manager.updateFood(); // Call FoodManager UPDATE function.
                break; // Stop this case.
            case 3: // Admin chooses Delete.
                manager.deleteFood(); // Call FoodManager DELETE function.
                break; // Stop this case.
            case 4: // Admin chooses return.
                cout << "Returning to main menu.\n"; // Friendly message.
                break; // End admin loop soon.
        } // End switch.
    } while (adminChoice != 4); // Repeat admin menu until admin chooses 4.
} // End runAdminPanel.

string chooseDatabasePath() { // Picks the correct database path depending on where the program is running.
    string path1 = "INPUT_DATA/database.txt"; // Normal GitHub/terminal path if program runs from project root.
    string path2 = "../INPUT_DATA/database.txt"; // Backup path if program runs one folder deeper.
    string path3 = "../../INPUT_DATA/database.txt"; // Backup path for Visual Studio x64/Debug style folders.

    if (fileExists(path1)) { // Check first possible location.
        return path1; // Use root INPUT_DATA.
    } // End path1 check.
    if (fileExists(path2)) { // Check second possible location.
        return path2; // Use parent folder INPUT_DATA.
    } // End path2 check.
    if (fileExists(path3)) { // Check third possible location.
        return path3; // Use grandparent folder INPUT_DATA.
    } // End path3 check.
    return path1; // Return default path so error message still tells expected location.
} // End chooseDatabasePath.

int main() { // Program starts here. Every C++ console program needs main().
    FoodManager manager; // Create the object that manages all food records and operations.
    string currentWeather = ""; // Current weather starts empty, so menu displays NOT SET.
    int choice; // Stores the user's main menu choice.

    string databasePath = chooseDatabasePath(); // Find the best database path automatically.
    if (!manager.loadFromFile(databasePath)) { // Try loading database file.
        cout << "Warning: Program started without loaded database records.\n"; // If failed, warn user but continue.
    } // End load check.

    do { // Main menu loop. do-while ensures the menu appears at least once.
        displayHeader(); // Print system title every loop.
        displayMainMenu(currentWeather); // Print menu and current weather status.
        choice = InputValidator::getIntInRange("Enter choice: ", 1, 10); // Safe input: only 1-10 accepted.

        switch (choice) { // Route user choice to the correct system action.
            case 1: // User wants to set weather.
                currentWeather = InputValidator::getWeatherInput(); // Ask and validate weather.
                cout << "Current weather set to: " << currentWeather << "\n"; // Confirm new weather.
                break; // End case 1.

            case 2: // User wants simple recommendation.
                if (currentWeather.empty()) { // Guard clause: recommendation needs weather first.
                    cout << "Please enter current weather first.\n"; // Explain missing requirement.
                } else { // Weather exists.
                    manager.recommendByWeather(currentWeather); // Show simple weather-based food list.
                } // End weather check.
                break; // End case 2.

            case 3: // User wants to save favorite.
                if (currentWeather.empty()) { // Favorite selection depends on current weather list.
                    cout << "Please enter current weather first.\n"; // Explain missing requirement.
                } else { // Weather exists.
                    manager.saveFavoriteFood(currentWeather); // Let user choose favorite food by ID.
                } // End weather check.
                break; // End case 3.

            case 4: // User wants to view favorites.
                manager.viewFavorites(); // Show favorites list.
                break; // End case 4.

            case 5: // User wants smart ranking.
                if (currentWeather.empty()) { // Smart ranking also needs weather.
                    cout << "Please enter current weather first.\n"; // Explain missing requirement.
                } else { // Weather exists.
                    manager.recommendSmartRanking(currentWeather); // Run polymorphic scoring engine.
                } // End weather check.
                break; // End case 5.

            case 6: // User wants to view all records.
                manager.viewAllFoods(); // Display all database records.
                break; // End case 6.

            case 7: // User wants to search.
                manager.searchFood(); // Search by ID or name.
                break; // End case 7.

            case 8: // User wants admin features.
                runAdminPanel(manager); // Ask PIN and show Add/Update/Delete if accepted.
                break; // End case 8.

            case 9: // User wants summary report.
                manager.generateSummaryReport(currentWeather); // Display analytics/report.
                break; // End case 9.

            case 10: // User wants to save and exit.
                if (manager.saveToFile(databasePath)) { // Save current records to database.txt.
                    cout << "Data saved successfully.\n"; // Confirm save.
                } // End save check.
                cout << "Thank you for using WEASOLVE!\n"; // Goodbye message.
                break; // End case 10.
        } // End switch.
    } while (choice != 10); // Continue program until user selects Save and Exit.

    return 0; // Return 0 means program ended successfully.
} // End main.
