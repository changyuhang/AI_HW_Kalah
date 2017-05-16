#ifndef SRC_AI_CLASS_H_
#define SRC_AI_CLASS_H_
#include <limits>
#include <vector>

#include "game_state_class.h"

namespace ai {
    int minimaxDecision(GameState state, int depth);
    int minimaxValue(GameState const &, int, int, int, int *);
    int evaluate(GameState state);
    void test_minimax();
}
#endif  // SRC_AI_CLASS_H_
