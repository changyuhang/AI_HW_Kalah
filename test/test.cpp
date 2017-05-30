#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

typedef struct {
    int house[14];
    int action;
    bool more_action;
}nextState;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};
int total_seeds = 0;
int c = 0;

int minimaxDecision(const int house[], int depth);
int minimax(const int house[], int depth, int alpha, int beta, int *action,
            bool whoes_turn);

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

bool relocation(const int now_house[], const int picked_house,
                int next_house[]) {
    players player = picked_house > 6 ? computer : human;   // computer or human
    copy(now_house, now_house + 14, next_house);
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

int minimaxDecision(const int house[], int depth) {
    int action = -1;
    int alpha = -numeric_limits<int>::max();
    int beta = numeric_limits<int>::max();
    cout << "分數" << minimax(house, depth, alpha, beta, &action, computer) << endl;
    return action;
}

int minimax(const int house[], int depth, int alpha, int beta, int *action,
            bool whoes_turn) {
    c++;
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


void test_minimax() {
    int ts;
    cin >> ts;
    while (ts--) {
        c = 0;
        total_seeds = 0;
        int house[14];
        int depth;
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
            total_seeds += house[i];
        }
        cin >> depth;
        clock_t t;
        t = clock();
        cout << minimaxDecision(house, depth) << endl;
        t = clock() - t;
        printf("It took me %d clicks (%f seconds).\n",
                            t, ((float)t)/CLOCKS_PER_SEC);
        cout << "深度" << depth << "次數" << c << endl;
    }
    return;
}

int main(int argc, char const *argv[]) {
    test_minimax();
    return 0;
}
