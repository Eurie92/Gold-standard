#include "FoodManager.h" // Includes the FoodManager class declaration.
#include "InputValidator.h" // Includes validation functions so user input is safe.
#include "RecommendationEngine.h" // Includes smart ranking engine.
#include "UserPreference.h" // Includes grouped user preference data.
#include "RecommendationResult.h" // Includes result object with food + score + explanation.
#include <iostream> // Needed for cout.
#include <fstream> // Needed for ifstream/ofstream file reading/writing.
#include <sstream> // Needed for stringstream parsing of database lines.
#include <iomanip> // Needed for fixed and setprecision for money formatting.
#include <cctype> // Needed for isspace inside trim().
#include <algorithm> // Needed for remove_if when deleting favorites.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY:
 * - Domingo: CRUD logic.
 * - Malabanan: file handling.
 * - Alvarez: recommendation engine connection.
 * - Paulino: integration and final checking.
 *
 * BIG PICTURE EXPLAINED LIKE YOU ARE 10:
 * FoodManager is like the librarian of the food records.
 * It knows where the records are stored, how to read them, how to save them,
 * how to add new records, and how to show recommendations.
 * main.cpp just says, "FoodManager, please do this." Then FoodManager does the work.
 */

static string trim(const string& text) { // Helper function to remove spaces at beginning and end of a string.
    size_t start = 0; // start points to the first character we want to keep.
    while (start < text.size() && isspace(static_cast<unsigned char>(text[start]))) { // While current first character is a space...
        start++; // Move start forward until we reach non-space.
    } // End leading-space loop.
    size_t end = text.size(); // end starts after the last character.
    while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) { // While last kept character is a space...
        end--; // Move end backward until non-space.
    } // End trailing-space loop.
    return text.substr(start, end - start); // Return only the clean middle part of the text.
} // End trim helper.

static bool isValidWeather(const string& weather) { // Helper that checks if weather category is official.
    return weather == "sunny" || weather == "rainy" || weather == "cold"; // Allowed values only.
} // End weather helper.

static bool isValidBudget(const string& budget) { // Helper that checks if budget category is official.
    return budget == "low" || budget == "mid" || budget == "high"; // Allowed values only.
} // End budget helper.

int FoodManager::findIndexById(int id) const { // Finds where a food with this ID is located inside vector.
    for (int i = 0; i < static_cast<int>(foods.size()); i++) { // Loop through vector indexes from 0 to size-1.
        if (foods[i].getId() == id) { // If current food's ID matches the target ID...
            return i; // Return the index so update/delete/search can use it.
        } // End match check.
    } // End loop.
    return -1; // -1 means not found. This is a common sentinel value.
} // End findIndexById.

int FoodManager::generateNextId() const { // Generates next ID automatically.
    int highestId = 0; // Start with zero; any real ID should be higher.
    for (const FoodItem& food : foods) { // Visit every food record.
        if (food.getId() > highestId) { // If this food has bigger ID than current highest...
            highestId = food.getId(); // Update highest ID.
        } // End if.
    } // End loop.
    return highestId + 1; // New ID is one more than highest existing ID.
} // End generateNextId.

const vector<FoodItem>& FoodManager::getFoods() const { // Returns read-only reference to foods vector.
    return foods; // const reference avoids copying the entire vector while preventing modification.
} // End getFoods.

