#include <iostream>
using namespace std;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};

int minimaxDecision(int house[], int depthMAX);
void maxValue(int house[], int depth, int depthMAX, int *mValue, int *action);
void minValue(int house[], int depth, int depthMAX, int *mValue, int *action);

void PrintHouse(int house[]){
    for (size_t i = 0; i < 14; i++) {
        cout << house[i] << " ";
    }
    cout << endl;
    return ;
}

int evaluate(int house[]){
    return house[player_store[computer]] - house[player_store[human]];
}

int listSuccessors(int house[], int successor[], bool isMaxPlayer) {

    int possible_actions = 0;
    for (size_t i = player_store[isMaxPlayer] - 6; i < player_store[isMaxPlayer]; i++) {
        if (house[i] != 0) {
            successor[possible_actions++] = i;
        }
    }
    return possible_actions;
}

bool relocation(int now_house[], int picked_house, int next_house[]){
    players player = picked_house > 6 ? computer : human; //computer or human
    copy(now_house, now_house + 14, next_house);
    next_house[picked_house] = 0;
    int index = picked_house + 1;

    for (size_t i = now_house[picked_house]; i > 0 ; i--, ++index) {
        index %= 14;
        if(index == player_store[!player]){
            i++;
            continue;
        }
        next_house[index]++;
    }
    index --;
    if(next_house[index] == 1 && index / 7 == player && next_house[12 - index] != 0 && index != player_store[player]){
        next_house[player_store[player]] += next_house[index] + next_house[12 - index];
        next_house[index] = 0;
        next_house[12 - index] = 0;
    }
    if(index == player_store[player]){
        return true;
    }else{
        return false;
    }
}


int minimaxDecision(int house[], int depthMAX) {
    int action;
    int v;
    maxValue(house, 0 ,depthMAX, &v, &action);
    return action;
}

void maxValue(int house[], int depth, int depthMAX, int *mValue, int *action) {
    if (depth == depthMAX) {
        *mValue = evaluate(house);
        //PrintHouse(house);
        return ;
    }
    int successor[6];
    int possible_actions = listSuccessors(house, successor, computer);
    int v = -99999;
    if (possible_actions == 0) {
        *mValue = evaluate(house);
        //PrintHouse(house);
        return ;
    }
    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = relocation(house, successor[i], next_house);
        if (more_action) {
            maxValue(next_house, depth + 1, depthMAX, &value, &a);
        }else {
            minValue(next_house, depth + 1, depthMAX, &value, &a);
        }
        if (v < value) {
            v = value;
            *action = successor[i];
        }
    }
    *mValue = v;
    return ;
}

void minValue(int house[], int depth, int depthMAX, int *mValue, int *action) {
    if (depth == depthMAX) {
        *mValue = evaluate(house);
        //PrintHouse(house);
        return ;
    }
    int successor[6];
    int possible_actions = listSuccessors(house, successor, human);
    int v = 99999;

    if (possible_actions == 0) {
        *mValue = evaluate(house);
        //PrintHouse(house);
        return ;
    }
    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = relocation(house, successor[i], next_house);
        if (more_action) {
            minValue(next_house, depth + 1, depthMAX, &value, &a);
        }else {
            maxValue(next_house, depth + 1, depthMAX, &value, &a);
        }
        if (v > value) {
            v = value;
            *action = successor[i];
        }
    }
    *mValue = v;
}

void test_minimax() {
    int ts;
    cin >> ts;
    while (ts--) {
        int house[14];
        int depthMAX;
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        cin >> depthMAX;
        cout << minimaxDecision(house, depthMAX) << endl;
    }
    return ;
}

int main(int argc, char const *argv[]) {
    test_minimax();
    return 0;
}
