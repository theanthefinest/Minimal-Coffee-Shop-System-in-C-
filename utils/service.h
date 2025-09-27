#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// =========> Define the Color Code <==============

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

// =========> Define the Print Style <==============

struct Menu{
    string ItemID;
    string DrinkName;
    string Size;
    double Price;
};


string ColorText(const string& text, const string& color){
    return color + text + RESET;
}

// =========> Void function Press any key to continue <================
void pressAnyKeyToContinue() {
    cout << ColorText("\n Thank you and Coming Again! (>.<)", YELLOW);
    cout << ColorText("\n Press any key to continue...", CYAN)<< endl;
    cin.ignore();
    cin.get();
    cout << endl;
}

// =========> Read Menu from CSV <================
vector<Menu> readMenuCSV(const string& filename){
    vector<Menu> menu;
    ifstream file(filename);
    
    if (!file.is_open()){
        cerr << ColorText("Error: Cannot open file " + filename, RED) << endl;
        return menu;
    }
    
    string line;
    bool isFirstLine = true;
    
    while (getline(file, line)){
        if (isFirstLine) {
            isFirstLine = false;
            continue; 
        }
        
        stringstream ss(line);
        Menu item;
        string priceStr;
        
        getline(ss, item.ItemID, ',');
        getline(ss, item.DrinkName, ',');
        getline(ss, item.Size, ',');
        getline(ss, priceStr);
        
        item.Price = stod(priceStr);
        menu.push_back(item);
    }
    
    file.close();
    return menu;
}

// ============> Display Menu <=================
void displayMenu(const vector<Menu>& menu) {
    cout << ColorText("\n Our Available Menu:     ",GREEN) << endl;
    cout << "───────────────────────────────────────────────" << endl;
    cout << " " << endl;
    cout << ColorText("┌─────┬─────────────────────┬───────────┬─────────┐", MAGENTA) << endl;
    cout << ColorText("│ ID  │ Drink Name          │ Size      │ Price   │", MAGENTA) << endl;
    cout << ColorText("├─────┼─────────────────────┼───────────┼─────────┤", MAGENTA) << endl;

    for (const auto& item : menu) {
        cout << ColorText("│", MAGENTA) << " "
             << setw(3) << left << ColorText(item.ItemID, YELLOW) << " "
             << ColorText("│", MAGENTA) << " "
             << setw(30) << left << ColorText(item.DrinkName, GREEN) << " "
             << ColorText("│", MAGENTA) << " "
             << setw(20) << left << ColorText(item.Size, BLUE) << " "
             << ColorText("│", MAGENTA) << " $ "
             << setw(5) << right << fixed << setprecision(2) << item.Price << " "
             << ColorText("│", MAGENTA) << endl;
    }

    cout << ColorText("└─────┴─────────────────────┴───────────┴─────────┘", MAGENTA) << endl;
    pressAnyKeyToContinue();
    system("clear");
}

// ============> Add Product <==================
bool adddrinkProduct(const string& filename){
    ofstream file(filename, ios::app);

    if(!file.is_open()){
        cerr << ColorText(" Can't open the file to write ", RED) <<endl;
    }

    Menu newItem;
    cout << ColorText(" Enter new Item ID: ", CYAN);
    getline(cin >> ws, newItem.ItemID);
    cout << ColorText(" Enter Drink Name: ", CYAN);
    getline(cin >> ws, newItem.DrinkName);
    cout << ColorText(" Enter Size: ", CYAN);
    getline(cin >> ws, newItem.Size);
    cout << ColorText(" Enter Price: ", CYAN);
    cin >> newItem.Price;

    cin.ignore();

    file << newItem.ItemID << ","
         << newItem.DrinkName << ","
         << newItem.Size << ","
         << newItem.Price <<endl;

    file.close();

    cout << ColorText(" Product is successfully added ~ >.< ~", GREEN) <<endl;
    pressAnyKeyToContinue();
    system("clear");
    return true;
}

