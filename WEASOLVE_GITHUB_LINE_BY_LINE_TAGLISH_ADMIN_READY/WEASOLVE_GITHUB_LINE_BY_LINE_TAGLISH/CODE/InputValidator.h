#ifndef INPUTVALIDATOR_H // Header guard para hindi ma-include twice ang declarations ng InputValidator.
#define INPUTVALIDATOR_H // Define the guard name para alam ng compiler na nabasa na ito.

#include <string> // Kailangan natin string because prompts, weather, budget, yes/no answers are text.
using namespace std; // Shortcut para hindi na std::string sa beginner-friendly code.

/*
 * ASSIGNED MEMBER PRIORITY: Paulino, Eurie V. (Project Lead / Validation Support)
 *
 * FILE ROLE IN SIMPLE TAGLISH:
 * InputValidator is the safety guard of the system. Parang guard sa gate.
 * Kapag may maling input, hindi niya papapasukin sa main logic hanggang maayos.
 * Example: Kung number ang hinihingi pero nag-type ang user ng "abc", hindi dapat mag-crash.
 *
 * LESSON BASIS:
 * - From looping/input safety lessons: use cin.clear() and cin.ignore() kapag nasira ang input stream.
 * - From guard clause lesson: reject invalid data early para hindi pumasok sa dangerous logic.
 * - From modular design lesson: validation is separated from main.cpp para hindi crowded ang controller.
 */
class InputValidator { // Class ito, pero puro static functions. Ibig sabihin hindi na kailangan gumawa ng object para gamitin.
public: // Public because other files like main.cpp and FoodManager.cpp need to call these functions.
    static int getIntInRange(const string& prompt, int min, int max); // Gets a whole number and ensures it is between min and max.
    static double getPositiveDouble(const string& prompt); // Gets a money/price number and ensures it is not negative.
    static string getNonEmptyLine(const string& prompt); // Gets text input and rejects blank/empty answers.
    static string getWeatherInput(); // Gets only valid weather: sunny, rainy, or cold.
    static string getBudgetInput(); // Gets only valid budget: low, mid, or high.
    static string getYesNoInput(const string& prompt); // Gets only yes or no.
    static string toLowerCase(string text); // Converts text to lowercase so Sunny, SUNNY, sunny become same.
}; // End ng InputValidator class.

#endif // End ng header guard.
