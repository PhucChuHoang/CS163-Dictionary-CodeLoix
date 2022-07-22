#include "UIhelper.h"

using namespace std;

int GetCommand() {
    int num;
    cout << "Your choice: ";
    cin >> num;
    return num;
}

void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void gotoxy(short x,short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

int getChoosing(vector<string> data, int location) {
    int currentChoose = 1;
    while(1) {
        char c = _getch();
        if ((int)c == 13) {
            SetColor(7);
            return currentChoose;
        }
        int prevChoose = currentChoose;
        if ((int)c == -32) {
            char c = _getch();
            if ((int)c == 72) {
                if (currentChoose != 1) {
                    --currentChoose;
                }
            }
            else if ((int)c == 80) {
                if (currentChoose != (int)(data.size())) {
                    ++currentChoose;
                }
            }
        }
        if (currentChoose != prevChoose) {
            gotoxy(location, prevChoose);
            SetColor(7);
            cout << data[prevChoose-1];
            SetColor(14);
            gotoxy(location, currentChoose);
            cout << data[currentChoose-1];
        }
    }
}
