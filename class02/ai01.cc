#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    string line;
    string msgs[] = {"ふ～ん、それで？", "それは大変だ！", "イイネ！", "なるほど、それから？", "こんにちは", "はじめまして！"};
    int randomIndex = 5;

    srand(time(NULL));

    cout << "エコぴょん: メッセージをどうぞ" << endl;
    cout << "あなた: ";
    getline(cin, line);

    while (!line.empty()) {
        cout << "エコぴょん: " << msgs[randomIndex] << endl;
        cout << "あなた: ";
        getline(cin, line);
        randomIndex = rand() % 5;
    }

    cout << "エコぴょん: ばいば～い" << endl;

    return 0;
}