#pragma once

#include "Word.h"
#include "Const.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

struct HashNode {
    Word data;
    HashNode* pNext = nullptr;

    HashNode (std::string &_data);
};

struct HashLinkedList {
    HashNode* pHead = nullptr;
    HashNode* pTail = nullptr;
};

struct HashTable {
    std::string Name;
    int P, N;
    HashLinkedList *List;
    std::vector <std::string> GetType;
    std::vector <std::string> History;

    HashTable(std::string Name, int _P, int _N);
    ~HashTable();

    int GetHash(std::string &s);
    void InsertNewString(std::string &s);
    void InsertNewWord(Word &W);

    void displayChain();
    void DeleteWord(std::string &s);
    HashNode* FindWord(std::string &s);

    void FileInput(std::string &Filename);
    void ShowAllWord();

    void SaveHistory();
    void LoadHistory();
    void DisplayHistory();
};

