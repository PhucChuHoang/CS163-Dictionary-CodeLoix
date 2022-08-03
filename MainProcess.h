#pragma once

#include "Word.h"
#include "HashTable.h"
#include "UIhelper.h"
#include "Menu.h"
#include "Trie.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <assert.h>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang);
void SaveData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang);

HashNode *SearchHelper(std::string &w, HashTable &MainData);
bool SearchProcessing(HashTable &MainData);
bool EditProcessing(HashTable &MainData);
bool RandomWordProcessing(HashTable &MainData);
bool FavouriteProcessing(HashTable &MainData);
bool MinigameProcessing(HashTable &MainData);
bool EditWordDefProcessing(HashTable &data, std::string to_edit);

bool ChooseFunctions(HashTable &MainData);
bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emotional, HashTable& slang);

void MainProcess();

