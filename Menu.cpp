#include "Menu.h"

using namespace std;


void ChangeWordDefMenu() {
    system("cls");
    cout << setw(95) << " " << "1. Change Definition" << '\n';
    cout << setw(95) << " " << "2. Add Definition" << '\n';
    cout << setw(95) << " " << "3. Back" << '\n';
}

vector<string> ChooseDictionaryMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. English - Vietnamese Dictionary");
    temp.push_back("2. Vietnamese - English Dictionary");
    temp.push_back("3. Emotional Dictionary");
    temp.push_back("4. Slang Dictionary");
    temp.push_back("5. Exit");
    return temp;
}

vector<string> ChooseFunctionsMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. Search");
    temp.push_back("2. Edit Dictionary");
    temp.push_back("3. View Random Word");
    temp.push_back("4. Favorite List");
    temp.push_back("5. Minigame");
    temp.push_back("6. Exit");
    return temp;
}

vector<string> SearchMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. Search");
    temp.push_back("2. View Search History");
    temp.push_back("3. Back");
    return temp;
}

vector<string> EditWordMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. Add New Word");
    temp.push_back("2. Edit Definition");
    temp.push_back("3. Remove Word");
    temp.push_back("4. Reset Dictionary");
    temp.push_back("5. Back");
    return temp;
}

vector<string> FavouriteMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. View Favorite List");
    temp.push_back("2. Remove Word from Favorite List");
    temp.push_back("3. Clear Favorite List");
    temp.push_back("4. Back");
    return temp;
}

vector<string> MinigameMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. Guess Word");
    temp.push_back("2. Guess Meaning");
    temp.push_back("3. Back");
    return temp;
}

vector<string> EditWordDefMenu() {
    system("cls");
    vector<string> temp;
    temp.push_back("1. Change Definition");
    temp.push_back("2. Add Definition");
    temp.push_back("3. Back");
    return temp;
}