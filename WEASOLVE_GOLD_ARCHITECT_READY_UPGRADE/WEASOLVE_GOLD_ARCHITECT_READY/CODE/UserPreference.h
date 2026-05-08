#ifndef USERPREFERENCE_H
#define USERPREFERENCE_H

#include <string>
using namespace std;

/*
 * NEW GOLD/ARCHITECT UPGRADE FILE
 * Struct: UserPreference
 *
 * Taglish explanation:
 * Ito ang lalagyan ng choices ng user habang nagre-recommend ang system.
 * Instead na ipasa natin separately ang weather, budgetLevel, at availableMoney
 * sa maraming functions, pinagsama natin sila sa isang structure.
 *
 * Why this is architectural improvement:
 * Mas malinis ang function parameters. Kapag may future preference like calories,
 * distance, or meal type, puwede natin idagdag dito without rewriting every function signature.
 */
struct UserPreference {
    string weather;          // Current weather selected by user: sunny, rainy, or cold.
    string budgetLevel;      // Budget category selected by user: low, mid, or high.
    double availableMoney;   // Actual money user can spend.
};

#endif
