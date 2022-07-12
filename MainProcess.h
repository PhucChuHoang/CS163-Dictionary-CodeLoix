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

#define rand rd

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emo, HashTable &slang);

bool SearchProcessing(HashTable &MainData);
bool EditProcessing(HashTable &MainData);
bool RandomWordProcessing(HashTable &MainData);
bool FavouriteProcessing(HashTable &MainData);
bool MinigameProcessing(HashTable &MainData);
bool EditWordDefProcessing(HashTable &data, string to_edit);
bool HistoryProcessing(HashTable &data);
bool ChooseFunctions(HashTable &MainData);
bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh, HashTable &emotional, HashTable& slang);

void MainProcess();

