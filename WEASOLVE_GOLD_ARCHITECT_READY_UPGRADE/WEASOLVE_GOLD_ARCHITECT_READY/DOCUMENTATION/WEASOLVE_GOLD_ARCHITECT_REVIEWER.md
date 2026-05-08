# WEASOLVE Gold Standard + Architect Award Reviewer

## 1. Short Introduction Script

Good day. We are V of Spades, and our project is WEASOLVE, which means Weather-Based Food Recommendation System. Our target is SDG 3: Good Health and Well-Being. The purpose of WEASOLVE is to help users decide what food to eat based on weather, budget, and available money.

Our system is not only a record storage program. It is a decision-support system. It loads food records from an external database, allows CRUD operations, validates user input, saves changes, and uses a smart ranking engine to recommend food.

## 2. Main Architecture Explanation

WEASOLVE is divided into multiple files so the program is not crowded in one `main.cpp` file.

- `main.cpp` is the controller. It displays the menu and calls the correct module.
- `FoodItem` represents one food record.
- `FoodManager` manages all records and handles CRUD, file handling, favorites, reports, and recommendation calls.
- `InputValidator` protects the program from invalid input.
- `RecommendationEngine` performs smart ranking.
- `RecommendationRule` is an abstract base class for scoring rules.

Taglish explanation: Para itong restaurant team. Si `main.cpp` ang receptionist. Si `FoodManager` ang manager ng records. Si `FoodItem` ang individual food card. Si `InputValidator` ang guard. Si `RecommendationEngine` ang judge na nagra-rank ng best food.

## 3. Gold Standard Upgrade

The upgraded system now has a smart scoring formula:

- Weather match: 40 points
- Budget match: 25 points
- Affordability: 25 points
- Health suitability: 10 points

Total: 100 points

This makes the recommendation explainable. The system can answer: "Why did WEASOLVE recommend this food?"

## 4. Architect Award Upgrade

The Architect Award requires strong system design. To support that, we added inheritance and polymorphism:

- `RecommendationRule` is the parent abstract class.
- `WeatherMatchRule`, `BudgetMatchRule`, `AffordabilityRule`, and `HealthSuitabilityRule` inherit from it.
- The engine stores rules using `unique_ptr<RecommendationRule>`.
- Each rule has its own `score()` and `explain()` function.

Simple explanation: Lahat sila ay rules, pero iba-iba ang job nila. One rule checks weather, one checks budget, one checks money, and one checks health note. This is polymorphism because the same function names behave differently depending on the rule object.

## 5. Member Study Assignments

### Paulino, Eurie V. - Project Lead / main.cpp / System Integration

Study:
- `main.cpp`
- menu loop
- switch-case
- how FoodManager and InputValidator connect
- overall architecture

Defense answer:
`main.cpp acts as the controller. It does not contain all logic. It only displays the menu, validates the chosen option, and calls the correct function from FoodManager. This follows modular design.`

### Beli, Jhon Rey B. - FoodItem

Study:
- `FoodItem.h`
- `FoodItem.cpp`
- private attributes
- constructors
- getters and setters
- `display()`
- `toFileString()`

Defense answer:
`FoodItem represents one food record. We used private attributes for encapsulation and public getters/setters for controlled access.`

### Domingo, Quirc Edrian P. - CRUD / FoodManager

Study:
- `viewAllFoods()`
- `searchFood()`
- `addFood()`
- `updateFood()`
- `deleteFood()`
- `vector<FoodItem>`

Defense answer:
`FoodManager handles CRUD operations. We used vector because the number of records changes when users add or delete food.`

### Malabanan, Justine Lyle R. - File Handling

Study:
- `loadFromFile()`
- `saveToFile()`
- `database.txt`
- parsing using `stringstream`
- `stoi()` and `stod()`

Defense answer:
`The system automatically loads records from database.txt and saves all changes when the user exits. This provides data persistence.`

### Alvarez, Jerome Oliver P. - Smart Recommendation Engine

Study:
- `RecommendationEngine.h/.cpp`
- `RecommendationRule.h/.cpp`
- scoring formula
- polymorphism
- smart ranked recommendation demo

Defense answer:
`The recommendation engine scores food using multiple rule classes. This makes the system explainable and expandable because new rules can be added without rewriting FoodManager.`

## 6. Possible Professor Questions and Strong Answers

### Q1. Why is the project multi-file?

Because multi-file architecture separates responsibilities. Header files declare what a module can do, while `.cpp` files implement the actual logic. This makes the system easier to maintain, debug, and divide among members.

### Q2. Why did you use vector instead of raw array?

A raw array has fixed size. Our project needs CRUD, meaning the user can add and delete records. `vector` is better because it can grow and shrink dynamically.

### Q3. What is your OOP implementation?

Our primary class is `FoodItem`. It uses private attributes, public getters/setters, constructors, and behavior methods like `display()` and `toFileString()`. We also added OOP design through `FoodManager`, `InputValidator`, and the polymorphic recommendation classes.

### Q4. What is the value-added logic?

The smart recommendation engine is our value-added logic. It does not only store data. It processes weather, budget, available money, and health notes to compute a recommendation score.

### Q5. Where is polymorphism used?

Polymorphism is used in `RecommendationRule`. The derived classes implement their own `score()` and `explain()` functions. The `RecommendationEngine` uses them through base-class pointers.

### Q6. Why is `InputValidator` important?

It prevents crashes caused by invalid user input. If the user enters letters when a number is required, it clears the error state and removes bad input from the buffer.

### Q7. Why use switch-case in main.cpp?

The menu choices are discrete exact numbers from 1 to 12. Switch-case is appropriate for exact choices.

### Q8. Why use if statements in recommendation rules?

Rules check conditions like weather match, budget match, and price within money. These are logical conditions, so if statements are appropriate.

### Q9. Why separate FoodManager and RecommendationEngine?

FoodManager should manage records. RecommendationEngine should analyze and rank records. This separation makes the system cleaner and more scalable.

### Q10. How can the system be improved in the future?

Future improvements include OpenWeather API integration, GUI implementation, calorie/nutrition scoring, restaurant distance filtering, and persistent favorites.

## 7. Presentation Flow for 8 Minutes

1. 0:00-0:40 Introduction and SDG
2. 0:40-1:20 Problem statement
3. 1:20-2:00 Features overview
4. 2:00-3:00 File structure and modular architecture
5. 3:00-4:10 OOP and polymorphism explanation
6. 4:10-5:30 Live demo of smart recommendation
7. 5:30-6:30 CRUD and database persistence demo
8. 6:30-7:20 Input validation and testing proof
9. 7:20-8:00 Closing and future improvements

## 8. Award Readiness Assessment

### Gold Standard

Strong chance if the team demonstrates:
- clean code
- full CRUD
- database persistence
- strong smart recommendation logic
- complete SDAD
- strong GitHub presentation
- confident defense

### Architect Award

Now realistic because the system includes:
- abstract base class
- derived classes
- virtual functions
- polymorphism
- separated recommendation engine
- extendable architecture

### Integrity Award

Also possible because of:
- InputValidator
- type mismatch protection
- range validation
- graceful error messages
- database line validation

### Best Portfolio Submission

Strong chance if GitHub includes:
- README
- screenshots
- class diagram
- flowchart
- testing matrix
- SDAD PDF
- clean commit history

## 9. Final Checklist Before GitHub Upload

- Compile the full program.
- Test all menu options.
- Upload the new code files.
- Add diagrams and screenshots.
- Add AI disclosure.
- Add README.
- Add SDAD.
- Add flowchart.
- Make commits with clear messages.
