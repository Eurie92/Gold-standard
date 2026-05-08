#include "RecommendationEngine.h"
#include <algorithm>
using namespace std;

RecommendationEngine::RecommendationEngine() {
    rules.push_back(make_unique<WeatherMatchRule>());
    rules.push_back(make_unique<BudgetMatchRule>());
    rules.push_back(make_unique<AffordabilityRule>());
    rules.push_back(make_unique<HealthSuitabilityRule>());
}

vector<RecommendationResult> RecommendationEngine::recommend(
    const vector<FoodItem>& foods,
    const UserPreference& preference
) const {
    vector<RecommendationResult> results;

    for (const FoodItem& food : foods) {
        int totalScore = 0;
        string explanation = "";
        int affordabilityPoints = 0;

        for (const auto& rule : rules) {
            int points = rule->score(food, preference);
            totalScore += points;

            if (dynamic_cast<AffordabilityRule*>(rule.get()) != nullptr) {
                affordabilityPoints = points;
            }

            if (points > 0) {
                explanation += rule->explain(food, preference);
            }
        }

        // Requirement decision:
        // We require affordabilityPoints > 0 so the system will not recommend food the user cannot pay for.
        // We require score >= 70 so the result is not random; it must be a strong match.
        if (affordabilityPoints > 0 && totalScore >= 70) {
            RecommendationResult result;
            result.food = food;
            result.score = totalScore;
            result.explanation = explanation;
            results.push_back(result);
        }
    }

    sort(results.begin(), results.end(),
        [](const RecommendationResult& a, const RecommendationResult& b) {
            if (a.score == b.score) {
                return a.food.getPrice() < b.food.getPrice();
            }
            return a.score > b.score;
        }
    );

    return results;
}
