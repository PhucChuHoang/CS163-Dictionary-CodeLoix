#pragma once

#include "Const.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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

    void AddType(int Type);
    void AddEx(int Type, std::string &Ex);
    void AddTrans(int Type, std::string &Trans);

    void ShowData(int level, std::vector <std::string> &GetType);
};

std::string GetTypeString(int Type, std::vector <std::string> &GetType);
int GetTypeInt(std::string Type, std::vector <std::string> &GetType);
void readData(std::vector<Word> &vietanh, std::ifstream &fin, std::vector <std::string> &GetType);
void AddType(std::string &Type, std::vector <std::string> &GetType);
