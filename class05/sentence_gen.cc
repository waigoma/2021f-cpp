#include <iostream>
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

//    ifstream file(filePath);

//    DWORD start = GetTickCount();
    for (vector<utf8> u : *file) {
        if (u.empty()) break;
//        cout << u[0] << " " << u[1] << endl;
//        DWORD startT = GetTickCount();
//        if (hit) { // matchStr が見つかった
//            hitList.push_back(u); // matchStr の次の文字が push される
//            hit2 = false;
//            int i = 0;
//            for (auto prob : probList) { // 実際に数える用のリストを for で回す
//                if (prob.character == u[0]) { // 数えるリストに既に登録されているかどうか
//                    probList[i].count++;
//                    hit2 = true;
//                    break;
//                }
//                i++;
//            }
//            if (!hit2) { // 数えるリストになかったらリストに push
//                probList.push_back({u, 1});
//            }
//            count++;
//            hit = false;
//        }

        if (u[0] == *matchStr) {
//            cout << u[0] << " " << u[1] << " " << (double)(GetTickCount() - startT) / 1000.0  << endl;
//            hit = false;
//            int i = 0;
            hitList.push_back(u[1]);
//            for (auto prob : probList) { // 実際に数える用のリストを for で回す
//                if (prob.character == u[1]) { // 数えるリストに既に登録されているかどうか
//                    probList[i].count++;
//                    hit = true;
//                    break;
//                }
//                i++;
//            }
//            if (!hit) { // 数えるリストになかったらリストに push
//                probList.push_back({u[1], 1});
//            }
            count++;
        }
//        cout << (double)(GetTickCount() - startT) / 1000.0 << " " << u[0] << " // ";
    }
//    cout << "find: " << (double)(GetTickCount() - start) / 1000.0 << " " << endl;

//    start = GetTickCount();
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
//    cout << "count: " << (double)(GetTickCount() - start) / 1000.0 << " " << endl;

    int i = 0;
//    start = GetTickCount();
    for (Probability prob : probList) {
        probList[i++].prob = (double) prob.count / count * 100;
    }


    qsort(&probList[0], probList.size(), sizeof(Probability), compare);
//    cout << "qsort: " << (double)(GetTickCount() - start) / 1000.0 << endl;
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
    cin >> str;
    DWORD start = GetTickCount();

    utf8 startStr(str.c_str());

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
    bool impossible = false;

    for (int i = 0; i < 10; i++) {
        output << startStr;
        DWORD startT = GetTickCount();
        while (!(startStr == endStr)) {
//            DWORD start2 = GetTickCount();
//            cout << "probList a: " << (double)(GetTickCount() - start) / 1000.0 << endl;
            vector<Probability> probList = getProbabilities(&fileChars, &startStr);
//            cout << "probList b: " << (double)(GetTickCount() - startT) / 1000.0 << endl;

            startStr = selectChar(probList);
//            cout << "selectChar: " << (double)(GetTickCount() - start) / 1000.0 << endl;
//            cout << "は？:" << startStr << endl;
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
        if (impossible) break;
    }

    DWORD end = GetTickCount();

    cout << "duration: " << (double)(end - start) / 1000.0 << endl;
}