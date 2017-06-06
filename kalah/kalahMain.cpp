#include "kalah.h"
#include "ai.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void printHouse(const int house[]) {
    for (size_t i = 0; i < 14; i++) {
        cout << house[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    int depth;
    int house[14] = {};
    total_seeds = 0;
    bool player;  // false = human, true = computer
    cout << "請輸入初始狀態" << endl;
    for (size_t i = 0; i < 14; i++) {
        cin >> house[i];
        total_seeds += house[i];
    }
    cout << "請輸入搜尋深度" << endl;
    while (std::cin >> depth) {
        if (depth > 0) break;
        std::cout << "輸入錯誤！請重新輸入大於0的數字:";
    }
    cout << "請輸入誰先(computer or human)";
    string playerFirst;
    while (std::cin >> playerFirst) {
        if (playerFirst == "human") {
            player = false;
            break;
        } else if (playerFirst == "computer") {
            player = true;
            break;
        }
        std::cout << "輸入錯誤！請輸入human或是computer:";
    }
    while (!noFurtherAction(house)) {
        bool more_action;
        int next_house[14];
        printHouse(house);
        if (player) {
            cout << "AI" << endl;
            more_action = relocation(house, minimaxDecision(house, depth),
                                            next_house);
        } else {
            cout << "human" << endl;
            more_action = relocation(house, getNextAction(house), next_house);
        }
        if (more_action == false) {
            player = !player;
        }
        copy(next_house, next_house + 14, house);
    }
    finalScoring(house);
    printHouse(house);
    if (player_store[human] > player_store[computer]) {
        cout << "你贏了" << endl;
    } else if (player_store[human] < player_store[computer]) {
        cout << "電腦贏了" << endl;
    } else {
        cout << "平手" << endl;
    }
    return 0;
}
