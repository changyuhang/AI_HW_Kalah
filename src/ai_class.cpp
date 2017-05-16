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
    int successor[6];
    int possible_actions = state.listSuccessors(successor);
    if (possible_actions == 0) {
        return evaluate(state);
    }

    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = state.relocation(successor[i], next_house);
        GameState next_state(state);
        next_state.nextState(successor[i]);
        if (more_action) {
            value = maxValue(next_state, depth - 2, alpha, beta, &a);
        } else {
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
    int successor[6];
    int possible_actions = state.listSuccessors(successor);

    if (possible_actions == 0) {
        return evaluate(state);
    }

    for (size_t i = 0; i < possible_actions; i++) {
        int next_house[14];
        int value, a;
        bool more_action = state.relocation(successor[i], next_house);
        GameState next_state(state);
        next_state.nextState(successor[i]);
        if (more_action) {
            value = minValue(next_state, depth - 2, alpha, beta, &a);
        } else {
            value = maxValue(next_state, depth - 1, alpha, beta, &a);
        }
        if (beta > value) {
            beta = value;
            *action = successor[i];
        }
        if (beta <= alpha) {
            return alpha;
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
