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
    cout << setw(105) << " " << "1. Search" << endl;
    cout << setw(105) << " " << "2. Edit Dictionary" << endl;
    cout << setw(105) << " " << "3. View Random Word" << endl;
    cout << setw(105) << " " << "4. Favorite List" << endl;
    cout << setw(105) << " " << "5. Minigame" << endl;
    cout << setw(105) << " " << "0. Back" << endl;
}

