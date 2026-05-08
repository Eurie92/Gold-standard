#ifndef RECOMMENDATIONRESULT_H // Header guard to prevent duplicate definition.
#define RECOMMENDATIONRESULT_H // Define guard.

#include "FoodItem.h" // Needed because each recommendation result contains a FoodItem.
#include <string> // Needed because explanation is text.
using namespace std; // Beginner-friendly shortcut.

/*
 * ASSIGNED MEMBER PRIORITY: Alvarez, Jerome Oliver P. (Smart Recommendation Study Support)
 *
 * PURPOSE:
 * RecommendationResult is the final package produced by the smart recommendation engine.
 * Hindi lang siya food. May score and explanation din.
 *
 * WHY IMPORTANT FOR DEFENSE:
 * Kapag tinanong ng professor, "Bakit iyan ang nirecommend?", may answer tayo.
 * The explanation field stores the reason line by line.
 */
struct RecommendationResult { // Grouped output of the recommendation engine.
    FoodItem food; // The actual food being recommended.
    int score; // Total score from all scoring rules, usually up to 100.
    string explanation; // Human-readable reason why this food was recommended.
}; // End struct.

#endif // End header guard.
