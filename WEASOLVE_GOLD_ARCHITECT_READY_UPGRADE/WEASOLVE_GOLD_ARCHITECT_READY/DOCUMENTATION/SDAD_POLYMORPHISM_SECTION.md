# SDAD Add-On Section: Polymorphic Recommendation Engine

## Architecture Upgrade

WEASOLVE uses a modular architecture where each file has a clear role. The main program flow is controlled by `main.cpp`, food records are represented by `FoodItem`, record management is handled by `FoodManager`, and input safety is handled by `InputValidator`.

To strengthen the analytical component of the system, the upgraded version adds a `RecommendationEngine`. This engine uses multiple recommendation rules to calculate a score for each food record.

## Polymorphism Explanation

The system uses an abstract base class named `RecommendationRule`. This class defines two required behaviors:

- `score()`
- `explain()`

The derived classes are:

1. `WeatherMatchRule`
2. `BudgetMatchRule`
3. `AffordabilityRule`
4. `HealthSuitabilityRule`

Each class implements its own scoring logic. This is polymorphism because the `RecommendationEngine` can treat all rule objects as `RecommendationRule` objects, while each child class behaves differently.

## Why This Is Better Than One Long If-Else Block

A simple program could place all recommendation logic in one long function. However, that approach becomes hard to maintain. In this upgraded architecture, each scoring rule is isolated. If a future developer wants to add a new rule such as calorie awareness, distance from restaurant, or student discount priority, they can add a new derived class without rewriting the whole engine.

## Value-Added Logic

WEASOLVE is not only a CRUD system. It processes stored food data and transforms it into ranked recommendations. The scoring system combines:

- weather suitability
- budget matching
- affordability
- health or weather suitability note

This supports the project requirement for value-added computation and makes the system more useful to users.
