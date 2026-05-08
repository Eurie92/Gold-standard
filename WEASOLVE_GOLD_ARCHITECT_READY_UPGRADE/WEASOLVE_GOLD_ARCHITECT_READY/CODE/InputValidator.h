#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
using namespace std;

/*
 * ASSIGNED MEMBER PRIORITY: Paulino, Eurie V.
 *
 * FILE ROLE (Taglish):
 * InputValidator is the safety guard of WEASOLVE. Kapag may user na nag-type ng
 * letter sa number input, negative price, blank name, or invalid weather, dito natin
 * hinaharang bago masira ang logic.
 *
 * LESSON BASIS:
 * - Guard clauses: reject invalid input early.
 * - Loops: keep asking until valid.
 * - cin.clear() and cin.ignore(): fix type mismatch so program will not crash or infinite loop.
 */
class InputValidator {
public:
    static int getIntInRange(string prompt, int min, int max);
    static double getPositiveDouble(string prompt);
    static string getWeatherInput();
    static string getBudgetInput();
    static string getYesNoInput(string prompt);
    static string getNonEmptyLine(string prompt);
    static string toLowerCase(string text);
};

#endif
