#include "MainProcess.h"

using namespace std;

void InitData(HashTable &AnhViet, HashTable &VietAnh, HashTable &AnhAnh) {
    string Path = "Data/";
    string AnhVietFile = "anhviet.txt";
    string VietAnhFile = "vietanh.txt";
    //string AnhAnhFile = "";

    //AnhViet.FileInput(Path + AnhVietFile);
    //VietAnh.FileInput(Path + VietAnhFile);
}

void MainProcess() {
    HashTable AnhViet(31, 14071), VietAnh(31, 14071), AnhAnh(31, 14071);
    InitData(AnhViet, VietAnh, AnhAnh);
    while (true) {
        //ChooseDictionary();
    }
}