bool FoodManager::loadFromFile(const string& filename) { // Reads database.txt and loads all valid records into vector.
    ifstream file(filename); // Open file for reading.
    if (!file.is_open()) { // Check if file failed to open.
        cout << "Error: Cannot open database file: " << filename << "\n"; // Tell user exact missing file path.
        return false; // Return false to tell main.cpp loading failed.
    } // End file open check.

    foods.clear(); // Clear old memory records before loading fresh data from file.
    string line; // This will store one whole line from database.txt.
    int lineNumber = 0; // Tracks line number for warning messages.

    while (getline(file, line)) { // Read file line by line until end of file. This is while because we don't know line count in advance.
        lineNumber++; // Count this line.
        if (trim(line).empty()) { // If line is blank or spaces only...
            continue; // Skip it. continue means go to next loop iteration.
        } // End blank-line check.

        stringstream ss(line); // Put the line inside a stream so we can split it by '|'.
        string idText, name, weather, budgetLevel, priceText, restaurant, healthNote; // Temporary text variables for each field.

        getline(ss, idText, '|'); // Read ID until first pipe.
        getline(ss, name, '|'); // Read name until next pipe.
        getline(ss, weather, '|'); // Read weather until next pipe.
        getline(ss, budgetLevel, '|'); // Read budget until next pipe.
        getline(ss, priceText, '|'); // Read price until next pipe.
        getline(ss, restaurant, '|'); // Read restaurant until next pipe.
        getline(ss, healthNote); // Read the remaining text as health note.

        idText = trim(idText); // Clean spaces around ID text.
        name = trim(name); // Clean spaces around name.
        weather = InputValidator::toLowerCase(trim(weather)); // Clean and lowercase weather for consistent comparison.
        budgetLevel = InputValidator::toLowerCase(trim(budgetLevel)); // Clean and lowercase budget.
        priceText = trim(priceText); // Clean spaces around price.
        restaurant = trim(restaurant); // Clean spaces around restaurant.
        healthNote = trim(healthNote); // Clean spaces around health note.

        if (idText.empty() || name.empty() || weather.empty() || budgetLevel.empty() || // Check required fields.
            priceText.empty() || restaurant.empty() || healthNote.empty()) { // Continue checking required fields.
            cout << "Warning: Skipping incomplete record at line " << lineNumber << ".\n"; // Warn but do not crash.
            continue; // Skip incomplete line and continue loading other records.
        } // End incomplete check.

        if (!isValidWeather(weather) || !isValidBudget(budgetLevel)) { // Validate categories from file.
            cout << "Warning: Skipping invalid category at line " << lineNumber << ".\n"; // Warn about bad category.
            continue; // Skip invalid record.
        } // End category check.

        try { // Try conversion because stoi/stod can throw if text is not numeric.
            int id = stoi(idText); // Convert ID text to integer.
            double price = stod(priceText); // Convert price text to double.
            if (id <= 0 || price < 0.0) { // ID must be positive and price cannot be negative.
                cout << "Warning: Skipping invalid ID/price at line " << lineNumber << ".\n"; // Warn user.
                continue; // Skip bad record.
            } // End numeric validity check.
            foods.push_back(FoodItem(id, name, weather, budgetLevel, price, restaurant, healthNote)); // Create object and add to vector.
        } catch (...) { // Catch any conversion error from stoi/stod.
            cout << "Warning: Skipping invalid numeric field at line " << lineNumber << ".\n"; // Warn without crashing.
        } // End try/catch.
    } // End while getline loop.

    file.close(); // Close file after reading.
    cout << foods.size() << " food record/s loaded successfully.\n"; // Show how many records were loaded.
    return true; // Tell main.cpp loading succeeded.
} // End loadFromFile.

bool FoodManager::saveToFile(const string& filename) const { // Saves current vector records back to database.txt.
    ofstream file(filename); // Open file for writing. This overwrites old content with updated records.
    if (!file.is_open()) { // Check if file cannot be opened.
        cout << "Error: Cannot open database file for saving: " << filename << "\n"; // Show exact file path.
        return false; // Tell main.cpp saving failed.
    } // End file open check.

    for (const FoodItem& food : foods) { // Visit every food record in memory.
        file << food.toFileString() << "\n"; // Convert food object to database line and write it.
    } // End save loop.

    file.close(); // Close file so changes are finalized.
    return true; // Tell main.cpp saving succeeded.
} // End saveToFile.

