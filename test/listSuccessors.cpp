#include <iostream>
using namespace std;

const int player_store[2] = {6, 13};

int listSuccessors(int house[], int successor[], bool isMaxPlayer);
void test_listSuccessors();

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

void test_listSuccessors() {
    int ts;
    int house[14];
    char temp[10];
    cin >> ts;
    while (ts--) {
        int successor[6];
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        cin >> temp;

        int possible_actions = listSuccessors(house, successor, strncmp(temp, "human", 5) != 0);
        cout << possible_actions << " [";
        for (size_t i = 0; i < possible_actions; i++) {
            cout << successor[i] << (i == (possible_actions - 1)? "" : " ");
        }
        cout << "]" << endl;
    }
}

int main(int argc, char const *argv[]) {
    test_listSuccessors();
    return 0;
}
