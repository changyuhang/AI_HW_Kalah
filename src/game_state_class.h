#ifndef SRC_GAME_STATE_CLASS_H_
#define SRC_GAME_STATE_CLASS_H_

#include <iostream>
#include <algorithm>


class GameState {
 public:
     const int player_store[2] = {6, 13};
     enum players {
         human = true,
         computer = false,
     };
     explicit GameState(int seeds);
     explicit GameState(int *house);
     int listSuccessors(int successor[], bool isMaxPlayer);
     bool noFurtherAction();
     bool relocation(int picked_house, int next_house[]);
     void finalScoring();
     void nextState(int picked_house);
     void printState();
     ~GameState();
     int house[14];
};

#endif  // SRC_GAME_STATE_CLASS_H_