void FoodManager::viewAllFoods() const { // Displays all food records. This is READ operation.
    if (foods.empty()) { // Guard clause: if no records, do not continue.
        cout << "\nNo food records found.\n"; // Tell user.
        return; // Exit function early.
    } // End empty check.

    cout << "\n========== ALL FOOD RECORDS ==========\n"; // Section title.
    for (const FoodItem& food : foods) { // Loop through all records.
        food.display(); // Let FoodItem display itself.
    } // End loop.
    cout << "Total records: " << foods.size() << "\n"; // Show total count.
} // End viewAllFoods.

void FoodManager::searchFood() const { // Lets user search by ID or name.
    if (foods.empty()) { // Guard clause: cannot search if no data.
        cout << "\nNo food records available to search.\n"; // Message.
        return; // Stop.
    } // End empty check.

    cout << "\nSearch Food Record\n"; // Title.
    cout << "[1] Search by ID\n"; // Option 1.
    cout << "[2] Search by Name\n"; // Option 2.
    int choice = InputValidator::getIntInRange("Enter choice: ", 1, 2); // Safe choice input.

    if (choice == 1) { // If user wants ID search.
        int id = InputValidator::getIntInRange("Enter food ID: ", 1, 1000000); // Get valid positive ID.
        int index = findIndexById(id); // Find the vector index.
        if (index == -1) { // If not found...
            cout << "Food record with ID " << id << " was not found.\n"; // Tell user.
        } else { // If found...
            foods[index].display(); // Display matching record.
        } // End found/not found.
    } else { // Otherwise search by name keyword.
        string keyword = InputValidator::toLowerCase(InputValidator::getNonEmptyLine("Enter food keyword: ")); // Get keyword and lowercase it.
        bool found = false; // Flag to know if at least one match was found.
        for (const FoodItem& food : foods) { // Loop through all foods.
            if (InputValidator::toLowerCase(food.getName()).find(keyword) != string::npos) { // Check if keyword exists inside food name.
                food.display(); // Show matching food.
                found = true; // Mark that match exists.
            } // End keyword match.
        } // End loop.
        if (!found) { // If no match after loop...
            cout << "No food record matched the keyword.\n"; // Tell user.
        } // End not found.
    } // End search type.
} // End searchFood.

void FoodManager::addFood() { // Admin-only CREATE operation.
    cout << "\n========== ADD NEW FOOD RECORD ==========" << "\n"; // Title.
    int newId = generateNextId(); // Auto-generate ID to avoid duplicate ID mistakes.
    string name = InputValidator::getNonEmptyLine("Enter food name: "); // Get valid non-empty food name.
    string weather = InputValidator::getWeatherInput(); // Get valid weather category.
    string budgetLevel = InputValidator::getBudgetInput(); // Get valid budget category.
    double price = InputValidator::getPositiveDouble("Enter estimated price: PHP "); // Get valid non-negative price.
    string restaurant = InputValidator::getNonEmptyLine("Enter restaurant/source: "); // Get valid restaurant/source.
    string healthNote = InputValidator::getNonEmptyLine("Enter health note: "); // Get valid health note.

    foods.push_back(FoodItem(newId, name, weather, budgetLevel, price, restaurant, healthNote)); // Create object and store in vector.
    cout << "Food record added successfully with ID " << newId << ".\n"; // Confirmation.
} // End addFood.

