#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

#include "utf8.h"

using namespace std;

typedef struct {
    utf8 character;
    int count;
    double prob;
} Probability;

int main() {
    // ファイル登録
    const string filePath = "default.txt";
    ifstream file(filePath);

    // ファイルがあるか確認
    if(!file){
        cerr << "Error: file could not opened." << endl;
        return 1;
    }

    // すべての文字を utf8 クラスに格納して vector にどーん
    vector<utf8> fileChars;
    string strTmp;
    while (getline(file, strTmp)) {
        utf8 u1;

        int offset = 0;
        const char* sp = strTmp.c_str();

        while (true) {
            u1 = utf8(sp + offset);
            offset += u1.countBytes();
            if (u1.is_null()) break;
            fileChars.push_back(u1);
        }
    }

    // 形容詞
    const utf8 adjective("い");
    const utf8 verb("う");
    const utf8 adjectivalNoun("だ");

    vector<string> adjVector;
    vector<string> vVector;
    vector<string> adjvVector;
    vector<string> nounVector;

    const utf8 mark1("、");
    const utf8 mark2("。");

    stringstream ss;

    // 品詞推定開始
    cout << "推定" << endl;
    utf8 tmp = fileChars[0];
    int i = 0;
    for (auto it : fileChars) {
        if (it.characterType() != tmp.characterType()) {
            if (tmp.characterType() == utf8::KANJI) {
                int j = i + 1;
                if (it == adjective) { // adj
                    ss << it << endl;
                    adjVector.push_back(ss.str());
                } else if (it == verb) { // verb
                    ss << it << endl;
                    vVector.push_back(ss.str());
                } else if (it == adjectivalNoun) { // adjv ~だ
                    ss << it << endl;
                    adjvVector.push_back(ss.str());
                } else if (fileChars[j] == adjectivalNoun) { // adjv ~かだ
                    if (it == mark1 || it == mark2) continue;
                    ss << it << fileChars[j] << endl;
                    adjvVector.push_back(ss.str());
                } else { // noun
                    ss << endl;
                    nounVector.push_back(ss.str());
                }
                ss.str("");
                ss.clear(stringstream::goodbit);
            }
        }

        if (it.characterType() == utf8::KANJI) ss << it;
        tmp = it;
        i++;
    }

    cout << "書き出し" << endl;
    ofstream adjFile("adj.txt");
    for (const auto& adj : adjVector) adjFile << adj;
    adjFile.close();

    ofstream verbFile("verb.txt");
    for (const auto& v : vVector) verbFile << v;
    verbFile.close();

    ofstream adjvFile("adjv.txt");
    for (const auto& adjv : adjvVector) adjvFile << adjv;
    adjvFile.close();

    ofstream nounFile("noun.txt");
    for (const auto& noun : nounVector) nounFile << noun;
    nounFile.close();

}