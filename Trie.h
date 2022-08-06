#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

struct TrieNode {
    char chr;

    int Count = 0;
    int isEnd = 0;
    TrieNode *Child = nullptr;
    TrieNode *Next = nullptr;

    TrieNode (char x);
};

struct Trie {
    TrieNode *Root = nullptr;

    void Self_Destruct(TrieNode* &Cur);

    Trie();
    ~Trie();

    void Insert(std::string &s);
    bool Search(std::string s);
    void _Delete(std::string &s, int pos, TrieNode* &Cur);
    void Delete(std::string s);

    void PrintSubTree(std::string s, TrieNode* Cur);

    void FWWSPHelper(TrieNode *Cur, std::vector <std::string> &res, int &NumberOfWords, std::string s);
    std::vector <std::string> FindWordWithSamePrefix(int NumberOfWords, std::string Prefix);

    void PrintAllWords();
};
