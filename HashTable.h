#pragma once

#include "Word.h"
#include "Const.h"
#include "Trie.h"

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
    Trie Prefix;
    std::vector <std::string> GetType;
    std::vector <std::string> History;
    std::vector <std::string> Favorite;

    HashTable(std::string Name, int _P, int _N);
    ~HashTable();

    int GetHash(std::string &s);
    void InsertNewString(std::string &s);
    void InsertNewWord(Word &W);

    void displayChain();
    void DeleteWord(std::string &s);
    HashNode* FindWord(std::string &s);

    void FileInput(std::string &Filename, bool isReset);
    void ShowAllWord();
    void SaveHashTable();

    void SaveHistory();
    void LoadHistory();
    void DisplayHistory();

    void SaveFavorite();
    void LoadFavorite();
    void DisplayFavorite();
};

