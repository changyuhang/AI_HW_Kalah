#include "kalah.h"
#include <iostream>
#include <algorithm>

// Part 1
bool noFurtherAction(const int house[]) {
    for (size_t i = 0; i < 13; i == 5 ? i += 2 : i++) {
        if (house[i] != 0) {
            if (i < 6) {
                i = 7;
                continue;
            } else {
                break;
            }
        } else {
            if (i == 5 || i == 12) {
                return true;
            }
        }
    }
    return false;
}

// Part 2
bool relocation(const int now_house[], const int picked_house,
                int next_house[]) {
    players player = picked_house > 6 ? computer : human;   // computer or human
    std::copy(now_house, now_house + 14, next_house);
    next_house[picked_house] = 0;
    int index = picked_house + 1;

    for (size_t i = now_house[picked_house]; i > 0 ; i--, ++index) {
        index %= 14;
        if (index == player_store[!player]) {
            i++;
            continue;
        }
        next_house[index]++;
    }
    index--;
    if (next_house[index] == 1
        && index / 7 == player
        && next_house[12 - index] != 0
        && index != player_store[player]) {
        next_house[player_store[player]] += next_house[index]
                                            + next_house[12 - index];
        next_house[index] = 0;
        next_house[12 - index] = 0;
    }
    if (index == player_store[player]) {
        return true;
    } else {
        return false;
    }
}

// Part 5-1

void finalScoring(int house[]) {
    for (size_t i = 0; i < 13; i++) {
        if (i == 6)i++;
        house[player_store[i / 7]] += house[i];
        house[i] = 0;
    }
}

// Part 5-2
int getNextAction(int house[]) {
    int action;
    while (std::cin >> action) {
        if (action >= player_store[human]) {
            std::cout << "You cannot take seeds from house#";
        } else if (house[action] == 0) {
            std::cout << "There is no seed in house#";
        } else {
            std::cout << "Your choice is house#";
            std::cout << action << "." << std::endl;
            break;
        }
        std::cout << action << "." << std::endl;
    }
    return action;
}
