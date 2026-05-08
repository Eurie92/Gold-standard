WEASOLVE: Weather-Based Food Recommendation System
Group: V of Spades
Project Lead: Paulino, Eurie V.
Target SDG: SDG 3 - Good Health and Well-Being
Version: Gold Standard + Architect Award Candidate Console Version

1. Project Overview
WEASOLVE helps users decide what food to eat based on three practical factors:

Current weather: sunny, rainy, or cold
Budget level: low, mid, or high
Available money
The system is designed for students and everyday users who may struggle to decide what to eat. It supports SDG 3 by encouraging weather-suitable, budget-aware, and wellness-aware food choices.

2. Why This Version Is Improved
This upgraded version adds a Smart Ranked Recommendation Engine. The system no longer only filters food records. It now scores and ranks recommendations using polymorphic rule classes.

Recommendation Score Formula
Rule	Points	Meaning
WeatherMatchRule	40	Food is suitable for selected weather
BudgetMatchRule	25	Food matches selected budget level
AffordabilityRule	25	Food price is within available money
HealthSuitabilityRule	10	Health note supports weather suitability
Total	100	Best possible recommendation score
3. Architecture Summary
The project uses modular C++ architecture:

main.cpp controls the menu and program flow.
FoodItem represents one food record.
FoodManager handles CRUD, file loading/saving, favorites, and reporting.
InputValidator protects the program from invalid input.
RecommendationEngine ranks food records.
RecommendationRule and derived classes implement polymorphism.
4. Folder Structure
V_of_Spades_SDG_Project/
├── README.md
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
├── DOCUMENTATION/
│   ├── WEASOLVE_GOLD_ARCHITECT_REVIEWER.md
│   ├── WEASOLVE_GOLD_ARCHITECT_REVIEWER.docx
│   ├── CLASS_DIAGRAM.png
│   ├── RECOMMENDATION_FLOWCHART.png
│   ├── TESTING_MATRIX.md
│   ├── SDAD_POLYMORPHISM_SECTION.md
│   └── AI_ASSISTANCE_DISCLOSURE.md
└── SCREENSHOTS/
    ├── menu_output.png
    ├── smart_recommendation_output.png
    └── view_all_output.png
5. Compile and Run
Compile
g++ -std=c++17 -Wall -Wextra CODE/main.cpp CODE/FoodItem.cpp CODE/FoodManager.cpp CODE/InputValidator.cpp CODE/RecommendationRule.cpp CODE/RecommendationEngine.cpp -o WEASOLVE
Run
./WEASOLVE
On Windows Command Prompt:

WEASOLVE.exe
6. Contributors and Priority Study Areas
Member	Priority Area
Paulino, Eurie V.	main.cpp, integration, final defense, GitHub, architecture overview
Beli, Jhon Rey B.	FoodItem class, encapsulation, constructors, getters/setters
Domingo, Quirc Edrian P.	FoodManager CRUD: add, view, search, update, delete
Malabanan, Justine Lyle R.	loadFromFile(), saveToFile(), database.txt persistence
Alvarez, Jerome Oliver P.	RecommendationEngine, RecommendationRule, scoring/ranking demo
7. AI Assistance Disclosure
This project received AI assistance for planning, debugging support, code commenting, documentation organization, and reviewer preparation. The final implementation, testing, customization, and presentation preparation should be reviewed and defended by the project team.
