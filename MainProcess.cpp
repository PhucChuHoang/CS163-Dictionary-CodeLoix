#include "MainProcess.h"

using namespace std;

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh) {
    string Path = "Data/";
    string AnhVietFile = Path + "anhviet.txt";
    string VietAnhFile = Path + "vietanh.txt";
    //string AnhAnhFile = "";

    AnhViet.FileInput(AnhVietFile);
    VietAnh.FileInput(VietAnhFile);
}

bool ChooseFunctions(HashTable &MainData) {

    ChooseFunctionsMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;



    return 1;
}

bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh) {

    ChooseDictionaryMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    if (Command == 1) while (ChooseFunctions(AnhViet));
    if (Command == 2) while (ChooseFunctions(VietAnh));
    if (Command == 3) while (ChooseFunctions(AnhAnh));

    return 1;
}

void MainProcess() {
    HashTable AnhViet(31, 14071), VietAnh(31, 14071), AnhAnh(31, 14071);
    InitData(AnhViet, VietAnh, AnhAnh);
    while (ChooseDictionary(AnhViet, VietAnh, AnhAnh));
}

