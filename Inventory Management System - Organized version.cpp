#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;

#define max 50

int num = 0;

class Inventory {
public:
    int id;
    char name[20];
    char color[20];
    int quantity;
    int price;
};

Inventory inventory[max], tempInventory[max];

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void delay(int mSec) {
    long goal = mSec + (clock());
    while (goal > (clock()));
}

bool isFilePresent() {
    FILE* fp;
    fp = fopen("InventoryRecords.txt", "r");
    if (fp == NULL)
        return false;
    else
        return true;
}

void getRecords() {
    FILE* fp;
    fp = fopen("InventoryRecords.txt", "r");
    int g = 0;
    if (fp != NULL) {
        while (feof(fp) == 0) {
            fscanf(fp, "%d\t%s\t%s\t%d\t%d\n", &inventory[g].id, &inventory[g].name, &inventory[g].color, &inventory[g].quantity, &inventory[g].price);
            g++;
        }
        num = g;
    }
    fclose(fp);
}

void saveRecords() {
    if (num == 0) {
        system("del InventoryRecords.txt");
    } else {
        FILE* fp;
        fp = fopen("InventoryRecords.txt", "w");
        for (int i = 0; i < num; i++) {
            fprintf(fp, "%d\t%s\t%s\t%d\t%d\n", inventory[i].id, inventory[i].name, inventory[i].color, inventory[i].quantity, inventory[i].price);
        }
        fclose(fp);
    }
}

class UI {
public:
    static void introText() {
        cout << "\t------------------------------------------------------------" << endl;
        cout << "\t------------------------------------------------------------" << endl;
        cout << "\t-----EDU SILK SCREEN PRINTS INVENTORY MANAGEMENT SYSTEM-----" << endl;
        cout << "\t------------------------------------------------------------" << endl;
        cout << "\t------------------------- Welcome! -------------------------" << endl;
        cout << "\t------------------------------------------------------------" << endl;
    }

    static void opening() {
        cout << "\t------------------------------------------------------------" << endl;
        cout << "\t------------------EDU SILK SCREEN PRINTS--------------------" << endl;
        cout << "\t------------------------------------------------------------" << endl;
    }

    static void saveScreen() {
        cout << endl;
        cout << "\t-----------------------------------------------------------" << endl;
        cout << "\t----------------------Inventory Saved----------------------" << endl;
        cout << "\t-----------------------------------------------------------" << endl;
    }
};

class Load : public UI {
public:
    static void loading() {
        clearScreen();
        introText();
        cout << "\n\n\n\t\tLoading";
        displayLoading();
    }

    static void loadingLogin() {
        cout << "\n\n\n\t\tPlease wait";
        displayLoading();
    }

    static void updateMsg() {
        cout << "\n\t\tUpdating";
        displayLoading();
    }

    static void saveMsg() {
        cout << "\n\t\tSaving";
        displayLoading();
    }

    static void quitMsg() {
        cout << "\n\t\tQuiting";
        displayLoading();
    }

private:
    static void displayLoading() {
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                delay(200);
                cout << " - ";
            } else {
                delay(200);
                cout << " . ";
            }
        }
    }
};

class Update : public Load {
public:
    static void updateID(int i) {
        cout << "\n\t\t\tCurrent ID->" << "\t- " << inventory[i].id << " -";
        cout << "\n\t\t\tEnter New ID-> ";
        cin >> inventory[i].id;
        updateMsg();
    }

    static void updateName(int i) {
        cout << "\n\t\t\tCurrent Name->" << "\t- " << inventory[i].name << " -";
        cout << "\n\t\t\tEnter New Name-> ";
        cin >> inventory[i].name;
        updateMsg();
    }

    static void updateColor(int i) {
        cout << "\n\t\t\tCurrent Color->" << "\t- " << inventory[i].color << " -";
        cout << "\n\t\t\tEnter New Color-> ";
        cin >> inventory[i].color;
        updateMsg();
    }

    static void updateQuantity(int i) {
        cout << "\n\t\t\tCurrent Quantity->" << "\t- " << inventory[i].quantity << " -";
        cout << "\n\t\t\tEnter New Quantity-> ";
        cin >> inventory[i].quantity;
        updateMsg();
    }

    static void updatePrice(int i) {
        cout << "\n\t\t\tCurrent Price->" << "\t- " << inventory[i].price << " -";
        cout << "\n\t\t\tEnter New Price-> ";
        cin >> inventory[i].price;
        updateMsg();
    }
};

void continueKey() {
    UI::introText();
    cout << "\n\n\n\t\t\tPress any key to Continue";
    getch();
}

void login() {
    clearScreen();
    char username[30], password[30], ch;
    int i = 0;
    UI::introText();
    cout << "\n\t\t\t>>>LOG IN<<<";
    cout << "\n\t\t\tEnter Username: ";
    cin >> username;
    cout << "\t\t\tEnter password: ";

    while (1) {
        ch = getch();
        if (ch == 13)
            break;
        if (ch == 32 || ch == 9)
            continue;
        else {
            cout << "*";
            password[i] = ch;
            i++;
        }
    }
    password[i] = '\0';

    if (strcmp(username, "User") == 0 && strcmp(password, "User") == 0) {
        clearScreen();
        UI::introText();
        cout << "\n\n\t\t\t\tLOG IN SUCCESSFUL\n";
        delay(1000);
        Load::loading();
    } else {
        clearScreen();
        UI::introText();
        char F;
        bool validInput = false;
        do {
            Load::loading();
            clearScreen();
            UI::introText();
            cout << "\n\n\t\tLOG IN FAILED\n";
            cout << "\t\t\tTry again? (y/n)--> ";
            cin >> F;

            if (F == 'y') {
                Load::loading();
                login();
                validInput = true;
            } else if (F == 'n') {
                clearScreen();
                UI::introText();
                Load::quitMsg();
                clearScreen();
                UI::introText();
                cout << "\n\n\n\t\t\t\t-Goodbye!-\n";
                delay(200);
                cout << "\t\t\tThank you for using the System.";
                delay(200);
                validInput = true;
                exit(0);
            } else {
                clearScreen();
                UI::introText();
            }
        } while (!validInput);
    }
}

