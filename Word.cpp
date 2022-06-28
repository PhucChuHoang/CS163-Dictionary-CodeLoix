#include "Word.h"
#include "Const.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

void Word::AddDef(int Def) {
    for (Int_VS_VS &c: typeDefEx)
        if (c.Type == Def) return;
    VecString _Exam;
    VecString _Trans;
    typeDefEx.push_back({Def, _Exam, _Trans});
}

void Word::AddEx(int Def, string &Ex) {
    for (Int_VS_VS &c: typeDefEx) {
        if (c.F == Def) {
            c.S.push_back(Ex);
            return;
        }
    }
}

void Word::AddTrans(int Def, string &_Trans) {
    for (Int_VS_VS &c: typeDefEx) {
        if (c.F == Def) {
            c.T.push_back(_Trans);
            return;
        }
    }
}

void Word::ShowData(int level, VecString &GetDef) {
    if (level >= 1) cout << Key << "\n";
    if (level >= 2) {
        for (Int_VS_VS &c: typeDefEx) {
            cout << "* " + GetDefString(c.F, GetDef) + '\n';
            for (string &s: c.S) cout << " - " + s + '\n';
            for (string &s: c.T) cout << " " + s + ((s != c.T.back()) ? "," : ".\n");
        }
    }
}

//Outer Functionsssssssssssssssssssssssssssssssssssssss

string GetDefString(int Def, VecString &GetDef) {
    if (Def >= int(GetDef.size())) return "unknown";
    return GetDef[Def];
}

int GetDefInt(string Def, VecString &GetDef) {
    for (int i = 0; i < int(GetDef.size()); i++)
            if (Def == GetDef[i]) return i;
    return oo;
}

void readData(vector <Word> &vietanh, ifstream &fin, VecString &GetDef) {
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
            AddDef(tmp_type, GetDef);
            tmp_typeDefEx.Type = GetDefInt(tmp_type, GetDef);
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


void AddDef(string &Def, VecString &GetDef) {
    if (GetDefInt(Def, GetDef) == oo) GetDef.push_back(Def);
}
