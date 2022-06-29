#include "MainProcess.h"

using namespace std;

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh) {
    string Path = "Data/";
    string AnhVietFile = Path + "anhviet.txt";
    string VietAnhFile = Path + "vietanh.txt";
    string HistoryFile = Path + "his.txt";
    //string AnhAnhFile = "";

    AnhViet.FileInput(AnhVietFile);
    VietAnh.FileInput(VietAnhFile);

}

bool SearchProcessing(HashTable &MainData) {
    SearchMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;



    return 1;
}

bool EditProcessing(HashTable &MainData) {
    EditWordMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;



    return 1;
}

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd() * 1LL * rd() % (h - l + 1);
}

bool RandomWordProcessing(HashTable &MainData) {
    long long location = Rand(0, MainData.N);
    while (MainData.List[location].pHead == nullptr) {
        location = Rand(0,MainData.N);
    }
    string word = MainData.List[location].pHead->data.Key;
    string wordDef = MainData.List[location].pHead->data.typeDefEx[0].Trans[0];
    cout << word << endl;
    cout << wordDef << endl;
    return 0;
}

bool FavouriteProcessing(HashTable &MainData) {
    FavouriteMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;



    return 1;
}

bool MinigameProcessing(HashTable &MainData) {
    MinigameMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;



    return 1;
}

bool ChooseFunctions(HashTable &MainData) {

    ChooseFunctionsMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    if (Command == 1) while (SearchProcessing(MainData));
    if (Command == 2) while (EditProcessing(MainData));
    if (Command == 3) while (RandomWordProcessing(MainData));
    if (Command == 4) while (FavouriteProcessing(MainData));
    if (Command == 5) while (MinigameProcessing(MainData));

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
    HashTable AnhViet("AnhViet", 31, 14071), VietAnh("VietAnh", 31, 14071), AnhAnh("AnhAnh", 31, 14071);
    InitData(AnhViet, VietAnh, AnhAnh);
    while (ChooseDictionary(AnhViet, VietAnh, AnhAnh));
}

