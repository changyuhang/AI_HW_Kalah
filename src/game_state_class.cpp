#include "game_state_class.h"

GameState::GameState(int seeds) {
    std::fill(house, house + 6, seeds);
    std::fill(house + 7, house + 13, seeds);
}

GameState::GameState(int *h) {
    std::copy(h, h + 14, house);
}
int GameState::listSuccessors(int successor[]) {
    int possible_actions = 0;
    for (size_t i = player_store[whoes_turn] - 6;
         i < player_store[whoes_turn]; i++) {
        if (house[i] != 0) {
            successor[possible_actions++] = i;
        }
    }
    return possible_actions;
}

bool GameState::noFurtherAction() {
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

bool GameState::relocation(int picked_house, int next_house[]) {
    players player = picked_house > 6 ? computer : human;  // computer or human
    std::copy(house, house + 14, next_house);
    next_house[picked_house] = 0;
    int index = picked_house + 1;

    for (size_t i = house[picked_house]; i > 0 ; i--, ++index) {
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

void GameState::finalScoring() {
    for (size_t i = 0; i < 13; i++) {
        if (i == 6)i++;
        house[player_store[i / 7]] += house[i];
        house[i] = 0;
    }
    return;
}

bool GameState::nextState(int picked_house) {
    int next_house[14];
    bool more_action = relocation(picked_house, next_house);
    std::copy(next_house, next_house + 14, house);
    return more_action;
}

void GameState::findPossibleAction(std::vector<GameState> &v) {
    int successor[6];
    int possible_actions = listSuccessors(successor);
    for (size_t i = 0; i < possible_actions; i++) {
        GameState next_state(house);
        next_state.whoes_turn = next_state.nextState(successor[i]);
        next_state.action = successor[i];
        v.push_back(next_state);
    }
}
void GameState::printState() {
    for (size_t i = 0; i < 14; i++) {
        std::cout << house[i];
    }
    std::cout << std::endl;
}

GameState::~GameState() {}
