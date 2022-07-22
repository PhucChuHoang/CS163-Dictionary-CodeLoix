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

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang) {
    GetData(AnhViet);
    GetData(VietAnh);
    GetData(emo);
    GetData(slang);
}

void SaveData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang) {
    AnhViet.SaveHashTable();
    VietAnh.SaveHashTable();
    emo.SaveHashTable();
    slang.SaveHashTable();
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
        system("cls");
        string w;
        cout << "Input word: ";
        cin >> w;
        vector <string> SuggestWords = MainData.Prefix.FindWordWithSamePrefix(10, w);
        if (SuggestWords.empty()) {
            cout << "Cannot found!";
            system("pause");
            return 1;
        }
        for (int i = 0; i < (int)(SuggestWords.size()); i++)
            cout << i + 1 << ". " << SuggestWords[i] << '\n';
        int pos = GetCommand();
        if (pos > (int) (SuggestWords.size()) || pos < 1) {
            cout << "Invalid input!";
            system("pause");
            return 1;
        }

        HashNode *wp = MainData.FindWord(SuggestWords[pos - 1]);
        wp->data.ShowData(3, MainData.GetType);

        // Save in history
        MainData.History.push_back(wp->data.Key);
        if (MainData.History.size() > 5){
            MainData.History.erase(MainData.History.begin());
        }
        // Save in Favorite
        cout << '\n';
        cout << "1. Save in Favorite" << '\n';
        cout << "2. Remove from Favorite" << '\n';
        cout << "0. Back" << '\n';

        int p = GetCommand();
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
            if (id == -1)
            MainData.Favorite.push_back(wp->data.Key);
            else cout << "You have added this word into favorite!" << '\n';
        }
        if (p == 2){
            if (id == -1){
                cout << "You have not add this word into favorite!" << '\n';
            }
            else{
                MainData.Favorite.erase(MainData.Favorite.begin() + id);
            }
        }
        system("pause");
    }

    // Search by definition
    if (Command == 2){

    }

    //Show search History
    if (Command == 3){
        MainData.DisplayHistory();
        cout << '\n' << "1. Clear History" << '\n';
        cout << "0. Back" << '\n';
        int p = GetCommand();
        if (p == 1){
            MainData.History.clear();
            MainData.SaveHistory();
        }
        system("pause");
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
        cin >> to_add.Key;
        HashNode* to_add_word = MainData.FindWord(to_add.Key);
        if (!to_add_word){
            MainData.InsertNewWord(to_add);
            while(EditWordDefProcessing(MainData, to_add.Key));
        }
        else{
            cout << "This word already exists in dictionary" << '\n';
            cout << "1. Edit definition" << '\n';
            cout << "2. Add another word" << '\n';
            cout << "0. Back" << '\n';
            int p  = GetCommand();
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
        cout << "Input the word you want to edit: ";
        string to_edit;
        cin.ignore();
        getline(cin, to_edit);
        while (EditWordDefProcessing(MainData, to_edit));
    }

    // Remove word
    if (Command == 3){
        cout << "Input the word you want to remove: ";
        string to_remove;
        cin.ignore();
        getline(cin, to_remove);
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
    cout << "1. Add to favorite list" << '\n';
    cout << "0. Back" << '\n';
    int p = GetCommand();
    int cnt = 0;
    int id = -1;
    for (string &c: MainData.Favorite){
        if (c == word){
            id = cnt;
            break;
        }
        cnt++;
    }
    if (p == 1){
        if (id == -1) MainData.Favorite.push_back(word);
        else cout << "You have added this word into favorite!" << '\n';
    }
    MainData.SaveFavorite();
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

bool EditWordDefProcessing(HashTable &data, string to_edit) {
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

    HashNode* to_edit_word = data.FindWord(to_edit);
    if (!to_edit_word) {
        cout << setw(95) << " " << "Word doesn't exist" << '\n';
        system("pause");
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
        cout << setw(95) << " " << "The word's definition has been changed." << '\n';
    }

    // add definition
    if (Command == 2) {
        cout << setw(95) << " " << "New definition has been added" << '\n';
    }

    to_edit_word->data.AddType(int_type);
    to_edit_word->data.AddTrans(int_type, tmp_def);
    system("pause");
    return 1;

}

bool checkDif(long long check1, long long check2, long long check3, long long check4) {
    return check1 != check2 && check1 != check3 && check1 != check4;
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
    getChoosing(ans, 0);
    gotoxy(0,ans.size()+1);
    SetColor(7);
    if (currentChoose == ansIndex) cout << "Correct" << '\n';
    else cout << "Incorrect" << '\n';
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

bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emotional, HashTable& slang) {
    vector<string> dict = ChooseDictionaryMenu();
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
    if (Command == 3) while (ChooseFunctions(AnhAnh));
    if (Command == 4) while (ChooseFunctions(emotional));
    if (Command == 5) while (ChooseFunctions(slang));

    return 1;
}

void MainProcess() {
    HashTable AnhViet("AnhViet", 31, 14071), VietAnh("VietAnh", 31, 14071), AnhAnh("AnhAnh", 31, 14071), emotional("emotional", 131, 14071), slang("slang", 131, 14701);
    InitData(AnhViet, VietAnh, AnhAnh, emotional, slang);
    SaveData(AnhViet, VietAnh, AnhAnh, emotional, slang);
    while (ChooseDictionary(AnhViet, VietAnh, AnhAnh, emotional, slang));
}
