#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};

int c = 0;

int minimaxDecision(int house[], int depth);
int maxValue(int house[], int depth, int alpha, int beta, int *action);
int minValue(int house[], int depth, int alpha, int beta, int *action);

int evaluate(int house[]) {
    return house[player_store[computer]] - house[player_store[human]];
}

int listSuccessors(int house[], int successor[], bool isMaxPlayer) {
    int possible_actions = 0;
    for (size_t i = player_store[isMaxPlayer] - 6;
        i < player_store[isMaxPlayer]; i++) {
        if (house[i] != 0) {
            successor[possible_actions++] = i;
        }
    }
    return possible_actions;
}

bool relocation(int now_house[], int picked_house, int next_house[]) {
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


int minimaxDecision(int house[], int depth) {
    int action = -1;
    int alpha = -numeric_limits<int>::max();
    int beta = numeric_limits<int>::max();
    maxValue(house, depth, alpha, beta, &action);
    return action;
}

int maxValue(int house[], int depth, int alpha, int beta, int *action) {
    c++;
    if (depth <= 0) {
        return evaluate(house);
    }
    int successor[6];
    int possible_actions = listSuccessors(house, successor, computer);
    if (possible_actions == 0) {
        return evaluate(house);
    }
    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = relocation(house, successor[i], next_house);
        if (more_action) {
            value = maxValue(next_house, depth - 2, alpha, beta, &a);
        } else {
            value = minValue(next_house, depth - 1, alpha, beta, &a);
        }
        if (alpha < value) {
            alpha = value;
            *action = successor[i];
        }
        if (beta <= alpha) {
            return beta;
        }
    }
    return alpha;
}

int minValue(int house[], int depth, int alpha, int beta, int *action) {
    c++;
    if (depth <= 0) {
        return evaluate(house);
    }
    int successor[6];
    int possible_actions = listSuccessors(house, successor, human);

    if (possible_actions == 0) {
        return evaluate(house);
    }
    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = relocation(house, successor[i], next_house);
        if (more_action) {
            value = minValue(next_house, depth - 2, alpha, beta, &a);
        } else {
            value = maxValue(next_house, depth - 1, alpha, beta, &a);
        }
        if (beta > value) {
            beta = value;
            *action = successor[i];
        }
        if (beta <= alpha) {
            return alpha;
        }
    }
    return beta;
}

void test_minimax() {
    int ts;
    cin >> ts;
    while (ts--) {
        c = 0;
        int house[14];
        int depth;
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
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
