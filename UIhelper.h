#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

int GetCommand();
int getChoosing(std::vector<std::string> data, int location);

void SetColor(WORD color);
void gotoxy(short x,short y);
void SetBGColor(WORD color);