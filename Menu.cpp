#include "Menu.h"

using namespace std;

void ChooseDictionaryMenu() {
    system("cls");
    cout << setw(90) << " " << "1. English - Vietnamese Dictionary" << '\n';
    cout << setw(90) << " " << "2. Vietnamese - English Dictionary" << '\n';
    cout << setw(90) << " " << "3. English Dictionary" << '\n';
    cout << setw(90) << " " << "0. Exit" << '\n';
}

void ChooseFunctionsMenu() {
    system("cls");
    cout << setw(95) << " " << "1. Search" << '\n';
    cout << setw(95) << " " << "2. Edit Dictionary" << '\n';
    cout << setw(95) << " " << "3. View Random Word" << '\n';
    cout << setw(95) << " " << "4. Favorite List" << '\n';
    cout << setw(95) << " " << "5. Minigame" << '\n';
    cout << setw(95) << " " << "0. Back" << '\n';
}

void SearchMenu() {
    system("cls");
    cout << setw(95) << " " << "1. Search by Keyword" << '\n';
    cout << setw(95) << " " << "2. Search by Definition" << '\n';
    cout << setw(95) << " " << "3. View Search History" << '\n';
    cout << setw(95) << " " << "0. Back" << '\n';
}

void EditWordMenu() {
    system("cls");
    cout << setw(95) << " " << "1. Add New Word" << '\n';
    cout << setw(95) << " " << "2. Edit Definition" << '\n';
    cout << setw(95) << " " << "3. Remove Word" << '\n';
    cout << setw(95) << " " << "4. Reset Dictionary" << '\n';
    cout << setw(95) << " " << "0. Back" << '\n';
}

void FavouriteMenu() {
    system("cls");
    cout << setw(95) << " " << "1. View Favorite List" << '\n';
    cout << setw(95) << " " << "2. Add Word to Favorite List" << '\n';
    cout << setw(95) << " " << "3. Remove Word from Favorite List" << '\n';
    cout << setw(95) << " " << "0. Back" << '\n';
}

void MinigameMenu() {
    system("cls");
    cout << setw(95) << " " << "1. Guess Word" << '\n';
    cout << setw(95) << " " << "2. Guess Meaning" << '\n';
    cout << setw(95) << " " << "0. Back" << '\n';
}
