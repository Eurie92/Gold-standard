# WEASOLVE PRESENTATION AND DEFENSE SCRIPT

## 1. Opening Introduction

Good day. We are V of Spades, and our project is WEASOLVE, which stands for Weather-Based Food Recommendation System. Our system helps users decide what food to eat based on weather, budget level, and available money. It also supports SDG 3, Good Health and Well-Being, because it helps users choose food options that match their situation and basic wellness needs.

## 2. Problem Statement

Many people struggle to decide what food to eat, especially students with limited budget. Some people also prefer different foods depending on the weather. WEASOLVE solves this by recommending food based on sunny, rainy, or cold weather, while also considering budget.

## 3. System Architecture Explanation

Our system is modular. We did not put everything inside one file.

- `main.cpp` is the controller.
- `FoodItem` represents one food record.
- `FoodManager` manages all food records and CRUD.
- `InputValidator` protects the system from invalid input.
- `RecommendationEngine` handles smart ranked recommendations.
- `RecommendationRule` is the parent class for polymorphic scoring rules.

## 4. Admin Panel Explanation

We placed Add, Update, and Delete inside the Admin Panel because those features modify the database. Normal users can still view, search, recommend, and save favorites, but only admin users can change records.

Admin PIN for demo: `1234`.

## 5. Smart Recommendation Explanation

Our smart recommendation engine uses scoring:

- Weather Match: 40 points
- Budget Match: 25 points
- Affordability: 25 points
- Health Suitability: 10 points

Total: 100 points.

The system ranks foods based on score and explains why each food was recommended.

## 6. Architect Award Explanation

We used inheritance and polymorphism:

- `RecommendationRule` is the abstract base class.
- `WeatherMatchRule`, `BudgetMatchRule`, `AffordabilityRule`, and `HealthSuitabilityRule` are derived classes.
- Each rule has its own `score()` and `explain()` behavior.

This means we can add more rules in the future without rewriting the whole recommendation engine.

## 7. Closing Statement

WEASOLVE is not only a storage system. It is a decision-support system that uses weather, budget, affordability, and health suitability to recommend food. It also demonstrates modular C++, OOP, CRUD, file handling, input validation, and polymorphic architecture.
