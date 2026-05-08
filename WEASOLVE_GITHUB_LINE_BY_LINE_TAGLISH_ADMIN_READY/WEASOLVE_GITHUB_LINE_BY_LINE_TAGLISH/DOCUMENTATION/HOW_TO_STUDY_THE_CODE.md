# HOW TO STUDY THE WEASOLVE CODE

## 1. Study Order

Do not start with the longest file. Study in this order:

1. `FoodItem.h` - Understand what one food record looks like.
2. `FoodItem.cpp` - Understand how one record displays and saves itself.
3. `InputValidator.h/.cpp` - Understand how invalid input is blocked.
4. `FoodManager.h` - Understand what the manager can do.
5. `FoodManager.cpp` - Study load/save, CRUD, recommendation, favorites, report.
6. `RecommendationRule.h/.cpp` - Study inheritance and polymorphism rules.
7. `RecommendationEngine.h/.cpp` - Study how all rules are applied and sorted.
8. `main.cpp` - Study how the menu connects everything.

## 2. Simple Connection Map

```txt
main.cpp
  ├── uses InputValidator for safe input
  ├── uses FoodManager for system actions
  └── sends user choices to correct functions

FoodManager
  ├── stores vector<FoodItem>
  ├── loads/saves INPUT_DATA/database.txt
  ├── performs CRUD
  ├── handles favorites and summary report
  └── calls RecommendationEngine for smart ranking

RecommendationEngine
  ├── owns different RecommendationRule objects
  ├── applies each rule to every FoodItem
  ├── computes total score
  └── sorts recommendations from highest to lowest

RecommendationRule
  ├── WeatherMatchRule
  ├── BudgetMatchRule
  ├── AffordabilityRule
  └── HealthSuitabilityRule
```

## 3. Why Admin Panel Was Added

Before, Add, Update, and Delete were visible in the normal menu. Now they are inside Admin Panel.

Reason:

```txt
Normal users should view, search, and receive recommendations.
Admin users should manage the database.
```

This makes the system more realistic without becoming too complicated.

## 4. What to Say in Defense

> We separated normal user features from admin features. Add, update, and delete can change the database, so we placed them behind a simple admin PIN. This demonstrates basic role-based access control while keeping the project understandable and aligned with our current C++ level.

## 5. Topic Basis

- Decision control: `switch-case` routes menu choices.
- Guard clauses: invalid or missing data is stopped early.
- Looping: `do-while` keeps the menu running.
- Collections: `vector<FoodItem>` stores many food records.
- Modular design: `.h` files declare, `.cpp` files implement.
- OOP: `FoodItem` encapsulates one record.
- Architect upgrade: `RecommendationRule` uses inheritance and polymorphism.