// ============> Update Product <===============
bool updateProduct(const string& filename, const string& ItemID) {
    vector<Menu> menu = readMenuCSV(filename);
    bool found = false;

    for (auto& item : menu) {
        if (item.ItemID == ItemID) {
            found = true;

            // Show current item
            cout << ColorText("\nCurrent Item Details:", YELLOW) << endl;
            cout << "ID: " << item.ItemID << " | "
                 << "Drink: " << item.DrinkName << " | "
                 << "Size: " << item.Size << " | "
                 << "Price: " << item.Price << endl;

            // Ask for new details
            Menu newUpdateMenu;
            newUpdateMenu.ItemID = ItemID; // keep same ID
            cout << ColorText("\nEnter new Drink Name: ", CYAN);
            getline(cin >> ws, newUpdateMenu.DrinkName);

            cout << ColorText("Enter new Size: ", CYAN);
            getline(cin >> ws, newUpdateMenu.Size);

            cout << ColorText("Enter new Price: ", CYAN);
            cin >> newUpdateMenu.Price;

            // Apply update
            item = newUpdateMenu;

            // Show updated item
            cout << ColorText("\n Updated Item Details:", GREEN) << endl;
            cout << "ID: " << item.ItemID << " | "
                 << "Drink: " << item.DrinkName << " | "
                 << "Size: " << item.Size << " | "
                 << "Price: " << item.Price << endl;

            break;
        }
    }

    if (!found) {
        cerr << ColorText(" Product to update not found. Check the ID.", RED) << endl;
        return false;
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << ColorText(" Cannot open the file, please try again!", RED) << endl;
        return false;
    }

    file << "ItemID,DrinkName,Size,Price" << endl;
    for (const auto& item : menu) {
        file << item.ItemID << ","
             << item.DrinkName << ","
             << item.Size << ","
             << item.Price << endl;
    }
    file.close();

    pressAnyKeyToContinue();
    system("clear");
    return true;
}

//============> Delete Product <=================
bool deleteProduct(const string& filename, const string& ItemID) {
    vector<Menu> menu = readMenuCSV(filename);
    bool found = false;

    for (auto it = menu.begin(); it != menu.end(); ++it) {
        if (it->ItemID == ItemID) {
            found = true;
            
            cout << ColorText("\n🗑️ Current Item to Delete:", YELLOW) << endl;
            cout << "ID: " << it->ItemID << " | "
                 << "Drink: " << it->DrinkName << " | "
                 << "Size: " << it->Size << " | "
                 << "Price: " << it->Price << endl;

            menu.erase(it); 
            cout << ColorText("\n Product is successfully deleted ~ >.< ~", GREEN) << endl;
            break;
        }
    }

    if (!found) {
        cerr << ColorText(" Product to delete not found. Check the ID.", RED) << endl;
        return false;
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << ColorText(" Cannot open the file, please try again!", RED) << endl;
        return false;
    }

    file << "ItemID,DrinkName,Size,Price" << endl;
    for (const auto& item : menu) {
        file << item.ItemID << ","
             << item.DrinkName << ","
             << item.Size << ","
             << item.Price << endl;
    }
    file.close();

    pressAnyKeyToContinue();
    system("clear");

    return true;
}

bool SearchProduct(const string&filename){
    vector<Menu> menu = readMenuCSV(filename);
    string searchTerm;
    cout << ColorText(" Enter Drink Name to search: ", CYAN);
    getline(cin >> ws, searchTerm);

    vector<Menu> results;
    for (const auto& item : menu) {
        if (item.DrinkName.find(searchTerm) != string::npos) {
            results.push_back(item);
        }
    }

    if (results.empty()) {
        cout << ColorText(" No matching products found for: " + searchTerm, RED) << endl;
    } else {
        cout << ColorText("\n Search Results:", GREEN) << endl;
        cout << ColorText("───────────────────────────────────────────────" , MAGENTA)<< endl;
        cout << " " << endl;
        cout << ColorText("┌─────┬─────────────────────┬───────────┬─────────┐", MAGENTA) << endl;
        cout << ColorText("│ ID  │ Drink Name          │ Size      │ Price   │", MAGENTA) << endl;
        cout << ColorText("├─────┼─────────────────────┼───────────┼─────────┤", MAGENTA) << endl;

        for (const auto& item : results) {
            cout << ColorText("│", MAGENTA) << " "
                 << setw(3) << left << ColorText(item.ItemID, YELLOW) << " "
                 << ColorText("│", MAGENTA) << " "
                 << setw(30) << left << ColorText(item.DrinkName, GREEN) << " "
                 << ColorText("│", MAGENTA) << " "
                 << setw(20) << left << ColorText(item.Size, BLUE) << " "
                 << ColorText("│", MAGENTA) << " $ "
                 << setw(5) << right << fixed << setprecision(2) << item.Price << " "
                 << ColorText("│", MAGENTA) << endl;
        }

        cout << ColorText("└─────┴─────────────────────┴───────────┴─────────┘", MAGENTA) << endl;
    }

    pressAnyKeyToContinue();
    system("clear");
    return true;
}