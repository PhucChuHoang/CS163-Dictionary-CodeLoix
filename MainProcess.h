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

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh);

bool SearchProcessing(HashTable &MainData);
bool EditProcessing(HashTable &MainData);
bool RandomWordProcessing(HashTable &MainData);
bool FavouriteProcessing(HashTable &MainData);
bool MinigameProcessing(HashTable &MainData);

bool ChooseFunctions(HashTable &MainData);
bool ChooseDictionary(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh);

void MainProcess();

