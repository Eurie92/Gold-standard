#include "RecommendationEngine.h" // Gives access to RecommendationEngine declarations.
#include <algorithm> // Needed for sort().
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P.
 *
 * FILE ROLE:
 * This file runs the smart ranking process. It loops through every food, applies every rule,
 * computes total score, stores strong results, then sorts them from highest score to lowest.
 *
 * BASIS:
 * - Looping lessons: for loops / range-based loops traverse collections.
 * - Collections lessons: vector stores many food records.
 * - Modular/OOP lessons: recommendation logic is separated from FoodManager.
 * - Architect upgrade: polymorphic rules allow expansion without rewriting the whole engine.
 */

RecommendationEngine::RecommendationEngine() { // Constructor runs when RecommendationEngine object is created.
    rules.push_back(make_unique<WeatherMatchRule>()); // Add weather scoring rule to the rule list.
    rules.push_back(make_unique<BudgetMatchRule>()); // Add budget scoring rule to the rule list.
    rules.push_back(make_unique<AffordabilityRule>()); // Add affordability scoring rule to the rule list.
    rules.push_back(make_unique<HealthSuitabilityRule>()); // Add health/well-being scoring rule to the rule list.
} // End constructor.

vector<RecommendationResult> RecommendationEngine::recommend(const vector<FoodItem>& foods,
                                                             const UserPreference& preference) const { // Main recommendation function.
    vector<RecommendationResult> results; // Empty list where accepted recommendations will be stored.

    for (const FoodItem& food : foods) { // Visit every food in the database one by one.
        int totalScore = 0; // Start score at zero for this food.
        string explanation = ""; // Start with empty explanation; rules will add reasons.

        for (const auto& rule : rules) { // Apply each scoring rule to this food.
            int ruleScore = rule->score(food, preference); // Polymorphism: same score() call, but actual child rule decides behavior.
            totalScore += ruleScore; // Add this rule's points to total score.
            if (ruleScore > 0) { // Only explain rules that gave points.
                explanation += rule->explain(food, preference); // Polymorphism again: each child rule has own explanation.
            } // End if.
        } // End loop through rules.

        if (totalScore >= 70) { // Threshold: only strong matches enter the recommendation list.
            RecommendationResult result; // Create one result package.
            result.food = food; // Store the food.
            result.score = totalScore; // Store computed score.
            result.explanation = explanation; // Store combined explanations.
            results.push_back(result); // Add result to list.
        } // End threshold check.
    } // End loop through foods.

    sort(results.begin(), results.end(), [](const RecommendationResult& a, const RecommendationResult& b) { // Sort results using custom comparison.
        return a.score > b.score; // Higher score should appear first.
    }); // End sort.

    return results; // Return ranked list to FoodManager.
} // End recommend function.
