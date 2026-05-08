#ifndef RECOMMENDATIONENGINE_H // Header guard for RecommendationEngine.
#define RECOMMENDATIONENGINE_H // Define guard.

#include "FoodItem.h" // Needed because engine receives FoodItem records.
#include "UserPreference.h" // Needed because engine uses user choices.
#include "RecommendationResult.h" // Needed because engine returns ranked recommendation results.
#include "RecommendationRule.h" // Needed because engine stores and uses polymorphic scoring rules.
#include <vector> // Needed for vector collection of foods, results, and rules.
#include <memory> // Needed for unique_ptr, a safe pointer that automatically deletes objects.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P.
 *
 * ARCHITECT AWARD ROLE:
 * RecommendationEngine is the brain of smart ranking. FoodManager owns the data,
 * but RecommendationEngine analyzes the data. This separation makes the system cleaner.
 *
 * ADVANCED CONCEPT EXPLAINED SIMPLY:
 * vector<unique_ptr<RecommendationRule>> rules means:
 * - We have a list/vector of rule objects.
 * - Each rule can be a different child class.
 * - unique_ptr helps safely manage memory.
 * - Because rules are accessed through RecommendationRule*, polymorphism happens.
 */
class RecommendationEngine { // Class responsible for ranked recommendations.
private: // Private because only the engine should directly manage its internal rules.
    vector<unique_ptr<RecommendationRule>> rules; // Collection of polymorphic scoring rules.

public: // Public functions can be used by FoodManager.
    RecommendationEngine(); // Constructor creates and stores the scoring rules.

    vector<RecommendationResult> recommend(const vector<FoodItem>& foods,
                                           const UserPreference& preference) const; // Main engine function: scores and ranks foods.
}; // End RecommendationEngine class.

#endif // End header guard.
