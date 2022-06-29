#include "Word.h"


using namespace std;

//Constructor and Destructor

/*Word::Word(string &s) {
    Key = s;
}*/

#define F Type
#define S Exam
#define T Trans

Word::~Word() {
    for (Int_VS_VS &c: typeDefEx) {
        c.S.clear();
        c.T.clear();
    }
    typeDefEx.clear();
}

//Inner Functionsssssssssssssssssssssssssssssssssssssss

void Word::AddType(int Type) {
    for (Int_VS_VS &c: typeDefEx)
        if (c.Type == Type) return;
    VecString _Exam;
    VecString _Trans;
    typeDefEx.push_back({Type, _Exam, _Trans});
}

void Word::AddEx(int Type, string &Ex) {
    for (Int_VS_VS &c: typeDefEx) {
        if (c.F == Type) {
            c.S.push_back(Ex);
            return;
        }
    }
}

void Word::AddTrans(int Type, string &_Trans) {
    for (Int_VS_VS &c: typeDefEx) {
        if (c.F == Type) {
            c.T.push_back(_Trans);
            return;
        }
    }
}

void Word::ShowData(int level, VecString &GetType) {
    if (level >= 1) cout << Key << "\n";
    if (level >= 2) {
        for (Int_VS_VS &c: typeDefEx) {
            cout << "* " + GetTypeString(c.F, GetType) + '\n';
            for (string &s: c.S) cout << " - " + s + '\n';
            for (string &s: c.T) cout << " " + s + ((s != c.T.back()) ? "," : ".\n");
        }
    }
}

//Outer Functionsssssssssssssssssssssssssssssssssssssss

string GetTypeString(int Type, VecString &GetType) {
    if (Type >= int(GetType.size())) return "unknown";
    return GetType[Type];
}

int GetTypeInt(string Type, VecString &GetType) {
    for (int i = 0; i < int(GetType.size()); i++)
            if (Type == GetType[i]) return i;
    return oo;
}

void readData(vector <Word> &vietanh, ifstream &fin, VecString &GetType) {
    while (!fin.eof()) {
        bool flag = false;
        Word toAdd;
        int type_count = 0;
        char prefix;
        string tmp_type;
        Int_VS_VS tmp_typeDefEx;
        while (fin >> prefix) {
          if (prefix == '@') {
            if (flag) {
              toAdd.typeDefEx.push_back(tmp_typeDefEx);
              vietanh.push_back(toAdd);
              type_count = 0;
              tmp_typeDefEx.Type = 0;
              tmp_typeDefEx.Exam.clear();
              tmp_typeDefEx.Trans.clear();
              toAdd.typeDefEx.clear();
            }
            else {
              flag = true;
            }
            getline(fin, toAdd.Key, '\n');
          }
          else if (prefix == '*') {
            ++type_count;
            if (type_count > 1) {
              toAdd.typeDefEx.push_back(tmp_typeDefEx);
              tmp_typeDefEx.Exam.clear();
              tmp_typeDefEx.Trans.clear();
            }

            getline(fin, tmp_type, '\n');
            AddType(tmp_type, GetType);
            tmp_typeDefEx.Type = GetTypeInt(tmp_type, GetType);
          }
          else if (prefix == '-') {
            string tmp_trans;
            getline(fin, tmp_trans, '\n');
            tmp_typeDefEx.Trans.push_back(tmp_trans);
          }
          else if (prefix == '=') {
            string tmp_ex;
            getline(fin, tmp_ex, '\n');
            if (tmp_ex.find("+") != string::npos) {
                stringstream ss(tmp_ex);
                getline(ss, tmp_ex, '+');
                tmp_typeDefEx.Exam.push_back(tmp_ex);
                getline(ss, tmp_ex, '\n' );
                tmp_typeDefEx.Exam.push_back(tmp_ex);
            }
            else {
                tmp_typeDefEx.Exam.push_back(tmp_ex);
            }
          }
        }
        toAdd.typeDefEx.push_back(tmp_typeDefEx);
        vietanh.push_back(toAdd);
    }
}

void readSlang(vector<Word> &Slang, ifstream &fin) {
  while (!fin.eof()) {
    Word to_add;
    string line;
    getline(fin, line, '\n');
    stringstream ss(line);
    getline(ss, to_add.Key, '`');
    string tmp_trans;
    while (ss.good()) {
      getline(ss, tmp_trans, '|');  
      to_add.typeDefEx[0].Trans.push_back(tmp_trans);
    }
    Slang.push_back(to_add);
  }
}


void AddType(string &Type, VecString &GetType) {
    if (GetTypeInt(Type, GetType) == oo) GetType.push_back(Type);
}
