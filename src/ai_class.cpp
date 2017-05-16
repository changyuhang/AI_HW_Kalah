#include "ai_class.h"
namespace ai {
int evaluate(GameState state) {
    return state.house[state.player_store[state.computer]]
            - state.house[state.player_store[state.human]];
}

int minimaxDecision(GameState state, int depth) {
    int action = -1;
    int alpha = -std::numeric_limits<int>::max();
    int beta = std::numeric_limits<int>::max();
    maxValue(state, depth, alpha, beta, &action);
    return action;
}

int maxValue(GameState state, int depth, int alpha, int beta, int *action) {
    if (depth <= 0) {
        return evaluate(state);
    }

    // std::vector<GameState> possible_state;
    // state.findPossibleAction(possible_state);
    // if (possible_state.size() == 0) {
    //     return evaluate(state);
    // }
    // for (GameState &next_state : possible_state) {
    //     next_state.printState();
    //     std::cout << state.whoes_turn <<next_state.whoes_turn << std::endl;
    //     int value, a;
    //     if (next_state.whoes_turn == state.whoes_turn) {  // more action
    //         value = maxValue(next_state, depth - 2, alpha, beta, &a);
    //     } else {
    //         value = minValue(next_state, depth - 1, alpha, beta, &a);
    //     }
    //     if (alpha < value) {
    //         alpha = value;
    //         *action = next_state.action;
    //     }
    //     if (beta <= alpha) {
    //         return beta;
    //     }
    // }
    int successor[6];
    int possible_actions = state.listSuccessors(successor);
    if (possible_actions == 0) {
        return evaluate(state);
    }

    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = state.relocation(successor[i], next_house);
        GameState next_state(next_house);
        if (more_action) {
            next_state.whoes_turn = state.whoes_turn;
            value = maxValue(next_state, depth - 2, alpha, beta, &a);
        } else {
            next_state.whoes_turn = !state.whoes_turn;
            value = minValue(next_state, depth - 1, alpha, beta, &a);
        }
        if (alpha < value) {
            alpha = value;
            *action = successor[i];
        }
        if (beta <= alpha) {
            return beta;
        }
    }
    return alpha;
}

int minValue(GameState state, int depth, int alpha, int beta, int *action) {
    if (depth <= 0) {
        return evaluate(state);
    }

    // std::vector<GameState> possible_state;
    // state.findPossibleAction(possible_state);
    // if (possible_state.size() == 0) {
    //     return evaluate(state);
    // }
    // for (GameState &next_state : possible_state) {
    //     int value, a;
    //     if (next_state.whoes_turn == state.whoes_turn) {  // more action
    //         value = minValue(next_state, depth - 2, alpha, beta, &a);
    //     } else {
    //         value = maxValue(next_state, depth - 1, alpha, beta, &a);
    //     }
    //     if (alpha < value) {
    //         alpha = value;
    //         *action = next_state.action;
    //     }
    //     if (beta <= alpha) {
    //         return alpha;
    //     }
    // }
    int successor[6];
    int possible_actions = state.listSuccessors(successor);

    if (possible_actions == 0) {
        return evaluate(state);
    }


    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = state.relocation(successor[i], next_house);
        GameState next_state(next_house);
        if (more_action) {
            next_state.whoes_turn = state.whoes_turn;
            value = minValue(next_state, depth - 2, alpha, beta, &a);
        } else {
            next_state.whoes_turn = !state.whoes_turn;
            value = maxValue(next_state, depth - 1, alpha, beta, &a);
        }
        if (beta > value) {
            beta = value;
            *action = successor[i];
        }
        if (beta <= alpha) {
            return beta;
        }
    }
    return beta;
}
void test_minimax() {
    int ts;
    std::cin >> ts;
    while (ts--) {
        int house[14];
        int depthMAX;
        for (size_t i = 0; i < 14; i++) {
            std::cin >> house[i];
        }
        std::cin >> depthMAX;
        GameState state(house);
        state.whoes_turn = true;
        std::cout << minimaxDecision(state, depthMAX) << std::endl;
    }
    return;
}
}  // namespace ai