void FoodManager::updateFood() { // Admin-only UPDATE operation.
    if (foods.empty()) { // Guard clause: cannot update if database is empty.
        cout << "\nNo food records available to update.\n"; // Message.
        return; // Stop.
    } // End empty check.

    cout << "\n========== UPDATE FOOD RECORD ==========\n"; // Title.
    int id = InputValidator::getIntInRange("Enter food ID to update: ", 1, 1000000); // Get target ID safely.
    int index = findIndexById(id); // Find index in vector.

    if (index == -1) { // If ID not found...
        cout << "Food record with ID " << id << " was not found.\n"; // Tell user.
        return; // Stop update.
    } // End not found.

    foods[index].display(); // Show current record first so admin knows what will change.
    cout << "What do you want to update?\n"; // Ask field to update.
    cout << "[1] Food Name\n[2] Weather\n[3] Budget Level\n[4] Price\n[5] Restaurant\n[6] Health Note\n[7] Cancel\n"; // Field options.
    int choice = InputValidator::getIntInRange("Enter choice: ", 1, 7); // Safe menu input.

    switch (choice) { // switch is perfect here because choices are exact numbers.
        case 1: foods[index].setName(InputValidator::getNonEmptyLine("Enter new food name: ")); break; // Update name.
        case 2: foods[index].setWeather(InputValidator::getWeatherInput()); break; // Update weather.
        case 3: foods[index].setBudgetLevel(InputValidator::getBudgetInput()); break; // Update budget.
        case 4: foods[index].setPrice(InputValidator::getPositiveDouble("Enter new price: PHP ")); break; // Update price.
        case 5: foods[index].setRestaurant(InputValidator::getNonEmptyLine("Enter new restaurant/source: ")); break; // Update restaurant.
        case 6: foods[index].setHealthNote(InputValidator::getNonEmptyLine("Enter new health note: ")); break; // Update health note.
        case 7: cout << "Update cancelled.\n"; return; // Cancel update.
    } // End switch.

    cout << "Food record updated successfully.\n"; // Confirmation.
} // End updateFood.

void FoodManager::deleteFood() { // Admin-only DELETE operation.
    if (foods.empty()) { // Guard clause: cannot delete if no data.
        cout << "\nNo food records available to delete.\n"; // Message.
        return; // Stop.
    } // End empty check.

    cout << "\n========== DELETE FOOD RECORD ==========\n"; // Title.
    int id = InputValidator::getIntInRange("Enter food ID to delete: ", 1, 1000000); // Get target ID safely.
    int index = findIndexById(id); // Find target record.

    if (index == -1) { // If not found...
        cout << "Food record with ID " << id << " was not found.\n"; // Message.
        return; // Stop deletion.
    } // End not found.

    foods[index].display(); // Show record before deleting to prevent accidental deletion.
    string confirm = InputValidator::getYesNoInput("Are you sure you want to delete this record? (yes/no): "); // Ask confirmation.
    if (confirm == "yes") { // Delete only if admin says yes.
        foods.erase(foods.begin() + index); // Remove from main vector.
        favorites.erase(remove_if(favorites.begin(), favorites.end(), [id](const FoodItem& item) { // Also remove from favorites if it exists there.
            return item.getId() == id; // Lambda condition: match same ID.
        }), favorites.end()); // erase-remove idiom completes deletion from favorites.
        cout << "Food record deleted successfully.\n"; // Confirmation.
    } else { // If admin says no...
        cout << "Delete cancelled.\n"; // Cancel message.
    } // End confirmation.
} // End deleteFood.

void FoodManager::recommendByWeather(const string& weather) const { // Simple recommendation based only on current weather.
    if (foods.empty()) { // Guard clause if no records.
        cout << "\nNo food records available for recommendation.\n"; // Message.
        return; // Stop.
    } // End empty check.

    string selectedWeather = InputValidator::toLowerCase(weather); // Normalize weather.
    bool found = false; // Flag for at least one recommendation.
    int count = 0; // Count matching foods.

    cout << "\n========== SIMPLE WEATHER RECOMMENDATIONS FOR " << selectedWeather << " ==========\n"; // Title.
    for (const FoodItem& food : foods) { // Loop through foods.
        if (food.getWeather() == selectedWeather) { // Match weather only.
            food.display(); // Display recommendation.
            found = true; // Mark found.
            count++; // Count it.
        } // End match.
    } // End loop.

    if (!found) { // If no match...
        cout << "No recommendations found for this weather.\n"; // Message.
    } else { // If matches exist...
        cout << "Total simple recommendation/s found: " << count << "\n"; // Show count.
        cout << "Tip: Use Smart Ranked Recommendation for score + explanation.\n"; // Suggest better feature.
    } // End found check.
} // End recommendByWeather.

