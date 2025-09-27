#include"./utils/service.h"

int main(){
    while (true) {
        cout << ColorText("╔══════════════════════════════════════════════╗", MAGENTA) << endl;
        cout << ColorText("║         🛠️  Admin Management System           ║", MAGENTA) << endl;
        cout << ColorText("╚══════════════════════════════════════════════╝", MAGENTA) << endl;

        cout << ColorText(" [1] ", CYAN) << ColorText("📋 Display Menu", YELLOW) << endl;
        cout << ColorText(" [2] ", CYAN) << ColorText("➕ Add Item to Menu", YELLOW) << endl;
        cout << ColorText(" [3] ", CYAN) << ColorText("✏️  Update Item in Menu", YELLOW) << endl;
        cout << ColorText(" [4] ", CYAN) << ColorText("❌ Delete Item from Menu", YELLOW) << endl;
        cout << ColorText(" [5] ", CYAN) << ColorText("🔍 Search Item in Menu", YELLOW) << endl;
        cout << ColorText(" [6] ", CYAN) << ColorText("💰 Sort Menu by Price", YELLOW) << endl;
        cout << ColorText(" [7] ", CYAN) << ColorText("🧾 Invoice", YELLOW) << endl;
        cout << ColorText(" [8] ", CYAN) << ColorText("🚪 Exit", YELLOW) << endl;

        cout << ColorText("════════════════════════════════════════════════", MAGENTA) << endl;
        cout << ColorText("👉 Please enter your choice: ", CYAN);
        int choice;
        cin >> choice;
        if (choice == 1) {
            vector<Menu> menu = readMenuCSV("database/menu.csv");
            displayMenu(menu);
        } else if (choice == 2) {
            adddrinkProduct("database/menu.csv");
        } else if (choice == 3) {
            string itemID;
            cout << ColorText(" Enter Item ID to update: ", CYAN);
            cin >> itemID;
            updateProduct("database/menu.csv", itemID);
        } else if (choice == 4) {
            string itemID;
            cout << ColorText(" Enter Item ID to delete: ", CYAN);
            cin >> itemID;
            deleteProduct("database/menu.csv", itemID);
        } else if (choice == 8) {
            cout << ColorText(" Goodbye Admin, Have a Nice Day !!", GREEN) << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}