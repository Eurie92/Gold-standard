# POSSIBLE PROFESSOR QUESTIONS AND ANSWERS

## Q1. Why did you separate Add, Update, and Delete into Admin Panel?

Because these features modify the database. In a real system, normal users should not freely change records. The Admin Panel is a simple role-based access control simulation.

## Q2. Is the admin PIN secure?

For this school console project, it is a simple demo PIN. It shows the logic of restricting access. If this became a real system, we would store hashed passwords and use accounts.

## Q3. Why use vector instead of array?

A vector can grow and shrink when records are added or deleted. A raw array has fixed size, so vector is better for CRUD operations.

## Q4. What is polymorphism in your system?

Polymorphism happens in the recommendation engine. The engine calls `score()` and `explain()` through the base class `RecommendationRule`, but each child class has its own behavior.

## Q5. What is your value-added computation?

The smart ranked recommendation engine. It scores food based on weather, budget, affordability, and health suitability, then ranks the best options.

## Q6. How do you prevent crashes from invalid input?

We use `InputValidator`. If the user types letters where a number is expected, we use `cin.clear()` and `cin.ignore()` to reset input and remove bad data.

## Q7. How does file handling work?

At startup, `loadFromFile()` reads `INPUT_DATA/database.txt` line by line. On save and exit, `saveToFile()` writes the updated vector back to the file.

## Q8. Why use `.h` and `.cpp` files?

`.h` files declare the interface or blueprint. `.cpp` files contain the implementation. This is separation of interface and implementation.

## Q9. What happens if database.txt has a bad line?

The loading function validates each line. If a line is incomplete or has invalid data, it skips the line and continues loading the rest instead of crashing.

## Q10. What makes your system Gold Standard candidate?

It has the required C++ features plus improved architecture, smart scoring, admin access, testing, documentation, and defense-ready comments.
