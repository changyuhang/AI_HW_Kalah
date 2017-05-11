#include <iostream>
using namespace std;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};

int getNextAction(int house[]);

int getNextAction(int house[]) {
    int action;
    while (cin >> action) {
        if(action >= player_store[human]) {
            cout << "You cannot take seeds from house#";
        }else if (house[action] == 0){
            cout << "There is no seed in house#";
        }else{
            cout << "Your choice is house#";
            cout << action << "." << endl;
            break;
        }
        cout << action << "." << endl;
    }
    return action;
}


void test_getNextAction() {
    int ts;
    int house[14];
    cin >> ts;
    while(ts--){
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        getNextAction(house);
    }
}

int main() {
    test_getNextAction();
    return 0;
}
