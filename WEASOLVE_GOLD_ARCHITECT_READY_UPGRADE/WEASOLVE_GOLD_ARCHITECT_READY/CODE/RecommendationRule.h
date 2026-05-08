#ifndef RECOMMENDATIONRULE_H
#define RECOMMENDATIONRULE_H

#include "FoodItem.h"
#include "UserPreference.h"
#include <string>
using namespace std;

/*
 * NEW GOLD/ARCHITECT UPGRADE FILE
 * Abstract Class: RecommendationRule
 *
 * Taglish explanation for beginners:
 * Isipin mo na may apat na judges sa contest. Judge 1 checks weather, Judge 2 checks
 * budget, Judge 3 checks affordability, Judge 4 checks health suitability. Lahat sila
 * ay "RecommendationRule", pero iba-iba ang criteria nila.
 *
 * OOP concept:
 * This is the parent/base class. It uses virtual functions, so child classes can have
 * different behavior while sharing the same interface. Ito ang polymorphism.
 *
 * Why this helps Architect Award:
 * Hindi na isang mahabang if-else block ang recommendation. May organized inheritance
 * hierarchy na puwedeng dagdagan ng new rules in the future.
 */
class RecommendationRule {
public:
    virtual ~RecommendationRule() {}
    virtual int score(const FoodItem& food, const UserPreference& preference) const = 0;
    virtual string explain(const FoodItem& food, const UserPreference& preference) const = 0;
};

class WeatherMatchRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

class BudgetMatchRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

class AffordabilityRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

class HealthSuitabilityRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

#endif
