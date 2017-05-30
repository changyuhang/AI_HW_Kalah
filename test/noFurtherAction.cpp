#include <iostream>
using namespace std;

bool noFurtherAction(int house[]);


bool noFurtherAction(int house[]){
    for (size_t i = 0; i < 13; i == 5 ? i += 2 : i++) {
        if (house[i] != 0) {
            if(i < 6){
                i = 7;
                continue;
            }else{
                break;
            }
        }else{
            if(i == 5 || i == 12){
                return true;
            }
        }
    }
    return false;
}

void test_noFurtherAction(){
    int t;
    cin >> t;
    while (t--) {
        int house[14];
        for (size_t i = 0; i < 14; i++) {
            cin >> house[i];
        }
        if(noFurtherAction(house)){
            cout << "YES" << endl;
        }else {
            cout << "NO" <<endl;
        }
    }
}