void FoodManager::recommendSmartRanking(const string& weather) const { // Gold/Architect recommendation using scoring engine.
    if (foods.empty()) { // Guard clause if no data.
        cout << "\nNo food records available for smart recommendation.\n"; // Message.
        return; // Stop.
    } // End empty check.

    UserPreference preference; // Create grouped user preference object.
    preference.weather = InputValidator::toLowerCase(weather); // Store selected current weather.
    preference.budgetLevel = InputValidator::getBudgetInput(); // Ask budget level.
    preference.availableMoney = InputValidator::getPositiveDouble("Enter your available money: PHP "); // Ask actual money.

    RecommendationEngine engine; // Create recommendation brain.
    vector<RecommendationResult> results = engine.recommend(foods, preference); // Ask engine to score and rank all foods.

    cout << "\n========== WEASOLVE SMART RANKED RECOMMENDATIONS ==========\n"; // Title.
    cout << "Weather: " << preference.weather << "\n"; // Show selected weather.
    cout << "Budget Level: " << preference.budgetLevel << "\n"; // Show selected budget.
    cout << "Available Money: PHP " << fixed << setprecision(2) << preference.availableMoney << "\n"; // Show money.
    cout << "Scoring Formula: Weather 40 + Budget 25 + Affordability 25 + Health Suitability 10 = 100\n"; // Explain formula.

    if (results.empty()) { // If no food reached threshold.
        cout << "No strong recommendation found. Try increasing your money or changing budget level.\n"; // Helpful advice.
        return; // Stop.
    } // End empty results.

    int rank = 1; // Rank starts at 1 for best result.
    for (const RecommendationResult& result : results) { // Loop through ranked results.
        cout << "\nRank #" << rank << " | Score: " << result.score << "/100\n"; // Show ranking and score.
        result.food.display(); // Show food details.
        cout << "Why recommended:\n" << result.explanation; // Show explanation produced by rules.
        rank++; // Move to next rank.
    } // End results loop.
} // End recommendSmartRanking.

void FoodManager::recommendByWeatherAndBudget(const string& weather) const { // Old compatibility function.
    recommendSmartRanking(weather); // Route to better smart ranking so old menu logic still works.
} // End wrapper.

void FoodManager::saveFavoriteFood(const string& weather) { // Saves one weather-matched food to favorites list.
    if (foods.empty()) { // Guard clause.
        cout << "\nNo food records available to save as favorite.\n"; // Message.
        return; // Stop.
    } // End empty check.

    string selectedWeather = InputValidator::toLowerCase(weather); // Normalize weather.
    bool hasMatch = false; // Tracks if there are foods under current weather.

    cout << "\n========== FOODS AVAILABLE FOR FAVORITES ==========\n"; // Title.
    for (const FoodItem& food : foods) { // Loop through foods.
        if (food.getWeather() == selectedWeather) { // Show only current weather foods.
            cout << "ID " << food.getId() << " - " << food.getName() << " (PHP " << fixed << setprecision(2) << food.getPrice() << ")\n"; // Compact list.
            hasMatch = true; // There is at least one option.
        } // End match.
    } // End loop.

    if (!hasMatch) { // If no option exists.
        cout << "No foods are available for the current weather.\n"; // Message.
        return; // Stop.
    } // End no match.

    int id = InputValidator::getIntInRange("Enter the ID of the food to save as favorite: ", 1, 1000000); // Ask chosen ID.
    int index = findIndexById(id); // Find record.

    if (index == -1 || foods[index].getWeather() != selectedWeather) { // Reject invalid ID or ID not in current weather list.
        cout << "Invalid ID. Please choose a food listed for the current weather.\n"; // Message.
        return; // Stop.
    } // End invalid check.

    for (const FoodItem& favorite : favorites) { // Check if already favorite.
        if (favorite.getId() == id) { // If duplicate ID found...
            cout << "This food is already in your favorites.\n"; // Message.
            return; // Stop to avoid duplicate favorites.
        } // End duplicate check.
    } // End loop.

    favorites.push_back(foods[index]); // Add selected food to favorites vector.
    cout << foods[index].getName() << " was saved to favorites.\n"; // Confirmation.
} // End saveFavoriteFood.

