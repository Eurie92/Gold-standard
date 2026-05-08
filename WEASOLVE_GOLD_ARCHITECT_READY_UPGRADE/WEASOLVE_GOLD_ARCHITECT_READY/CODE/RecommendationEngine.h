#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include "FoodItem.h"
#include "UserPreference.h"
#include "RecommendationResult.h"
#include "RecommendationRule.h"
#include <vector>
#include <memory>
using namespace std;

/*
 * NEW GOLD/ARCHITECT UPGRADE FILE
 * Class: RecommendationEngine
 *
 * Taglish explanation:
 * Ito ang utak ng upgraded recommendation system. Hindi na siya simpleng filter lang.
 * Gumagamit siya ng multiple rule objects para bigyan ng score ang bawat food.
 *
 * Separation of concerns:
 * - FoodManager = taga-manage ng records, CRUD, load/save.
 * - RecommendationEngine = taga-analyze and rank ng recommendations.
 *
 * Polymorphism:
 * The vector stores pointers to RecommendationRule. Kahit iba-iba ang child classes,
 * one loop lang ang kailangan para tawagin ang score() and explain(). This is the
 * architect-level part of the system.
 */
class RecommendationEngine {
private:
    vector<unique_ptr<RecommendationRule>> rules;

public:
    RecommendationEngine();

    vector<RecommendationResult> recommend(
        const vector<FoodItem>& foods,
        const UserPreference& preference
    ) const;
};

#endif
