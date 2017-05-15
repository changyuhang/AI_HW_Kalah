#ifndef SRC_AI_CLASS_H_
#define SRC_AI_CLASS_H_
#include <limits>

#include "game_state_class.h"

namespace ai {
    int minimaxDecision(GameState state, int depth);
    int maxValue(GameState state, int depth, int alpha, int beta, int *action);
    int minValue(GameState state, int depth, int alpha, int beta, int *action);
    int evaluate(GameState state);
    void test_minimax();
}
#endif  // SRC_AI_CLASS_H_
