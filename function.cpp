#include "function.h"

#include "Word.h"
#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void runProgram() {
    system("cls");
    int choice, temp;
    cout << setw(90) << " " << "The English-Vietnamese Dictionary - Made by CodeLoix Group" << endl;
    cout << setw(105) << " " << "1. Switch Between Dictionaries" << endl;
    cout << setw(105) << " " << "2. Search" << endl;
    cout << setw(105) << " " << "3. Edit Dictionary" << endl;
    cout << setw(105) << " " << "4. View Random Word" << endl;
    cout << setw(105) << " " << "5. Favorite List" << endl;
    cout << setw(105) << " " << "6. Minigame" << endl;
    cout << setw(105) << " " << "7. Exit" << endl;
    cout << setw(105) << " " << "Your choice: ";
    cin >> choice;
    if (choice == 1) {
        system("cls");
        cout << setw(105) << " " << "1. English to English" << endl;
        cout << setw(105) << " " << "2. English to Vietnamese" << endl;
        cout << setw(105) << " " << "3. Vietnamese to English" << endl;
        cout << setw(105) << " " << "4. Back" << endl;
        cout << setw(105) << " " << "Your choice: ";
        cin >> temp;
        if (temp == 4) {
            runProgram();
        }
    }
    else if (choice == 2) {
        system("cls");
        cout << setw(105) << " " << "1. Search by Keyword" << endl;
        cout << setw(105) << " " << "2. Search by Definition" << endl;
        cout << setw(105) << " " << "3. View Search History" << endl;
        cout << setw(105) << " " << "4. Back" << endl;
        cout << setw(105) << " " << "Your choice: ";
        cin >> temp;
        if (temp == 4) {
            runProgram();
        }
    }
    else if (choice == 3) {
        system("cls");
        cout << setw(105) << " " << "1. Add New Word" << endl;
        cout << setw(105) << " " << "2. Edit Definition" << endl;
        cout << setw(105) << " " << "3. Remove Word" << endl;
        cout << setw(105) << " " << "4. Reset Dictionary" << endl;
        cout << setw(105) << " " << "5. Back" << endl;
        cout << setw(105) << " " << "Your choice: ";
        cin >> temp;
        if (temp == 5) {
            runProgram();
        }
    }
    else if (choice == 4) {
        system("cls");

    }
    else if (choice == 5) {
        system("cls");
        cout << setw(105) << " " << "1. View Favorite List" << endl;
        cout << setw(105) << " " << "2. Add Word to Favorite List" << endl;
        cout << setw(105) << " " << "3. Remove Word from Favorite List" << endl;
        cout << setw(105) << " " << "4. Back" << endl;
        cout << setw(105) << " " << "Your choice: ";
        cin >> temp;
        if (temp == 4) {
            runProgram();
        }
    }
    else if (choice == 6) {
        system("cls");
        cout << setw(105) << " " << "1. Guess Word" << endl;
        cout << setw(105) << " " << "2. Guess Meaning" << endl;
        cout << setw(105) << " " << "3. Back" << endl;
        cout << setw(105) << " " << "Your choice: ";
        cin >> temp;
        if (temp == 3) {
            runProgram();
        }
    }
    else if (choice == 7) {
        return;
    }
    else {
        cout << setw(105) << " " << "Invalid input." << endl;
        system("pause");
        runProgram();
    }
}

void saveHistory(vector<string> hisSearch) {
    ofstream fout;
    string filePath = "Data/his.txt";
    fout.open(filePath);
    for (int i = 0; i < int(hisSearch.size()); ++i) {
        fout << hisSearch[i] << endl;
    }
    fout.close();
}

vector<string> loadHistory() {
    ifstream fin;
    vector<string> hisSearch;
    string filePath = "Data/his.txt", temp;
    fin.open(filePath);
    while(!fin.eof()) {
        fin >> temp;
        hisSearch.push_back(temp);
    }
    fin.close();
    return hisSearch;
}

void displayHistory(vector<string> hisSearch) {
    cout << setw(93) << "Search History" << endl;
    for (int i = 0; i < int(hisSearch.size()); ++i) {
        cout << setw(93) << " " << i + 1 << ". " << hisSearch[i] << endl;
    }
}
