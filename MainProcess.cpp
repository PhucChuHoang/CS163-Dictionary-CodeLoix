#include "MainProcess.h"

using namespace std;

void GetData(HashTable &HT) {
    string Path = "Data/";
    string check = Path + "Checker/" + HT.Name + ".txt";
    string Filename = Path;
    ifstream fi(check);
    bool isReset = 0;
    if (fi.good()) {
        fi >> isReset;
    }
    fi.close();
    if (isReset) Filename += "Origin/";
        else Filename += "Save/";
    Filename += HT.Name + ".txt";
    HT.FileInput(Filename, isReset);
    if (isReset) {
        string his = "Data/History/" + HT.Name + ".txt";
        ofstream fho(his);
        fho.close();
    }
}

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &emo, HashTable &slang) {
    GetData(AnhViet);
    GetData(VietAnh);
    GetData(emo);
    GetData(slang);
}

void SaveData(HashTable &AnhViet, HashTable &VietAnh, HashTable &emo, HashTable &slang) {
    AnhViet.SaveHashTable();
    VietAnh.SaveHashTable();
    emo.SaveHashTable();
    slang.SaveHashTable();
}

HashNode *SearchHelper(string &w, HashTable &MainData) {
    system("cls");

    vector <string> SuggestWords = MainData.Prefix.FindWordWithSamePrefix(oo, w);
    if (SuggestWords.empty()) return nullptr;
    sort(SuggestWords.begin(), SuggestWords.end(), [](const string &a, const string &b) {
        return a.size() < b.size();
    });
    gotoxy(0,0);
    cout << "Result: " << endl;
    for (int i = 0; i < (int)(SuggestWords.size()); i++)
        cout << SuggestWords[i] << '\n';
    gotoxy(0,1);
    SetColor(14);
    cout << SuggestWords[0];
    SetColor(7);
    int pos = getChoosing(SuggestWords, 0);
    // if (pos > (int) (SuggestWords.size()) || pos < 1) {
    //     cout << "Invalid input!";
    //     system("pause");
    //     return 1;
    // }

    return MainData.FindWord(SuggestWords[pos - 1]);
}

