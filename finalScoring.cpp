#include <iostream>
using namespace std;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};

void finalScoring(int house[]){
    for (size_t i = 0; i < 13; i++) {
        if(i == 6)i++;
        house[player_store[i / 7]] += house[i];
        house[i] = 0;
    }
}

void test_finalScoring(){
    int ts;
    int house[14];
    cin >> ts;
    while(ts--){
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        finalScoring(house);
        cout << "[";
        for (size_t i = 0; i < 14; i++) {
            cout << house[i] << (i == 13? "" : " ");
        }
        cout << "]" << endl;
    }
}

int main(){
    test_finalScoring();
    return 0;
}
