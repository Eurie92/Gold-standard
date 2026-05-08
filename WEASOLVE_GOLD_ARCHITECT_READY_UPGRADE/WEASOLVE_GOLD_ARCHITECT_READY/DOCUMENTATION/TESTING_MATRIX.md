# WEASOLVE Testing Matrix

| Test Case | Input / Action | Expected Result | Status |
|---|---|---|---|
| Load database | Start program | Loads 20+ records from database.txt | Passed |
| Invalid menu input | Type letters when number is required | InputValidator rejects and asks again | Passed |
| Set weather | Enter rainy | Current weather becomes rainy | Passed |
| Simple recommendation | Option 2 after weather set | Shows all foods matching weather | Passed |
| Smart ranking | rainy, low, PHP 100 | Shows ranked foods with score and explanation | Passed |
| View all | Option 6 | Displays all food records | Passed |
| Search by ID | Existing ID | Displays matching record | Passed |
| Add record | Valid new food data | Adds new record with generated ID | Passed |
| Update record | Existing ID and new value | Record updates correctly | Passed |
| Delete record | Existing ID + yes confirmation | Record is removed | Passed |
| Summary report | Option 11 | Shows counts, average price, cheapest, most expensive | Passed |
| Save and exit | Option 12 | Saves database.txt and exits | Passed |
| Reopen after saving | Run again | Previously saved changes are retained | Passed |
