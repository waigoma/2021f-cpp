#include <iostream>
#include <ctime>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

#include "utf8.h"

using namespace std;

typedef struct {
    utf8 character;
    int count;
    double prob;
} Probability;

int compare(const void* myA, const void* myB) {
    if (((Probability*) myA)->prob > ((Probability*) myB)->prob) {
        return -1;
    } else if (((Probability*) myA)->prob < ((Probability*) myB)->prob) {
        return 1;
    } else {
        return 0;
    }
}

int getRandomNumber(int range, int addition=0) {
//    srand(time(NULL));
    random_device rnd;

    return rnd() % range + addition;
}

// matchStrの次の文字リストを取得し、[文字, 個数]を返す
vector<Probability> getProbabilities(const vector<vector<utf8>>* file, const utf8* matchStr) {
    // matchStrの次の文字リスト
    vector<utf8> hitList;
    vector<Probability> probList; // 実際に数える用 [文字, 個数]
    // 全体で何文字あったか保存用
    int count = 0;

    // matchStr を見つけたかどうか
    bool hit = false;

//    DWORD start = GetTickCount();
    for (vector<utf8> u : *file) {
        if (u.empty()) break;
        if (u[0] == *matchStr) {
            hitList.push_back(u[1]);
            count++;
        }
    }

    for (auto hitStr : hitList) { // matchStr の次の文字リストを for で回す
        hit = false;
        int i = 0;
        for (auto prob : probList) { // 実際に数える用のリストを for で回す
            if (prob.character == hitStr) { // 数えるリストに既に登録されているかどうか
                probList[i].count++;
                hit = true;
                break;
            }
            i++;
        }
        if (!hit) { // 数えるリストになかったらリストに push
            probList.push_back({hitStr, 1});
        }
    }

    int i = 0;
    for (Probability prob : probList) {
        probList[i++].prob = (double) prob.count / count * 100;
    }


    qsort(&probList[0], probList.size(), sizeof(Probability), compare);
    return probList;
}

utf8 selectChar(const vector<Probability>& probList) {
    utf8 character(0,0,0,0,0,0);
    if (probList.empty()) return character;
    double rdm = getRandomNumber(10001) / 100.0;
//    cout << rdm << endl;
    while (rdm > 0) {
        for (Probability prob : probList) {
            rdm -= prob.prob;
            if (rdm < 0) {
                character = prob.character;
                break;
            }
        }
    }
    return character;
}

int main() {
    // 開始文字を聞く2
    string str;
    //  cout << "開始文字: ";
    DWORD start = GetTickCount();

    utf8 startStr;

    // ファイル登録
    const string filePath = "2-gram.txt";
    ifstream file(filePath);

    // ファイルがあるか確認
    if(!file){
        cerr << "Error: file could not opened." << endl;
        return 1;
    }

    vector<vector<utf8>> fileChars;
    string strTmp;
    while (getline(file, strTmp)) {
//        cout << strTmp << endl;
        vector<utf8> tmp;
        utf8 u1;

        int offset = 0;
        const char* sp = strTmp.c_str();

        while (true) {
            u1 = utf8(sp + offset);
            offset += u1.countBytes();
            if (u1.is_null()) break;
            tmp.push_back(u1);
        }

        fileChars.push_back(tmp);
    }

    const utf8 endStr("。");

    stringstream output;

    string line = "tmp";
    cout << "文字を入力してください。( :q で終了)" << endl;
    while (!line.empty()) {
        cout << "あなた: ";
        getline(cin, line);

        if (line == ":q") {
            cout << "終了します。" << endl;
            break;
        }

        // 文字数
        vector<utf8> lines;

        int utf8count = 0;
        int offset = 0;
        utf8 u1;
        const char* sp = line.c_str();

        while (true) {
            u1 = utf8(sp + offset);
            lines.push_back(u1);
            offset += u1.countBytes();
            if (u1.is_null()) break;
            utf8count++;
        }

        int idx = getRandomNumber(utf8count);
        startStr = lines[idx];

        output << "無能: " << startStr;
        bool impossible = false;
        DWORD startT = GetTickCount();
        while (!(startStr == endStr)) {
//            cout << "probList a: " << (double)(GetTickCount() - start) / 1000.0 << endl;
            vector<Probability> probList = getProbabilities(&fileChars, &startStr);
//            cout << "probList b: " << (double)(GetTickCount() - start) / 1000.0 << endl;

            startStr = selectChar(probList);
//            cout << "selectChar: " << (double)(GetTickCount() - start) / 1000.0 << endl;
//        cout << startStr << endl;
            if (startStr.is_null()) {
                output << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
                impossible = true;
                break;
            }
            else output << startStr;
        }
        startStr = utf8(str.c_str());
        cout << "duration: " << (double)(GetTickCount() - startT) / 1000.0 << endl;
        cout << output.str() << endl << endl;
        output.str("");
        output.clear(stringstream::goodbit);
    }

    DWORD end = GetTickCount();

    cout << "duration: " << (double)(end - start) / 1000.0 << endl;

}