#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;

#include "Word.h"
#include "HashTable.h"

int main() {

    //HashTable VietAnh(31, 14027, GetDefVA); //Init(P, N) (P < N, Better if P and N are prime numbers)

    string VietAnhFilePath = "Data/";
    string VietAnhFileName = "vietanh.txt";

    string VietAnhFile = VietAnhFilePath + VietAnhFileName;

    HashTable VietAnh(31, 14067);
    VietAnh.FileInput(VietAnhFile);

    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    //VietAnh.ShowAllWord();

    while (1) {
        string word;
        getline(cin, word);
        //cin.ignore();
        if (word == "stop") break;
        HashNode* Temp = VietAnh.FindWord(word);
        if (Temp == nullptr) {
            cout << "Cannot found " + word + "!\n";
            continue;
        }
        Temp->data.ShowData(3, VietAnh.GetDef);
        Temp = nullptr;
    }

    /*string AnhVietFilePath = "Data/";
    string AnhVietFileName = "AVdata.txt";

    string AnhVietFile = AnhVietFilePath + AnhVietFileName;

    HashTable AnhViet(3, 7);
    AnhViet.FileInput(AnhVietFile);
    AnhViet.ShowAllWord();*/
    return 0;
}
