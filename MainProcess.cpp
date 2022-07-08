#include "MainProcess.h"

using namespace std;

void GetData(HashTable &HT) {
    string Path = "Data/";
    string check = Path + "Checker/" + HT.Name + ".txt";
    string Filename = Path;
    ifstream fi(check);
    int isReset;
    fi >> isReset;
    fi.close();
    if (isReset) Filename += "Origin/";
        else Filename += "Save/";
    Filename += HT.Name + ".txt";
    HT.FileInput(Filename);
    if (isReset) {
        string his = "Data/History/" + HT.Name + ".txt";
        ofstream fho(his);
        fho.close();
    }
    HT.LoadHistory();
}

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh) {
    GetData(AnhViet);
    GetData(VietAnh);
}

bool SearchProcessing(HashTable &MainData) {
    SearchMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    if (Command == 1) {
        system("cls");
        string w;
        cout << "Input word: ";
        cin >> w;
        vector <string> SuggestWords = MainData.Prefix.FindWordWithSamePrefix(10, w);
        if (SuggestWords.empty()) {
            cout << "Ko tim thay!";
            system("pause");
            return 1;
        }
        for (int i = 0; i < (int)(SuggestWords.size()); i++)
            cout << i + 1 << ". " << SuggestWords[i] << '\n';
        int pos = GetCommand();
        if (pos >= (int) (SuggestWords.size()) || pos < 1) {
            cout << "Invalid input!";
            system("pause");
            return 1;
        }

        HashNode *wp = MainData.FindWord(SuggestWords[pos - 1]);
        wp->data.ShowData(3, MainData.GetType);
        system("pause");
    }

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
    system("cls");
    long long location = Rand(0, MainData.N-1);
    while ((location < 0) || (MainData.List[location].pHead) == nullptr || (MainData.List[location].pHead->data.typeDefEx[0].Trans.empty())) {
        location = Rand(0, MainData.N-1);
    }
    string word = MainData.List[location].pHead->data.Key;
    string wordDef = MainData.List[location].pHead->data.typeDefEx[0].Trans[0];
    cout << setw(106 - word.length()/2) << " " << word << endl;
    cout << setw(106 - wordDef.length()/2) << " " << wordDef << endl;
    system("pause");
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