void FoodManager::viewFavorites() const { // Shows favorite foods saved during session.
    if (favorites.empty()) { // Guard clause if no favorites yet.
        cout << "\nNo favorite foods saved yet.\n"; // Message.
        return; // Stop.
    } // End empty check.

    cout << "\n========== FAVORITE FOODS ==========\n"; // Title.
    for (const FoodItem& food : favorites) { // Loop through favorite list.
        food.display(); // Display each favorite.
    } // End loop.
    cout << "Total favorite/s: " << favorites.size() << "\n"; // Show favorite count.
} // End viewFavorites.

void FoodManager::generateSummaryReport(const string& currentWeather) const { // Creates analytics/report from current data.
    int sunnyCount = 0, rainyCount = 0, coldCount = 0; // Counters by weather.
    int lowCount = 0, midCount = 0, highCount = 0; // Counters by budget.
    double totalPrice = 0.0; // Accumulator for average price.
    const FoodItem* cheapest = nullptr; // Pointer to cheapest food. nullptr means none yet.
    const FoodItem* mostExpensive = nullptr; // Pointer to most expensive food. nullptr means none yet.

    for (const FoodItem& food : foods) { // Visit every record to compute report.
        if (food.getWeather() == "sunny") sunnyCount++; // Count sunny foods.
        else if (food.getWeather() == "rainy") rainyCount++; // Count rainy foods.
        else if (food.getWeather() == "cold") coldCount++; // Count cold foods.

        if (food.getBudgetLevel() == "low") lowCount++; // Count low budget foods.
        else if (food.getBudgetLevel() == "mid") midCount++; // Count mid budget foods.
        else if (food.getBudgetLevel() == "high") highCount++; // Count high budget foods.

        totalPrice += food.getPrice(); // Add price to total for average calculation.
        if (cheapest == nullptr || food.getPrice() < cheapest->getPrice()) cheapest = &food; // Update cheapest pointer if needed.
        if (mostExpensive == nullptr || food.getPrice() > mostExpensive->getPrice()) mostExpensive = &food; // Update most expensive pointer if needed.
    } // End report loop.

    cout << "\n========== WEASOLVE SUMMARY REPORT ==========\n"; // Report title.
    cout << "Current weather      : " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n"; // Show current weather or NOT SET.
    cout << "Total food records   : " << foods.size() << "\n"; // Total records.
    cout << "Total favorite foods : " << favorites.size() << "\n"; // Total favorites.
    cout << "\nWeather counts:\nSunny: " << sunnyCount << " | Rainy: " << rainyCount << " | Cold: " << coldCount << "\n"; // Weather distribution.
    cout << "Budget counts:\nLow: " << lowCount << " | Mid: " << midCount << " | High: " << highCount << "\n"; // Budget distribution.

    if (!foods.empty()) { // Avoid division by zero.
        cout << "Average food price   : PHP " << fixed << setprecision(2) << (totalPrice / foods.size()) << "\n"; // Average price.
    } // End average check.
    if (cheapest != nullptr) { // If we found a cheapest food...
        cout << "Cheapest food        : " << cheapest->getName() << " (PHP " << fixed << setprecision(2) << cheapest->getPrice() << ")\n"; // Print cheapest.
    } // End cheapest.
    if (mostExpensive != nullptr) { // If we found most expensive food...
        cout << "Most expensive food  : " << mostExpensive->getName() << " (PHP " << fixed << setprecision(2) << mostExpensive->getPrice() << ")\n"; // Print most expensive.
    } // End most expensive.
    cout << "============================================\n"; // End report.
} // End generateSummaryReport.
