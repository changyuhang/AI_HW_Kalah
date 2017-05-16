#ifndef SRC_GAME_STATE_CLASS_H_
#define SRC_GAME_STATE_CLASS_H_

#include <iostream>
#include <algorithm>
#include <vector>

class GameState {
 public:
     const int player_store[2] = {6, 13};
     enum players {
         human = false,
         computer = true,
     };
     explicit GameState(int seeds);
     explicit GameState(int *house);
     int listSuccessors(int successor[]);
     bool noFurtherAction();
     bool relocation(int picked_house, int next_house[]);
     void finalScoring();
     bool nextState(int picked_house);
     void findPossibleAction(std::vector<GameState> &);
     void printState();
     ~GameState();
     int house[14];
     bool whoes_turn;
     int action;
};

#endif  // SRC_GAME_STATE_CLASS_H_
