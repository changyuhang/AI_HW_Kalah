#include <iostream>
using namespace std;

const int player_store[2] = {6, 13};
enum players { human = false, computer = true};

bool relocation(const int now_house[], const int picked_house, int next_house[]);
void test_relocation();

// bool relocation(int now_house[], int picked_house, int next_house[]){
//     players player = picked_house > 6 ? computer : human; //computer or human
//     copy(now_house, now_house + 14, next_house);
//     next_house[picked_house] = 0;
//     int index = picked_house + 1;
//
//     for (size_t i = now_house[picked_house]; i > 0 ; i--, ++index) {
//         index %= 14;
//         if(index == player_store[!player]){
//             i++;
//             continue;
//         }
//         next_house[index]++;
//     }
//     index --;
//     if(next_house[index] == 1 && index / 7 == player && next_house[12 - index] != 0 && index != player_store[player]){
//         next_house[player_store[player]] += next_house[index] + next_house[12 - index];
//         next_house[index] = 0;
//         next_house[12 - index] = 0;
//     }
//     if(index == player_store[player]){
//         return true;
//     }else{
//         return false;
//     }
// }

bool relocation(const int now_house[], const int picked_house,
                int next_house[]) {
    players player = picked_house > 6 ? computer : human;   // computer or human
    // copy(now_house, now_house + 14, next_house);
    next_house[picked_house] = 0;
    int index = picked_house + 1;
    int seeds = now_house[picked_house];
    for (size_t i = 0; i < 14 ; i++) {
        index %= 14;
        if (index == player_store[!player]) {
            next_house[index] = now_house[index];
            index++;
        } else if (index == picked_house) {
            index++;
        }
        if (seeds) {
            next_house[index] = seeds / 13 + 1 + now_house[index];
            seeds -= seeds / 13 + 1;
        } else {
            next_house[index] = now_house[index];
        }
        index++;
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

void test_relocation(){
    int ts;
    int house[14];
    int picked_house;
    cin >> ts;
    while(ts--){
        int next_house[14];
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        cin >> picked_house;
        bool temp = relocation(house, picked_house, next_house);
        cout << "[";
        for (size_t i = 0; i < 14; i++) {
            cout << next_house[i] << (i == 13? "" : " ");
        }
        cout << "]" << endl;
        cout << (temp ? "YES" : "NO") << endl;
    }
}

int main(){
    test_relocation();
    return 0;
}
