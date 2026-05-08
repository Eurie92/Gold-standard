# WEASOLVE: Weather-Based Food Recommendation System

**Group:** V of Spades  
**Project Lead:** Paulino, Eurie V.  
**Target SDG:** SDG 3 - Good Health and Well-Being  
**Version:** GitHub-ready, line-by-line Taglish commented, Gold + Architect candidate version

## Important Update

Add, Update, and Delete are now inside the **Admin Panel** instead of the normal user menu.

Default demo admin PIN:

```txt
1234
```

This is a simple role-based access simulation for a school console project. It is not meant to be bank-level security.

## Compile Command

```bash
g++ -std=c++17 -Wall -Wextra CODE/main.cpp CODE/FoodItem.cpp CODE/FoodManager.cpp CODE/InputValidator.cpp CODE/RecommendationRule.cpp CODE/RecommendationEngine.cpp -o WEASOLVE
```

## Run

```bash
./WEASOLVE
```

On Windows terminal:

```bash
WEASOLVE.exe
```

## Folder Structure

```txt
WEASOLVE_GITHUB_LINE_BY_LINE_TAGLISH/
├── CODE/
│   ├── main.cpp
│   ├── FoodItem.h
│   ├── FoodItem.cpp
│   ├── FoodManager.h
│   ├── FoodManager.cpp
│   ├── InputValidator.h
│   ├── InputValidator.cpp
│   ├── UserPreference.h
│   ├── RecommendationResult.h
│   ├── RecommendationRule.h
│   ├── RecommendationRule.cpp
│   ├── RecommendationEngine.h
│   └── RecommendationEngine.cpp
├── INPUT_DATA/
│   └── database.txt
└── DOCUMENTATION/
    ├── HOW_TO_STUDY_THE_CODE.md
    ├── PRESENTATION_AND_DEFENSE_SCRIPT.md
    ├── POSSIBLE_PROFESSOR_QUESTIONS.md
    └── IMPROVEMENT_RECOMMENDATIONS.md
```

## Member Study Priority

| Member | Priority Files / Topic |
|---|---|
| Paulino, Eurie V. | `main.cpp`, system integration, admin panel, final defense architecture |
| Beli, Jhon Rey B. | `FoodItem.h`, `FoodItem.cpp`, OOP class, encapsulation, getters/setters |
| Domingo, Quirc Edrian P. | `FoodManager.cpp` CRUD functions: view, search, add, update, delete |
| Malabanan, Justine Lyle R. | `FoodManager.cpp` file handling: loadFromFile/saveToFile and database format |
| Alvarez, Jerome Oliver P. | Recommendation engine: `RecommendationRule`, `RecommendationEngine`, scoring explanation |

## AI Assistance Disclosure

This project received AI assistance for planning, code commenting, debugging support, architecture improvement suggestions, reviewer preparation, and documentation organization. The final implementation should still be reviewed, tested, and understood by the project leader and members before submission.
