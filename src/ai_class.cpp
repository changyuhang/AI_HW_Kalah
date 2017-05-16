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
    minimaxValue(state, depth, alpha, beta, &action);
    return action;
}
int minimaxValue(GameState const &state, int depth, int alpha, int beta, int *action) {
    if (depth <= 0) {
        return evaluate(state);
    }
    std::vector<GameState> possible_state;
    state.findPossibleAction(possible_state);
    if (possible_state.empty()) {
        GameState temp(state);
        temp.finalScoring();
        return evaluate(temp);
    }

    if (state.whoes_turn == state.computer) {
        for (const GameState &next_state : possible_state) {
            int a, value;
            if (next_state.whoes_turn == state.whoes_turn) {
                value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
            } else {
                value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
            }
            if (alpha < value) {
                alpha = value;
                *action = next_state.action;
            }
            if (beta <= alpha) {
                return beta;
            }
        }
        return alpha;
    } else {
        for (const GameState &next_state : possible_state) {
            int a, value;
            if (next_state.whoes_turn == state.whoes_turn) {
                value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
            } else {
                value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
            }
            if (beta > value) {
                beta = value;
                *action = next_state.action;
            }
            if (beta <= alpha) {
                return alpha;
            }
        }
        return beta;
    }
}
// int minimaxValue(GameState const &state, int depth, int alpha, int beta, int *action) {
//     if (depth <= 0) {
//         return evaluate(state);
//     }
//     int successor[6];
//     int possible_actions = state.listSuccessors(successor);
//     if (possible_actions == 0) {
//         return evaluate(state);
//     }
//     if (state.whoes_turn == state.computer) {
//         for (size_t i = 0; i < possible_actions; i++) {
//             int next_house[14];
//             int value, a;
//             bool more_action = state.relocation(successor[i], next_house);
//             GameState next_state(state);
//             next_state.nextState(successor[i]);
//             if (more_action) {
//                 value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
//             } else {
//                 value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
//             }
//             if (alpha < value) {
//                 alpha = value;
//                 *action = successor[i];
//             }
//             if (beta <= alpha) {
//                 return beta;
//             }
//         }
//         return alpha;
//     } else {
//         for (size_t i = 0; i < possible_actions; i++) {
//             int next_house[14];
//             int value, a;
//             bool more_action = state.relocation(successor[i], next_house);
//             GameState next_state(state);
//             next_state.nextState(successor[i]);
//             if (more_action) {
//                 value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
//             } else {
//                 value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
//             }
//             if (beta > value) {
//                 beta = value;
//                 *action = successor[i];
//             }
//             if (beta <= alpha) {
//                 return alpha;
//             }
//         }
//         return beta;
//     }
// }

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
