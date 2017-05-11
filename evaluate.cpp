#include <iostream>
using namespace std;

enum players { human = false, computer = true};
const int player_store[2] = {6, 13};

int evaluate(int house[]);
void test_evaluate();

int evaluate(int house[]){
    return house[player_store[computer]] - house[player_store[human]];
}

void test_evaluate(){
    int ts;
    int house[14];
    cin >> ts;
    while(ts--){
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        cout << evaluate(house) << endl;
    }
}

int main(int argc, char const *argv[]) {
    test_evaluate();
    return 0;
}
