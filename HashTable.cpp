#include "HashTable.h"
#include <algorithm>
using namespace std;

HashNode::HashNode(string &_data) {
    data.Key = _data;
}

HashTable::HashTable(string _Name, int _P, int _N) {
    Name = _Name;
    P = _P;
    N = _N;
    List = new HashLinkedList[N];
    GetType.clear();
    History.clear();
    LoadHistory();
}

HashTable::~HashTable() {

    for (int i = 0; i < N; i++) {
        HashNode *pD = nullptr;
        List[i].pTail = nullptr;
        while (List[i].pHead) {
            pD = List[i].pHead;
            List[i].pHead = List[i].pHead->pNext;
            delete pD;
            pD = nullptr;
        }
    }


    GetType.clear();
    SaveHistory();
    History.clear();
    delete [] List;
}

int HashTable::GetHash(string &s) {

    int res = 0, p = P;
    for (char &c: s) {
        res = (res + c * p) % N;
        p = (p * P) % N;
    }
    return res;
}

void HashTable::InsertNewString(string &s) {
    int location = GetHash(s);
    if (FindWord(s) != nullptr) return;
    Prefix.Insert(s);
    if (List[location].pHead == nullptr) {
        HashNode* temp = new HashNode(s);
        List[location].pHead = List[location].pTail = temp;
    }
    else {
        HashNode* temp = new HashNode(s);
        List[location].pTail->pNext = temp;
        List[location].pTail = List[location].pTail->pNext;
    }
}

void HashTable::InsertNewWord(Word &W) {
    InsertNewString(W.Key);
    HashNode* Temp = FindWord(W.Key);

    for (Int_VS_VS &c: W.typeDefEx) {
        Temp->data.AddType(c.Type);
        for (string &s: c.Exam) Temp->data.AddEx(c.Type, s);
        for (string &s: c.Trans) Temp->data.AddTrans(c.Type, s);
    }
}

void HashTable::displayChain() {
    for (int i = 0; i < N; ++i) {
        cout << "Key" << " " << i << " :";
        if (List[i].pHead != nullptr) {
            HashNode* current = List[i].pHead;
            while (current != nullptr) {
                cout << current->data.Key << "      ";
                current = current->pNext;
            }
        }
        cout << '\n';
    }
}

void HashTable::DeleteWord(string &s) {
    int location = GetHash(s);
    if (List[location].pHead == nullptr){
        cout << "Word doesn't exist" << endl;
        system("pause");
        return;
    }

    Prefix.Delete(s);
    if (List[location].pHead->data.Key == s) {
        HashNode* pD = List[location].pHead;
        if (List[location].pTail->data.Key == s) List[location].pTail = nullptr;
        List[location].pHead = List[location].pHead->pNext;
        delete pD;
        pD = nullptr;
    }
    else {
        HashNode* Cur = List[location].pHead;
        while (Cur->pNext) {

            if (Cur->pNext->data.Key == s) {
                HashNode* pD = Cur->pNext;
                if (Cur->pNext == List[location].pTail) List[location].pTail = Cur;
                Cur->pNext = Cur->pNext->pNext;
                delete pD;
                pD = nullptr;
                return;
            }

            Cur = Cur->pNext;
        }
        cout << "Word doesn't exist" << endl;
        system("pause");
    }

}

HashNode* HashTable::FindWord(string &s) {
    int HashKey = GetHash(s);

    HashNode* Cur = List[HashKey].pHead;

    while (Cur) {
        if (Cur->data.Key == s) return Cur;
        Cur = Cur->pNext;
    }

    return nullptr;
}

void HashTable::FileInput(string &Filename, bool isReset) {

    ifstream fi(Filename);
    vector <Word> Temp;
    string tmp = "";
    for (int i = (int)Filename.size() - 1; i >= 0; i--){
        if (Filename[i] =='/') break;
        tmp += Filename[i];
    }
    reverse(tmp.begin(), tmp.end());
    if (fi.good()) {
        Temp.clear();
        readData(Temp, fi, GetType);
    }
    fi.close();
    for (Word &c: Temp) InsertNewWord(c);
    Temp.clear();

    if (!isReset) {
        LoadFavorite();
        LoadHistory();
    }
}

void HashTable::ShowAllWord() {
    for (int i = 0; i < N; ++i) {
        if (List[i].pHead != nullptr) {
            HashNode* current = List[i].pHead;
            while (current != nullptr) {
                current->data.ShowData(3, GetType);
                current = current->pNext;
            }
        }
        cout << '\n';
    }
}

void HashTable::SaveHashTable() {
    string Filename = "Data/Save/" + Name + ".txt";
    string Filecheck = "Data/Checker/" + Name + ".txt";

    ofstream fco(Filecheck);
    fco << 0;
    fco.close();

    ofstream fo(Filename);

    for (int i = 0; i < N; i++) {
        HashNode *Cur = List[i].pHead;
        while (Cur) {

            Word Temp = Cur->data;

            fo << "@" + Temp.Key << '\n';

            for (Int_VS_VS &c: Temp.typeDefEx) {
                fo << "*" + GetTypeString(c.Type, GetType) << '\n';
                for (string &T: c.Trans) fo << "-" + T << '\n';
                for (string &E: c.Exam) fo << "=" + E << '\n';
            }

            Cur = Cur->pNext;
            fo << '\n';
        }
    }

    fo.close();

    SaveHistory();
    SaveFavorite();
}

//History dev

void HashTable::SaveHistory() {
    ofstream fout;
    string filePath = "Data/History/" + Name + ".txt";
    fout.open(filePath);
    for (string &c: History) fout << c << '\n';
    fout.close();
}

void HashTable::LoadHistory() {
    ifstream fin;
    string filePath = "Data/History/" + Name + ".txt", temp;
    fin.open(filePath);
    if (fin.is_open()) {
        while(!fin.eof()) {
            getline(fin, temp);
            History.push_back(temp);
        }
        History.pop_back();
        fin.close();
    }
    return;
}

void HashTable::DisplayHistory() {
    if (History.size() == 0) {
        cout << setw(93) << " " << "You haven't searched anything!" << '\n';
        return;
    }
    cout << setw(107) << "Search History" << '\n';
    int cnt = 0;
    for (string &c: History) cout << setw(93) << " " << (cnt++) << ". " << c << '\n';
}

//Favorite dev

void HashTable::SaveFavorite() {
    ofstream fout;
    string filePath = "Data/Favorite/" + Name + ".txt";
    fout.open(filePath);
    for (string &c: Favorite) fout << c << '\n';
    fout.close();
}

void HashTable::LoadFavorite() {
    ifstream fin;
    string filePath = "Data/Favorite/" + Name + ".txt", temp;
    fin.open(filePath);
    if (fin.is_open()) {
        while(!fin.eof()) {
            getline(fin, temp);
            Favorite.push_back(temp);
        }
        Favorite.pop_back();
        fin.close();
    }
    return;
}

void HashTable::DisplayFavorite() {
    cout << setw(106) << "Favorite list" << '\n';
    int cnt = 0;
    for (string &c: Favorite) cout << setw(93) << " " << (cnt++) << ". " << c << '\n';
}


