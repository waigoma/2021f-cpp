#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

#include "utf8.h"

using namespace std;

int getRandomNumber(int range, int addition=0) {
    random_device rnd;

    return rnd() % range + addition;
}

vector<string> getWords(ifstream* file) {
    string strTmp;
    vector<string> words;

    // ファイルがあるか確認
    if(!*file){
        cerr << "Error: file could not opened." << endl;
        return words;
    }

    while (getline(*file, strTmp)) {
        words.push_back(strTmp);
    }
    return words;
}

string getRandomWord(const vector<string>& words, bool match, utf8* matchStr) {
    vector<string> tmp;
    int rdm;

    if (words.empty()) return "error";

    for (const string& word: words) {
        if (*matchStr == utf8(word.c_str())) tmp.push_back(word);
    }

    if (tmp.empty()) return "error";

    rdm = getRandomNumber((int) tmp.size());
    return tmp[rdm];
}

string getRandomWord(const vector<string>& words) {
    int rdm;

    if (words.empty()) return "error";

    rdm = getRandomNumber((int) words.size());
    return words[rdm];
}

int main() {
    // 開始文字を聞く2
    string str;
    cout << "開始文字: ";
    cin >> str;

    utf8 startStr(str.c_str());

    // ファイル登録
    const string nounPath = "noun.txt";
    const string verbPath = "verb.txt";
    const string adjPath = "adj.txt";
    const string adjvPath = "adjv.txt";

    ifstream nounFile(nounPath);
    ifstream verbFile(verbPath);
    ifstream adjFile(adjPath);
    ifstream adjvFile(adjvPath);

    vector<vector<string>> rules;
    rules.push_back({"noun", "verb"});
    rules.push_back({"noun", "adjv"});
    rules.push_back({"noun", "adj"});

    vector<string> nounList = getWords(&nounFile);
    vector<string> verbList = getWords(&verbFile);
    vector<string> adjList = getWords(&adjFile);
    vector<string> adjvList = getWords(&adjvFile);

    stringstream output;

    int rdm = getRandomNumber((int) rules.size());
    vector<string> rule = rules[rdm];
    if (rule[0] == "noun" && rule[1] == "verb") {
        // noun
        string noun = getRandomWord(nounList, true, &startStr);

        if (noun == "error") {
            cout << str << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
            return -1;
        }

        // 1文目
        output << noun << "は";

        //  verb
        string verb = getRandomWord(verbList);
        output << verb << "。";
    } else if (rule[0] == "noun" && rule[1] == "adjv") {
        // noun
        string noun = getRandomWord(nounList, true, &startStr);

        if (noun == "error") {
            cout << str << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
            return -1;
        }

        // 1文目
        output << noun << "は";

        // adjv
        string adjv = getRandomWord(adjvList);
        output << adjv << "。";
    } else if (rule[0] == "noun" && rule[1] == "adj") {
        // noun
        string noun = getRandomWord(nounList, true, &startStr);

        if (noun == "error") {
            cout << str << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
            return -1;
        }

        // 1文目
        output << noun << "は";

        // adj
        string adj = getRandomWord(adjList);
        output << adj << "です。";
    }

    cout << output.str() << endl;

}