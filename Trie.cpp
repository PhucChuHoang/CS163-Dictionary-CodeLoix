#include "Trie.h"

using namespace std;

TrieNode::TrieNode (char x) {
    chr = x;
}

void Trie::Self_Destruct(TrieNode* &Cur) {
    if (Cur == nullptr) return;

    Self_Destruct(Cur->Next);
    Self_Destruct(Cur->Child);

    delete Cur;
    Cur = nullptr;
}

Trie::Trie() {
    Root = new TrieNode('a');
}

Trie::~Trie() {
    Self_Destruct(Root);
}

void Trie::Insert(string &s) {
    if (Search(s)) return;
    TrieNode *Cur = Root;

    for (char &c: s) {
        if (Cur->Child == nullptr) {
            Cur->Child = new TrieNode(c);
            Cur = Cur->Child;
        }
        else {
            TrieNode *Child = Cur->Child;
            while (Child->chr != c && Child->Next) Child = Child->Next;
            if (Child->chr != c) Child->Next = new TrieNode(c), Child = Child->Next;
            Cur = Child;
        }

        Cur->Count++;
    }

    Cur->isEnd = 1;
}

bool Trie::Search(std::string s) {
    TrieNode *Cur = Root;

    for (char &c: s) {
        if (Cur->Child == nullptr) return 0;
        else {
            TrieNode *Child = Cur->Child;
            while (Child && Child->chr != c) Child = Child->Next;
            if (Child == nullptr || Child->chr != c) return 0;
            Cur = Child;
        }
    }

    return Cur->isEnd;
}

void Trie::_Delete(std::string &s, int pos, TrieNode* &Cur) { //BUGGGGGGGGGGGgg

    TrieNode *p = Cur;
    while (p->chr != s[pos]) p = p->Next;
    if ((int) (s.size()) > pos + 1) _Delete(s, pos + 1, p->Child);
        else p->isEnd = 0;
    p->Count--;

    if (p->Count == 0) {
        TrieNode *pD = nullptr;
        if (p == Cur) {
            pD = Cur;
            Cur = Cur->Next;
        }
        else {
            p = Cur;
            while (p->Next->chr != s[pos]) p = p->Next;
            pD = p->Next;
            p->Next = p->Next->Next;
        }
        delete pD;
        pD = nullptr;
    }
}

void Trie::Delete(std::string s) {// s always in Trie
    if (Search(s)) _Delete(s, 0, Root->Child);
}

void Trie::PrintSubTree(std::string s, TrieNode* Cur) {
    if (Cur->isEnd) cout << s << '\n';

    TrieNode *p = Cur->Child;
    while (p) {
        PrintSubTree(s + p->chr, p);
        p = p->Next;
    }
}

void Trie::FWWSPHelper(TrieNode *Cur, std::vector <std::string> &res, int &NumberOfWords, std::string s) {
    if (NumberOfWords == 0) return;

    if (Cur->isEnd) {
        NumberOfWords--;
        res.push_back(s);
    }

    TrieNode *p = Cur->Child;
    while (p) {
        FWWSPHelper(p, res, NumberOfWords, s + p->chr);
        p = p->Next;
    }
}

std::vector <std::string> Trie::FindWordWithSamePrefix(int NumberOfWords, std::string Prefix) {

    std::vector <std::string> res;
    res.clear();

    TrieNode *p = Root;
    for (char &c: Prefix) {
        TrieNode *Child = p->Child;
        while (Child && Child->chr != c) Child = Child->Next;
        p = Child;
        if (p == nullptr) return res;
    }

    FWWSPHelper(p, res, NumberOfWords, Prefix);

    return res;
}

void Trie::PrintAllWords() {
    PrintSubTree("", Root);
}

