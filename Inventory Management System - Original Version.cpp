#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;
#define max 50
int num=0;

class Inventory{
    public:
    int id;
    char name[20];
    char color[20];
    int quantity;
    int price;
};
void clearScreen(){
    cout << "\033[2J\033[1;1H";
}
Inventory inventory[max],tempInventory[max];
void getRecords(){
    FILE *fp; //file pointer
    fp = fopen("InventoryRecords.txt", "r");
    int g = 0;
    if (fp!=NULL){
        while(feof(fp)==0){
            fscanf(fp,"%d\t%s\t%s\t%d\t%d\n", &inventory[g].id,&inventory[g].name,&inventory[g].color,&inventory[g].quantity,&inventory[g].price);
            g++;
        }
        num=g;
    }
    fclose(fp);
}
void saveRecords(){
    if(num==0){
        system("del InventoryRecords.txt");
        }
    else{
        FILE *fp;
        fp = fopen("InventoryRecords.txt","w");
        for(int i=0;i<num;i++){
            fprintf(fp,"%d\t%s\t%s\t%d\t%d\n", inventory[i].id,inventory[i].name,inventory[i].color,inventory[i].quantity,inventory[i].price);


        }
        fclose(fp);
    }
}
bool isFilePresent(){
    FILE *fp;
    fp = fopen("InventoryRecords.txt","r");
    if(fp==NULL)
        return false;
    else
        return true;
}
void delay(int mSec) {
        long goal = mSec + (clock());
        while (goal > (clock()));
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
class Load: public UI {
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
        static void saveMsg(){
        cout << "\n\t\tSaving";
        displayLoading();
    }
        static void quitMsg(){
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
class Update: public Load {
public:
    static void updateID(int i){
        cout << "\n\t\t\tCurrent ID->"<< "\t- " << inventory[i].id << " -";
        cout << "\n\t\t\tEnter New ID-> ";
        cin >> inventory[i].id;
        updateMsg();
    }
    static void updateName(int i){
        cout << "\n\t\t\tCurrent Name->"<< "\t- " << inventory[i].name << " -";
        cout << "\n\t\t\tEnter New Name-> ";
        cin >> inventory[i].name;
        updateMsg();
    }
    static void updateColor(int i){
        cout << "\n\t\t\tCurrent Color->"<< "\t- " << inventory[i].color << " -";
        cout << "\n\t\t\tEnter New Color-> ";
        cin >> inventory[i].color;
        updateMsg();
    }
    static void updateQuantity(int i){
        cout << "\n\t\t\tCurrent Quantity->"<< "\t- " << inventory[i].quantity << " -";
        cout << "\n\t\t\tEnter New Quantity-> ";
        cin >> inventory[i].quantity;
        updateMsg();
    }
    static void updatePrice(int i){
        cout << "\n\t\t\tCurrent Price->"<< "\t- " << inventory[i].price << " -";
        cout << "\n\t\t\tEnter New Price-> ";
        cin >> inventory[i].price;
        updateMsg();
    }
};
void continueKey(){
    UI::introText();
    cout << "\n\n\n\t\t\tPress any key to Continue";
    getch();
}
void login(){
    clearScreen();
    char username[30],password[30],ch; int i=0;
    UI::introText();
    cout << "\n\t\t\t>>>LOG IN<<<";
    cout << "\n\t\t\tEnter Username: ";
    cin >> username;
    cout << "\t\t\tEnter password: ";


    while(1){
        ch = getch();
        if(ch==13)
            break;
        if(ch==32 || ch==9)
            continue;
        else{
            cout <<"*";
            password[i]=ch;
            i++;
        }
    }
    password[i] = '\0';
    if(strcmp(username,"User")==0 && strcmp(password,"User")==0){
        clearScreen();
        UI::introText();
        cout << "\n\n\t\t\t\tLOG IN SUCCESSFUL\n";
        delay(1000);
        Load::loading();
       
    }
    else{
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
class Menus: public Update{
public:
    static void menu(){
            clearScreen();
            opening();
            char choice;
                cout << endl;
                cout << "\t\t\t---O-P-T-I-O-N-S---\n" << endl;
                delay(200);
                cout << "\t\t\t(1) Add an item" << endl;
                delay(200);
                cout << "\t\t\t(2) Delete an item" << endl;
                delay(200);
                cout << "\t\t\t(3) Update an item" << endl;
                delay(200);
                cout << "\t\t\t(4) Sell an item" << endl;
                delay(200);
                cout << "\t\t\t(5) Find an item" << endl;
                delay(200);
                cout << "\t\t\t(6) View all products" << endl;
                delay(200);
                cout << "\t\t\t(7) Save inventory to file" << endl;
                delay(200);
                cout << "\t\t\t(Q) Quit" << endl;
                cout << "\n\n\t\t\tPlease choose an option:" << endl;
                delay(200);
        }
    static void editMenu(){
            clearScreen();
            opening();
            int id;
            cout <<"\n\t\t\t-----Update-----\n";
            delay(200);
            cout <<"\n\t\t\tWhat do you want to edit: \n";
            delay(200);
            cout <<"\t\t\t i ------> ID\n";
            delay(200);
            cout <<"\t\t\t n ------> NAME\n";
            delay(200);
            cout <<"\t\t\t c ------> COLOR\n";
            delay(200);
            cout <<"\t\t\t q ------> QUANTITY\n";
            delay(200);
            cout <<"\t\t\t p ------> PRICE\n";
            delay(200);
            cout <<"\t\t\t e ------> EXIT\n";
            delay(200);
        }
};
class Options: public Menus{
public:
    static void addItem() {
    try {
        int i = num;
        num += 1;
        clearScreen();
        UI::opening();
        cout << "\n\n\t\t\t--Add New Item-- \n";
        delay(200);
        cout << "\t\t\tID : ";
        if (!(cin >> inventory[i].id)) {
            throw "Invalid input: ID must be an integer.";
        }
        cout << "\t\t\tName : ";
        cin >> inventory[i].name;
        cout << "\t\t\tColor : ";
        cin >> inventory[i].color;
        cout << "\t\t\tQuantity : ";
        if (!(cin >> inventory[i].quantity)) {
            throw "Invalid input: Quantity must be an integer.";
        }
        cout << "\t\t\tPrice : ";
        if (!(cin >> inventory[i].price)) {
            throw "Invalid input: Price must be a integer.";
        }
        clearScreen();
        UI::opening();
        Load::saveMsg();
        clearScreen();
        UI::opening();
        cout << "\n\n\t\t\tRecorded Successfully...!!!";
        delay(500);
        cout << "\n\n\t\t\tPress Any Key To Continue. . ";
        getch();
    } catch (const char* e) {
        cerr << "\n\t\t\tError: " << e << endl;
        cout << "\n\n\t\t\tPress Any Key To Continue. . ";
        getch();
        cin.clear();
        cin.ignore();
    }
}
    static void view(){
                clearScreen();
                opening();
                cout << "\n\n\t\t\t   List of all the Items";
                cout << "\n\tID\tNAME\tCOLOR\tQUANTITY\tPRICE" << endl;
                cout << "\t------------------------------------------------------------" << endl;
                for(int i = 0, j = 8; i <= num -1; i++,j++){
                    cout <<"\t" << inventory[i].id <<" ";
                    delay(200);
                    cout <<"\t" << inventory[i].name  <<" ";
                    delay(200);
                    cout <<"\t" << inventory[i].color <<" ";
                    delay(200);
                    cout <<"\t" << inventory[i].quantity <<" ";
                    delay(200);
                    cout <<"\t\t"<< inventory[i].price <<" ";
                    delay(200);
                    cout << endl;
                }
            }
    static void findItem() {
                clearScreen();
                opening();
                sortByID();
                view();
                int id;
                cout << "\n\n\t\tEnter ID of the item you want to find: ";
                delay(200);
                cin >> id;
                bool found = false;
                for (int i = 0; i < num; i++) {
                    if (inventory[i].id == id) {
                        cout << "\n\t\t\t   Item Details\n\n\n";
                        delay(200);
                        cout << "\t\t\tID: " << inventory[i].id << endl;
                        delay(200);
                        cout << "\t\t\tNAME: " << inventory[i].name << endl;
                        delay(200);
                        cout << "\t\t\tCOLOR: " << inventory[i].color << endl;
                        delay(200);
                        cout << "\t\t\tQUANTITY: " << inventory[i].quantity << endl;
                        delay(200);
                        cout << "\t\t\tPRICE: " << inventory[i].price << endl;
                        delay(200);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n\t\t\tItem with ID " << id << " not found." << endl;
                    delay(200);
                }
                cout << "\n\t\t\tPress Any Key To Continue. . ";
                delay(200);
                getch();
            }
    static void edit(){
                clearScreen();
                opening();
                cout << "\n\t\t\t-----Update-----\n";
                sortByID();
                view();
                int id;
                int i;
                char option;
                bool found = false;
                cout <<"\n\n\t\tEnter ID you want to edit: ";
                delay(200);
                cin >> id;
                for (i = 0; i < num; i++){
                    if (inventory[i].id == id){
                        editMenu();
                        cout << "\n\t\tEnter your choice: ";
                        found = true;
                        char option;
                        cin >> option;
                        while(option !='e'){
                            switch (option){
                                case 'i':
                                    updateID(i);
                                    break;
                                case 'n':
                                    updateName(i);
                                    break;
                                case 'c':
                                    updateColor(i);
                                    break;
                                case 'q':
                                    updateQuantity(i);
                                    break;
                                case 'p':
                                    updatePrice(i);
                                    break;
                            }
                            editMenu();
                            cout << "\n\t\tEnter your choice: ";
                            cin >> option;
                        }
                    break;
                    }
                }
                if (!found) {
                    cout << "\n\t\t\tID not found!";
                    delay(200);
                    cout << "\n\t\tPress Any Key To Continue. . ";
                    delay(200);
                    getch();
                }
            }
    static void sellItem() {
                clearScreen();
                opening();
                sortByID();
                view();
                cout << "\n\n\t\t\t-----Sell Item-----\n";
                int id;
                cout << "\t\tEnter the ID of the item you want to sell: ";
                delay(200);
                cin >> id;
                int i;
                for(i = 0; i < num; i++) {
                    if(inventory[i].id == id) {
                        break;
                    }
                }
                if(i < num) {
                    int sellQuantity;
                    cout << "\t\tEnter the quantity of the item you want to sell: ";
                    cin >> sellQuantity;
                    if(sellQuantity <= inventory[i].quantity) {
                        int totalPrice = sellQuantity * inventory[i].price;
                        inventory[i].quantity -= sellQuantity;
                        cout << "\t\t" << sellQuantity << " item(s) sold successfully!\n";
                        delay(200);
                        cout << "\t\tTotal Price: $" << totalPrice << endl;
                        delay(200);
                    } else {
                        cout << "\t\tInsufficient quantity to sell!\n";
                        delay(200);
                    }
                } else {
                    cout << "\t\tItem with ID " << id << " not found." << endl;
                    delay(200);
                }
                cout << "\n\t\t\tPress Any Key To Continue. . ";
                getch();
            }
    static void deleteItem(){
                for(int i=0;i<num;i++){
                    tempInventory[i]=inventory[i];
                }
                int id;
                int check = -1;
                cout << "\n\n\t\t\t******** Delete Records ******** \n";
                sortByID();
                view();
                cout << "\n\t\tEnter the ID you want to delete: ";
                delay(200);
                cin >> id;
                int i,j;
                for(i = 0;i <= num-1;i++){
                    if(inventory[i].id==id){
                        check=i;
                    }
                }
                if(check!=-1)
                {
                    for(i = 0,j = 0;i <= num-1;i++,j++){
                        if(i==check)
                        {
                            i++;
                        }
                        inventory[j]=tempInventory[i];
                    }


                    clearScreen();
                    UI::opening();
                    num--;
                    cout << "\n\t\t\t Deleting";
                    for(int i = 0; i<10; i++){
                        delay(200);
                        cout << ".";
                    }


                    clearScreen();
                    opening();
                    cout << "\n\n\t\t\tDeleted Successfully...!!!";
                    delay(500);
                }
                else {
                    cout << "\n\n\t\t\tID not found!";
                }
                cout << "\n\t\t\tPress Any Key To Continue. . ";
                getch();
            }
    static void quitMenu(){
                cout << "\n\n\n\t\tYou are about to quit the program.\n";
                delay(500);
                cout << "\t\tDo you want to save? (y/n)--> ";
                delay(500);
                char F;
                bool validInput;
                cin >> F;
                if (F == 'y') {
                    clearScreen();
                    opening();
                    saveMsg();
                    clearScreen();
                    opening();
                    saveScreen();
                    delay(1000);
                    saveRecords();
                    clearScreen();
                opening();
                    cout << "\n\n\n\t\tThank you for using our system! ";
                    delay(200);
                    validInput = true;
                    exit(0);
                } else if (F == 'n') {
                    clearScreen();
                    opening();
                    quitMsg();
                    clearScreen();
                    opening();
                    cout << "\n\n\n\t\t\t\t-Goodbye!-\n";
                    cout << "\t\t\tThank you for using our system! ";
                    delay(200);
                    validInput = true;
                    exit(0);
                } else {
                    clearScreen();
                    opening();
                    quitMenu();
                }


         }
};


class Main: public Options{
public:
    static void Focus(){
        menu();
        getRecords();
        char option;
        if (inventory[0].id==0&& isFilePresent())
            num--;
        while(1){
            option = getch();
            switch (option){


                case '1':
                addItem();              
                break;


            case '2':
                deleteItem();
                break;
            case '3':
                edit();
                break;
            case '4':
                sellItem();
                break;
            case '5':
                findItem();
                break;
            case '6':
                clearScreen();
                opening();
                sortByID();
                view();
                cout<<"\n\t\tPress Any Key To Continue. . ";
                delay(200);
                getch();
                break;


            case '7':
                clearScreen();
                opening();
                saveMsg();
                clearScreen();
                opening();
                saveScreen();
                saveRecords();
                cout<<"\n\t\tPress Any Key To Continue. . ";
                delay(200);
                getch();
                break;


            case 'q':
            case 'Q':
                clearScreen();
                opening();
                quitMenu();
                break;
                }
                menu();
        }
    }
};

int main () {
        continueKey();
        Load::loading();
        login();
        Main::Focus();
        return 0;
}