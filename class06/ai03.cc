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

vector<string> getNouns(vector<utf8> fileChars) {
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

    return nounVector;
}

int main() {
    // 開始文字を聞く2
    utf8 startStr;

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

    int rdm;

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
        const char *sp = line.c_str();

        while (true) {
            u1 = utf8(sp + offset);
            lines.push_back(u1);
            offset += u1.countBytes();
            if (u1.is_null()) break;
            utf8count++;
        }

        vector<string> inputNouns = getNouns(lines);
        rdm = getRandomNumber((int) inputNouns.size());

        startStr = utf8(inputNouns[rdm].c_str());

        rdm = getRandomNumber((int) rules.size());
        vector<string> rule = rules[rdm];
        if (rule[0] == "noun" && rule[1] == "verb") {
            // noun
            string noun = getRandomWord(nounList, true, &startStr);

            if (noun == "error") {
                cout << startStr << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
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
                cout << startStr << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
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
                cout << startStr << " <- その文字は、私の辞書にありません。なので、文章を生成不可能です。";
                return -1;
            }

            // 1文目
            output << noun << "は";

            // adj
            string adj = getRandomWord(adjList);
            output << adj << "です。";
        }

        cout << output.str() << endl << endl;
        output.str("");
        output.clear(stringstream::goodbit);
    }

}