#include "ai.h"
#include "kalah.h"

#include <iostream>
#include <algorithm>
#include <limits>
int c = 0;
int total_seeds = 0;
using namespace std;
int evaluate(const int house[]) {
    return house[player_store[computer]] - house[player_store[human]];
}

int listSuccessors(const int house[], int successor[], bool isMaxPlayer) {
    int possible_actions = 0;
    for (size_t i = player_store[isMaxPlayer] - 6;
        i < player_store[isMaxPlayer]; i++) {
        if (house[i] != 0) {
            successor[possible_actions++] = i;
        }
    }
    return possible_actions;
}

bool cmp(const nextState& a, const nextState& b) {
    if (a.more_action && b.more_action) {
        return evaluate(a.house) > evaluate(b.house);
    } else if (b.more_action) {
        return false;
    } else if (a.more_action) {
        return true;
    } else {
        return evaluate(a.house) > evaluate(b.house);
    }
}

int minimaxDecision(int house[], int depth) {
    int action = -1;
    int alpha = -numeric_limits<int>::max();
    int beta = numeric_limits<int>::max();
    cout << "分數" << minimax(house, depth, alpha, beta, &action, computer) << endl;
    cout << "action" << action << endl;
    // minimax(house, depth, alpha, beta, &action, computer);
    return action;
}

int minimax(int house[], int depth, int alpha, int beta, int *action,
            bool whoes_turn) {
    c++;
    if (noFurtherAction(house)) {
        finalScoring(house);
        return evaluate(house);
    }
    if (house[player_store[computer]] > total_seeds / 2) {
        return 999;
    } else if (house[player_store[human]] > total_seeds / 2) {
        return -999;
    } else if (depth <= 0) {
        return evaluate(house);
    }

    int successor[6];
    int possible_actions = listSuccessors(house, successor, whoes_turn);
    if (possible_actions == 0) {
        return evaluate(house);
    }

    nextState next_state[6];
    for (size_t i = 0; i < possible_actions; i++) {
        next_state[i].action = successor[i];
        next_state[i].more_action = relocation(house, successor[i]
                                                    , next_state[i].house);
    }

    sort(next_state, next_state + possible_actions, cmp);

    if (whoes_turn) {
        for (size_t i = 0; i < possible_actions; i++) {
            int value, a;
            if (next_state[i].more_action) {
                value = minimax(next_state[i].house, depth - 2, alpha, beta, &a,
                                computer);
            } else {
                value = minimax(next_state[i].house, depth - 1, alpha, beta, &a,
                                human);
            }
            if (alpha < value) {
                alpha = value;
                *action = next_state[i].action;
            }
            if (beta <= alpha) {
                return beta;
            }
        }
        return alpha;
    } else {
        for (size_t i = 0; i < possible_actions; i++) {
            int value, a;
            if (next_state[i].more_action) {
                value = minimax(next_state[i].house, depth - 2, alpha, beta, &a,
                                human);
            } else {
                value = minimax(next_state[i].house, depth - 1, alpha, beta, &a,
                                computer);
            }
            if (beta > value) {
                beta = value;
                *action = next_state[i].action;
            }
            if (beta <= alpha) {
                return alpha;
            }
        }
        return beta;
    }
}
