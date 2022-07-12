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

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang) {
    GetData(AnhViet);
    GetData(VietAnh);
    // GetData(emo);
    // GetData(slang);
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
            cout << "Can't find!";
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
    system("cls");
    HashTable Fav("Fav", 31, 14071);
    string Filename = "Data/Favorite/" + MainData.Name + ".txt";
    Fav.FileInput(Filename);
    // Show list
    if (Command == 1){
        
    }
    // Add word to the list
    if (Command == 2){

    }

    // Delete word from the list
    if (Command == 3){

    }

    return 1;
}
bool EditWordDefProcessing(HashTable &data, string to_edit) {
    EditWordDefMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    HashNode* to_edit_word = data.FindWord(to_edit);
    if (!to_edit_word) {
        cout << setw(95) << " " << "Word doesn't exist" << endl;
        return 0;
    }

    string tmp_type;
    string tmp_def;
    cout << setw(95) << " " << "Input type of the new definition: ";
    getline(cin, tmp_type);
    AddType(tmp_type, data.GetType);
    cout << setw(95) << " " << "Input the new definition: ";
    getline(cin, tmp_def);
    int int_type = GetTypeInt(tmp_type, data.GetType);

    // change definition (clear + update)
    if (Command == 1) {
        to_edit_word->data.typeDefEx.clear();
        cout << setw(95) << " " << "The word's definition has been changed." << endl;
    }

    // add definition
    if (Command == 2) {
        cout << setw(95) << " " << "New definition has been added" << endl;
    }

    to_edit_word->data.AddType(int_type);
    to_edit_word->data.AddTrans(int_type, tmp_def);
    return 1;

}

bool checkDif(long long check1, long long check2, long long check3, long long check4) {
    return check1 != check2 && check1 != check3 && check1 != check4;
}

bool MinigameProcessing(HashTable &MainData) {
    MinigameMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    system("cls");
    long long location = Rand(0, MainData.N-1);
    long long fake1 = Rand(0, MainData.N-1), fake2 = Rand(0, MainData.N-1), fake3 = Rand(0, MainData.N-1);
    while ((location < 0) || (MainData.List[location].pHead) == nullptr || (MainData.List[location].pHead->data.typeDefEx[0].Trans.empty())) {
        location = Rand(0, MainData.N-1);
    }
    while ((fake1 < 0) || !checkDif(fake1, location, fake2, fake3) || (MainData.List[fake1].pHead) == nullptr || (MainData.List[fake1].pHead->data.typeDefEx[0].Trans.empty())) {
        fake1 = Rand(0, MainData.N-1);
    }
    while ((fake2 < 0) || !checkDif(fake2, location, fake1, fake3) || (MainData.List[fake2].pHead) == nullptr || (MainData.List[fake2].pHead->data.typeDefEx[0].Trans.empty())) {
        fake2 = Rand(0, MainData.N-1);
    }
    while ((fake3 < 0) || !checkDif(fake3, location, fake1, fake2) || (MainData.List[fake3].pHead) == nullptr || (MainData.List[fake3].pHead->data.typeDefEx[0].Trans.empty())) {
        fake3 = Rand(0, MainData.N-1);
    }
    string wordAns = MainData.List[location].pHead->data.Key;
    string defAns = MainData.List[location].pHead->data.typeDefEx[0].Trans[0];
    int ansIndex = Rand(1,4);
    bool used1 = false, used2 = false;

    if (Command == 1) {
        cout << "What is the meaning of \"" << wordAns << "\"?" << endl;
        for (int i = 1; i <= 4; ++i) {
            if (i == ansIndex) {
                cout << i <<". " << defAns << endl;
                continue;
            }
            else {
                if (!used1) {
                    cout << i << ". " << MainData.List[fake1].pHead->data.typeDefEx[0].Trans[0] << endl;
                    used1 = true;
                }
                else if (!used2) {
                    cout << i << ". " << MainData.List[fake2].pHead->data.typeDefEx[0].Trans[0] << endl;
                    used2 = true;
                }
                else {
                    cout << i << ". " << MainData.List[fake3].pHead->data.typeDefEx[0].Trans[0] << endl;
                }
            }
        }
    }
    else if (Command == 2) {
        cout << "What is the word for \"" << defAns << "\"?" << endl;
        for (int i = 1; i <= 4; ++i) {
            if (i == ansIndex) {
                cout << i <<". " << wordAns << endl;
                continue;
            }
            else {
                if (!used1) {
                    cout << i << ". " << MainData.List[fake1].pHead->data.Key << endl;
                    used1 = true;
                }
                else if (!used2) {
                    cout << i << ". " << MainData.List[fake2].pHead->data.Key << endl;
                    used2 = true;
                }
                else {
                    cout << i << ". " << MainData.List[fake3].pHead->data.Key << endl;
                }
            }
        }
    }

    int res = GetCommand();
    if (res == ansIndex) cout << "Correct" << endl;
    else cout << "Incorrect" << endl;
    system("pause");

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

bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emotional, HashTable& slang) {

    ChooseDictionaryMenu();
    int Command = GetCommand();

    if (Command == 0) return 0;

    if (Command == 1) while (ChooseFunctions(AnhViet));
    if (Command == 2) while (ChooseFunctions(VietAnh));
    if (Command == 3) while (ChooseFunctions(AnhAnh));
    if (Command == 4) while (ChooseFunctions(emotional));
    if (Command == 5) while (ChooseFunctions(slang));

    return 1;
}

void MainProcess() {
    HashTable AnhViet("AnhViet", 31, 14071), VietAnh("VietAnh", 31, 14071), AnhAnh("AnhAnh", 31, 14071), emotional("emotional", 31, 14071), slang("emotional", 31, 14701);
    InitData(AnhViet, VietAnh, AnhAnh, emotional, slang);
    while (ChooseDictionary(AnhViet, VietAnh, AnhAnh, emotional, slang));
}