bool SearchProcessing(HashTable &MainData) {
    vector<string> menu = SearchMenu();
    gotoxy(0,1);
    for (int i = 1; i <= menu.size(); ++i) {
        cout << setw(95) << " " << menu[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << menu[0];
    SetColor(7);
    int Command = getChoosing(menu, 95);

    if (Command == menu.size()) return 0;
    system("cls");
    // Search by keyword
    if (Command == 1) {
        string w;
        cout << "Input word: ";
        cin >> w;
        HashNode *wp = SearchHelper(w, MainData);
        system("cls");
        if (wp == nullptr) {
            cout << "Cannot found !!";
            system("pause");
            return 1;
        }
        wp->data.ShowData(3, MainData.GetType);

        // Save in history
        MainData.History.push_back(wp->data.Key);
        if (MainData.History.size() > 5){
            MainData.History.erase(MainData.History.begin());
        }
        // Save in Favorite
        cout << '\n';
        system("pause");
        system("cls");
        vector<string> favMenu;
        favMenu.push_back("1. Save in Favorite");
        favMenu.push_back("2. Remove from Favorite");
        favMenu.push_back("3. Back");

        gotoxy(0,0);
        cout << "Do you want to: " << endl;
        for (int i = 0; i < favMenu.size(); ++i) {
            cout << favMenu[i] << '\n';
        }
        gotoxy(0,1);
        SetColor(14);
        cout << favMenu[0];
        SetColor(7);
        int currentChoose = 1;
        while(1) {
            char c = _getch();
            if ((int)c == 13) {
                SetColor(7);
                break;
            }
            int prevChoose = currentChoose;
            if ((int)c == -32) {
                char c = _getch();
                if ((int)c == 72) {
                    if (currentChoose != 1) {
                        --currentChoose;
                    }
                }
                else if ((int)c == 80) {
                    if (currentChoose != (int)(favMenu.size())) {
                        ++currentChoose;
                    }
                }
            }
            if (currentChoose != prevChoose) {
                gotoxy(0, prevChoose);
                SetColor(7);
                cout << favMenu[prevChoose-1];
                SetColor(14);
                gotoxy(0, currentChoose);
                cout << favMenu[currentChoose-1];
            }
        }
        gotoxy(0, 4);

        int p = currentChoose;
        int cnt = 0;
        int id = -1;
        for (string &c: MainData.Favorite){
            if (c == wp->data.Key){
                id = cnt;
                break;
            }
            cnt++;
        }
        if (p == 1){
            if (id == -1) {
                MainData.Favorite.push_back(wp->data.Key);
                cout << "Save in Favorite successfully!" << '\n';
            }     
            else cout << "You have added this word into favorite!" << '\n';
            system("pause");
        }
        if (p == 2){
            if (id == -1){
                cout << "You have not add this word into favorite!" << '\n';
            }
            else{
                MainData.Favorite.erase(MainData.Favorite.begin() + id);
            }
            system("pause");
        }
    }
    //Show search History
    if (Command == 2){
        MainData.DisplayHistory();
        vector<string> askMenu;
        askMenu.push_back("1. Clear History");
        askMenu.push_back("2. Back");
        gotoxy(0, MainData.History.size() + 2);
        for (int i = 0; i < askMenu.size(); ++i) {
            cout << askMenu[i] << '\n';
        }
        gotoxy(0, MainData.History.size() + 2);
        SetColor(14);
        cout << askMenu[0];
        SetColor(7);
        int currentChoose = 1;
        while(1) {
            char c = _getch();
            if ((int)c == 13) {
                SetColor(7);
                break;
            }
            int prevChoose = currentChoose;
            if ((int)c == -32) {
                char c = _getch();
                if ((int)c == 72) {
                    if (currentChoose != 1) {
                        --currentChoose;
                    }
                }
                else if ((int)c == 80) {
                    if (currentChoose != (int)(askMenu.size())) {
                        ++currentChoose;
                    }
                }
            }
            if (currentChoose != prevChoose) {
                gotoxy(0, prevChoose + MainData.History.size() + 1);
                SetColor(7);
                cout << askMenu[prevChoose-1];
                SetColor(14);
                gotoxy(0, currentChoose + MainData.History.size() + 1);
                cout << askMenu[currentChoose-1];
            }
        }
        gotoxy(0, MainData.History.size() + 3);
        int p = currentChoose;
        if (p == 1){
            MainData.History.clear();
            MainData.SaveHistory();
        }
        else {
            return 1;
        }
    }
    return 1;
}

bool EditProcessing(HashTable &MainData) {
    vector<string> wordMenu = EditWordMenu();
    gotoxy(0,1);
    for (int i = 1; i <= wordMenu.size(); ++i) {
        cout << setw(95) << " " << wordMenu[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << wordMenu[0];
    SetColor(7);
    int Command = getChoosing(wordMenu, 95);

    if (Command == wordMenu.size()) return 0;
    system("cls");
    //Add new word
    if (Command == 1){
        cout << "Input the word you want to add: ";
        Word to_add;
        getline(cin, to_add.Key);
        HashNode* to_add_word = MainData.FindWord(to_add.Key);
        if (!to_add_word){
            MainData.InsertNewWord(to_add);
            while(EditWordDefProcessing(MainData, to_add.Key));
        }
        else{
            vector<string> askMenu;
            askMenu.push_back("1. Edit definition");
            askMenu.push_back("2. Add another word");
            askMenu.push_back("3. Back");
            gotoxy(0,2);
            cout << "This word already exists in dictionary" << '\n';
            for (int i = 0; i < askMenu.size(); ++i) {
                cout << askMenu[i] << '\n';
            }
            gotoxy(0,3);
            SetColor(14);
            cout << askMenu[0];
            SetColor(7);
            int currentChoose = 1;
            while(1) {
                char c = _getch();
                if ((int)c == 13) {
                    SetColor(7);
                    break;
                }
                int prevChoose = currentChoose;
                if ((int)c == -32) {
                    char c = _getch();
                    if ((int)c == 72) {
                        if (currentChoose != 1) {
                            --currentChoose;
                        }
                    }
                    else if ((int)c == 80) {
                        if (currentChoose != (int)(askMenu.size())) {
                            ++currentChoose;
                        }
                    }
                }
                if (currentChoose != prevChoose) {
                    gotoxy(0, prevChoose + 2);
                    SetColor(7);
                    cout << askMenu[prevChoose-1];
                    SetColor(14);
                    gotoxy(0, currentChoose + 2);
                    cout << askMenu[currentChoose-1];
                }
            }
            gotoxy(0, 10);
            int p = currentChoose;
            if (p == 1){
                while (EditWordDefProcessing(MainData, to_add.Key));
            }
            if (p == 2){
                return 1;
            }
            else return 0;
        }
    }

    // Edit definition
    if (Command == 2){
        cout << "Input the word you want to edit: \n";
        string to_edit;
        getline(cin, to_edit);
        HashNode *wp = SearchHelper(to_edit, MainData);
        to_edit = wp->data.Key;
        wp = nullptr;
        while (EditWordDefProcessing(MainData, to_edit));
    }

    // Remove word
    if (Command == 3){
        cout << "Input the word you want to remove: ";
        string to_remove;
        getline(cin, to_remove);
        HashNode *wp = SearchHelper(to_remove, MainData);
        to_remove = wp->data.Key;
        wp = nullptr;
        MainData.DeleteWord(to_remove);
    }

    // Reset Dictionary
    if (Command == 4){
        string Filename = "Data/Checker/" + MainData.Name + ".txt";
        ofstream fo;
        fo.open(Filename);
        fo << 1 << '\n';
        fo.close();

        cout << "Please restart your app :>\n";
        system("pause");
        exit(0);
    }

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
    cout << setw(106 - word.length()/2) << " " << word << '\n';
    cout << setw(106 - wordDef.length()/2) << " " << wordDef << '\n' << '\n';
    MainData.History.push_back(word);
    if (MainData.History.size() > 5){
        MainData.History.erase(MainData.History.begin());
    }
    MainData.SaveHistory();
    vector<string> addMenu;
    addMenu.push_back("1. Add to favorite list");
    addMenu.push_back("2. Back");
    gotoxy(0,4);
    for (int i = 1; i <= addMenu.size(); ++i) {
        cout << setw(95) << " " << addMenu[i - 1] << '\n';
    }
    gotoxy(0,4);
    SetColor(14);
    cout << setw(95) << " " << addMenu[0];
    SetColor(7);
    int currentChoose = 1;
    while(1) {
        char c = _getch();
        if ((int)c == 13) {
            SetColor(7);
            break;
        }
        int prevChoose = currentChoose;
        if ((int)c == -32) {
            char c = _getch();
            if ((int)c == 72) {
                if (currentChoose != 1) {
                    --currentChoose;
                }
            }
            else if ((int)c == 80) {
                if (currentChoose != (int)(addMenu.size())) {
                    ++currentChoose;
                }
            }
        }
        if (currentChoose != prevChoose) {
            gotoxy(95, prevChoose + 3);
            SetColor(7);
            cout << addMenu[prevChoose-1];
            SetColor(14);
            gotoxy(95, currentChoose + 3);
            cout << addMenu[currentChoose-1];
        }
    }
    if (currentChoose == 2) {
        return 0;
    }

    int cnt = 0;
    int id = -1;
    for (string &c: MainData.Favorite){
        if (c == word){
            id = cnt;
            break;
        }
        cnt++;
    }
    if (currentChoose == 1){
        if (id == -1) MainData.Favorite.push_back(word);
        else cout << "You have added this word into favorite!" << '\n';
    }
    MainData.SaveFavorite();
    gotoxy(95,6);
    system("pause");
    return 0;
}

bool FavouriteProcessing(HashTable &MainData) {
    vector<string> favouriteMenu = FavouriteMenu();
    gotoxy(0,1);
    for (int i = 1; i <= favouriteMenu.size(); ++i) {
        cout << setw(95) << " " << favouriteMenu[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << favouriteMenu[0];
    SetColor(7);
    int Command = getChoosing(favouriteMenu, 95);

    if (Command == favouriteMenu.size()) return 0;

    system("cls");
    // Show Favorite list
    if (Command == 1){
        MainData.DisplayFavorite();
        system("pause");
    }

    // Remove from Favorite list
    if (Command == 2){
        MainData.DisplayFavorite();
        cout << "Remove a word from a list.";
        int p = GetCommand();
        if (p < 1 || p > MainData.Favorite.size()){
            cout << "Invalid input!";
            system("pause");
            return 1;
        }
        MainData.Favorite.erase(MainData.Favorite.begin() + p - 1);
        MainData.SaveFavorite();
    }

    // Clear Favorite list
    if (Command == 3){
        MainData.Favorite.clear();
        MainData.SaveFavorite();
    }
    return 1;
}

bool EditWordDefProcessing(HashTable &Hashdata, string to_edit) {
    vector<string> defMenu = EditWordDefMenu();
    gotoxy(0,1);
    for (int i = 1; i <= defMenu.size(); ++i) {
        cout << setw(95) << " " << defMenu[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << defMenu[0];
    SetColor(7);
    int Command = getChoosing(defMenu, 95);

    if (Command == defMenu.size()) return 0;

    HashNode* to_edit_word = Hashdata.FindWord(to_edit);
    if (!to_edit_word) {
        cout << setw(95) << " " << "Word doesn't exist" << '\n';
        system("pause");
        return 0;
    }

    string tmp_type;
    string tmp_def;
    // cin.ignore(1000,'\n');
    system("cls");
    cout << setw(95) << " " << "Input type of the new definition: ";
    getline(cin, tmp_type);
    AddType(tmp_type, Hashdata.GetType);
    cout << setw(95) << " " << "Input the new definition: ";
    getline(cin, tmp_def);
    int int_type = GetTypeInt(tmp_type, Hashdata.GetType);

    // change definition (clear + update)
    if (Command == 1) {
        to_edit_word->data.typeDefEx.clear();
        cout << setw(95) << " " << "The word's definition has been changed." << '\n';
    }

    // add definition
    if (Command == 2) {
        cout << setw(95) << " " << "New definition has been added." << '\n';
    }

    to_edit_word->data.AddType(int_type);
    to_edit_word->data.AddTrans(int_type, tmp_def);
    system("pause");
    return 1;

}

bool checkDif(long long check1, long long check2, long long check3, long long check4) {
    return (check1 != check2 && check1 != check3 && check1 != check4);
}

bool MinigameProcessing(HashTable &MainData) {
    vector<string> gameMenu = MinigameMenu();
    gotoxy(0,1);
    for (int i = 1; i <= gameMenu.size(); ++i) {
        cout << setw(95) << " " << gameMenu[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << gameMenu[0];
    SetColor(7);
    int Command = getChoosing(gameMenu, 95);

    if (Command == gameMenu.size()) return 0;

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

    int currentChoose = 1;
    vector<string> ans;
    if (Command == 1) {
        cout << "What is the meaning of \"" << wordAns << "\"?" << '\n';
        for (int i = 1; i <= 4; ++i) {
            if (i == ansIndex) {
                ans.push_back(defAns);
                continue;
            }
            else {
                if (!used1) {
                    ans.push_back(MainData.List[fake1].pHead->data.typeDefEx[0].Trans[0]);
                    used1 = true;
                }
                else if (!used2) {
                    ans.push_back(MainData.List[fake2].pHead->data.typeDefEx[0].Trans[0]);
                    used2 = true;
                }
                else {
                    ans.push_back(MainData.List[fake3].pHead->data.typeDefEx[0].Trans[0]);
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            cout << ans[i] << '\n';
        }
    }
    else if (Command == 2) {
        cout << "What is the word for \"" << defAns << "\"?" << '\n';
        for (int i = 1; i <= 4; ++i) {
            if (i == ansIndex) {
                ans.push_back(wordAns);
                continue;
            }
            else {
                if (!used1) {
                    ans.push_back(MainData.List[fake1].pHead->data.Key);
                    used1 = true;
                }
                else if (!used2) {
                    ans.push_back(MainData.List[fake2].pHead->data.Key);
                    used2 = true;
                }
                else {
                    ans.push_back(MainData.List[fake3].pHead->data.Key);
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            cout << ans[i] << '\n';
        }
    }
    gotoxy(0, currentChoose);
    SetColor(14);
    cout << ans[currentChoose-1];
    currentChoose = getChoosing(ans, 0);
    gotoxy(0,ans.size()+2);
    SetColor(7);
    if (currentChoose == ansIndex) cout << "The answer is Correct!!!" << '\n';
    else cout << "Incorrect, Good luck next time." << '\n';
    system("pause");

    return 1;
}

bool ChooseFunctions(HashTable &MainData) {
    vector<string> data = ChooseFunctionsMenu();
    gotoxy(0,1);
    for (int i = 1; i <= data.size(); ++i) {
        cout << setw(95) << " " << data[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << data[0];
    SetColor(7);
    int Command = getChoosing(data, 95);

    if (Command == data.size()) return 0;

    if (Command == 1) while (SearchProcessing(MainData));
    if (Command == 2) while (EditProcessing(MainData));
    if (Command == 3) while (RandomWordProcessing(MainData));
    if (Command == 4) while (FavouriteProcessing(MainData));
    if (Command == 5) while (MinigameProcessing(MainData));
    return 1;
}

bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &emotional, HashTable& slang) {
    vector<string> dict = ChooseDictionaryMenu();
    cout << setw(98) << " " << "WELCOME TO CODELOIX DICTIONARY" << '\n';
    gotoxy(0,1);
    for (int i = 1; i <= dict.size(); ++i) {
        cout << setw(95) << " " << dict[i - 1] << '\n';
    }
    gotoxy(0,1);
    SetColor(14);
    cout << setw(95) << " " << dict[0];
    SetColor(7);
    int Command = getChoosing(dict, 95);

    if (Command == dict.size()) return 0;

    if (Command == 1) while (ChooseFunctions(AnhViet));
    if (Command == 2) while (ChooseFunctions(VietAnh));
    if (Command == 3) while (ChooseFunctions(emotional));
    if (Command == 4) while (ChooseFunctions(slang));

    return 1;
}

void MainProcess() {
    HashTable AnhViet("AnhViet", 31, 14071), VietAnh("VietAnh", 31, 14071), emotional("emotional", 131, 14071), slang("slang", 131, 14701);
    InitData(AnhViet, VietAnh, emotional, slang);
    while (ChooseDictionary(AnhViet, VietAnh, emotional, slang));
    SaveData(AnhViet, VietAnh, emotional, slang);
}
