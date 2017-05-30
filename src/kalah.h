#ifndef KALAH_H_
#define KALAH_H_
enum players { human = false, computer = true};
const int player_store[2] = {6, 13};
bool noFurtherAction(int house[]);
bool relocation(const int now_house[], const int picked_house
                                     , int next_house[]);
void finalScoring(int house[]);
int getNextAction(int house[]);
#endif  // KALAH_H_
