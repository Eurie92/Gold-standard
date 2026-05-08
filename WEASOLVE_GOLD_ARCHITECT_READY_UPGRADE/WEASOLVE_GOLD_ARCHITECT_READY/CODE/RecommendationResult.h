#ifndef RECOMMENDATIONRESULT_H
#define RECOMMENDATIONRESULT_H

#include "FoodItem.h"
#include <string>
using namespace std;

/*
 * NEW GOLD/ARCHITECT UPGRADE FILE
 * Struct: RecommendationResult
 *
 * Taglish explanation:
 * Kapag nagrecommend ang WEASOLVE, hindi sapat na sabihin lang ang food name.
 * Para ready sa professor defense, dapat masagot natin: "Bakit ito nirecommend?"
 * Kaya ang result natin ay may FoodItem, numerical score, at explanation.
 */
struct RecommendationResult {
    FoodItem food;       // The recommended food object.
    int score;           // Total score from all polymorphic rules. Target: close to 100.
    string explanation;  // Human-readable reasons why this food was recommended.
};

#endif
