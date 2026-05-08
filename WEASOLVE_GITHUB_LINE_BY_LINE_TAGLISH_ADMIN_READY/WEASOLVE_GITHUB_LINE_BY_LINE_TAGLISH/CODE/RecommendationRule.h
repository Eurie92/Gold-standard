#ifndef RECOMMENDATIONRULE_H // Header guard for RecommendationRule and derived classes.
#define RECOMMENDATIONRULE_H // Define guard.

#include "FoodItem.h" // Needed because rules inspect FoodItem details.
#include "UserPreference.h" // Needed because rules compare food against user choices.
#include <string> // Needed for explanation text.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P.
 *
 * ARCHITECT AWARD FILE:
 * This file shows inheritance and polymorphism.
 *
 * EXPLAINED LIKE YOU ARE 10:
 * Imagine may contest. May different judges: Weather Judge, Budget Judge, Affordability Judge,
 * and Health Judge. Lahat sila may same job name: "give score". Pero iba-iba ang basis nila.
 * That is polymorphism: same function name, different behavior depending on the child class.
 */
class RecommendationRule { // Abstract base class. Base means parent; abstract means hindi siya directly ginagamit as object.
public: // Public because RecommendationEngine must call these functions.
    virtual ~RecommendationRule() {} // Virtual destructor ensures safe cleanup when using base-class pointers.

    virtual int score(const FoodItem& food, const UserPreference& preference) const = 0; // Pure virtual: child classes MUST define their own scoring logic.
    virtual string explain(const FoodItem& food, const UserPreference& preference) const = 0; // Pure virtual: child classes MUST explain their own points.
}; // End parent/base class.

class WeatherMatchRule : public RecommendationRule { // Child class that checks if food weather matches user weather.
public: // Public so RecommendationEngine can use it.
    int score(const FoodItem& food, const UserPreference& preference) const override; // override means we are replacing the base version with specific weather logic.
    string explain(const FoodItem& food, const UserPreference& preference) const override; // Returns explanation for weather points.
}; // End WeatherMatchRule.

class BudgetMatchRule : public RecommendationRule { // Child class that checks if food budget matches user budget.
public: // Public behavior.
    int score(const FoodItem& food, const UserPreference& preference) const override; // Specific budget scoring.
    string explain(const FoodItem& food, const UserPreference& preference) const override; // Specific budget explanation.
}; // End BudgetMatchRule.

class AffordabilityRule : public RecommendationRule { // Child class that checks if user can afford the food.
public: // Public behavior.
    int score(const FoodItem& food, const UserPreference& preference) const override; // Specific affordability scoring.
    string explain(const FoodItem& food, const UserPreference& preference) const override; // Specific affordability explanation.
}; // End AffordabilityRule.

class HealthSuitabilityRule : public RecommendationRule { // Child class that gives extra points based on health note and weather suitability.
public: // Public behavior.
    int score(const FoodItem& food, const UserPreference& preference) const override; // Specific health/well-being scoring.
    string explain(const FoodItem& food, const UserPreference& preference) const override; // Specific health explanation.
}; // End HealthSuitabilityRule.

#endif // End header guard.
