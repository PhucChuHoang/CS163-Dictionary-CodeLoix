#pragma once

#include <iostream>
#include <vector>
#include <fstream>

typedef std::vector <std::string> VecString;
typedef std::pair <int, VecString > IntVecString;

struct Int_VS_VS {
    int Type;
    VecString Exam; //
    VecString Trans; //trans
};

struct Word
{
    std::string Key = "";
    std::vector <Int_VS_VS> typeDefEx;

    //Word(std::string &s);
    ~Word();

    void AddDef(int Def);
    void AddEx(int Def, std::string &Ex);
    void AddTrans(int Def, std::string &Trans);

    void ShowData(int level, std::vector <std::string> &GetDef);
};

std::string GetDefString(int Def, std::vector <std::string> &GetDef);
int GetDefInt(std::string Def, std::vector <std::string> &GetDef);
void readData(std::vector<Word> &vietanh, std::ifstream &fin, std::vector <std::string> &GetDef);
void AddDef(std::string &Def, std::vector <std::string> &GetDef);