void sortByID() {
    for (int i = 0; i < num - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < num; j++) {
            if (inventory[j].id < inventory[minIndex].id) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Inventory temp = inventory[i];
            inventory[i] = inventory[minIndex];
            inventory[minIndex] = temp;
        }
    }
}

void displayInventory() {
    UI::opening();
    if (num == 0) {
        cout << "\n\t\t\tNo Records Found!";
    } else {
        cout << "\n\n\t------------------------------------------------------------";
        cout << "\n\t| ID\t| Name\t\t| Color\t\t| Quantity\t| Price\t|";
        cout << "\n\t------------------------------------------------------------";

        for (int i = 0; i < num; i++) {
            cout << "\n\t| " << inventory[i].id
                 << "\t| " << inventory[i].name
                 << "\t\t| " << inventory[i].color
                 << "\t\t| " << inventory[i].quantity
                 << "\t\t| " << inventory[i].price
                 << "\t|";
        }
        cout << "\n\t------------------------------------------------------------";
    }
}

void addInventory() {
    char choice;
    do {
        clearScreen();
        UI::opening();

        Inventory newItem;
        cout << "\n\t\tEnter New Item Details:";
        cout << "\n\t\tID: ";
        cin >> newItem.id;
        cout << "\n\t\tName: ";
        cin >> newItem.name;
        cout << "\n\t\tColor: ";
        cin >> newItem.color;
        cout << "\n\t\tQuantity: ";
        cin >> newItem.quantity;
        cout << "\n\t\tPrice: ";
        cin >> newItem.price;

        inventory[num] = newItem;
        num++;

        sortByID();
        saveRecords();

        cout << "\n\t\tAdd another item? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}

void searchInventory() {
    clearScreen();
    UI::opening();

    int searchID, found = 0;
    cout << "\n\t\tEnter ID to search: ";
    cin >> searchID;

    for (int i = 0; i < num; i++) {
        if (inventory[i].id == searchID) {
            cout << "\n\n\t------------------------------------------------------------";
            cout << "\n\t| ID\t| Name\t\t| Color\t\t| Quantity\t| Price\t|";
            cout << "\n\t------------------------------------------------------------";

            cout << "\n\t| " << inventory[i].id
                 << "\t| " << inventory[i].name
                 << "\t\t| " << inventory[i].color
                 << "\t\t| " << inventory[i].quantity
                 << "\t\t| " << inventory[i].price
                 << "\t|";
            cout << "\n\t------------------------------------------------------------";
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "\n\t\tRecord not found!";
    }

    continueKey();
}

void updateInventory() {
    clearScreen();
    UI::opening();

    int updateID, found = 0;
    cout << "\n\t\tEnter ID to update: ";
    cin >> updateID;

    for (int i = 0; i < num; i++) {
        if (inventory[i].id == updateID) {
            cout << "\n\t\tRecord found!";
            char choice;
            do {
                clearScreen();
                UI::opening();

                cout << "\n\t\tWhat would you like to update?";
                cout << "\n\t\t1. ID";
                cout << "\n\t\t2. Name";
                cout << "\n\t\t3. Color";
                cout << "\n\t\t4. Quantity";
                cout << "\n\t\t5. Price";
                cout << "\n\t\t6. Back to main menu";
                cout << "\n\n\t\tEnter choice: ";
                cin >> choice;

                switch (choice) {
                case '1':
                    Update::updateID(i);
                    break;
                case '2':
                    Update::updateName(i);
                    break;
                case '3':
                    Update::updateColor(i);
                    break;
                case '4':
                    Update::updateQuantity(i);
                    break;
                case '5':
                    Update::updatePrice(i);
                    break;
                case '6':
                    saveRecords();
                    return;
                default:
                    cout << "\n\t\tInvalid choice!";
                    break;
                }
            } while (choice != '6');

            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "\n\t\tRecord not found!";
    }
}

void deleteInventory() {
    clearScreen();
    UI::opening();

    int deleteID, found = 0;
    cout << "\n\t\tEnter ID to delete: ";
    cin >> deleteID;

    for (int i = 0; i < num; i++) {
        if (inventory[i].id == deleteID) {
            for (int j = i; j < num - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            num--;
            saveRecords();
            cout << "\n\t\tRecord deleted!";
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "\n\t\tRecord not found!";
    }

    continueKey();
}

void menu() {
    char choice;
    do {
        clearScreen();
        UI::introText();

        cout << "\n\t\t1. Display Inventory";
        cout << "\n\t\t2. Add Inventory";
        cout << "\n\t\t3. Search Inventory";
        cout << "\n\t\t4. Update Inventory";
        cout << "\n\t\t5. Delete Inventory";
        cout << "\n\t\t6. Quit";

        cout << "\n\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            displayInventory();
            continueKey();
            break;
        case '2':
            addInventory();
            break;
        case '3':
            searchInventory();
            break;
        case '4':
            updateInventory();
            break;
        case '5':
            deleteInventory();
            break;
        case '6':
            Load::quitMsg();
            return;
        default:
            cout << "\n\t\tInvalid choice!";
        }
    } while (choice != '6');
}

int main() {
    if (isFilePresent()) {
        getRecords();
    }
    login();
    menu();
    return 0;
}