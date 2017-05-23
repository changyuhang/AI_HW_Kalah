#include "ai_class.h"
namespace ai {
int c = 0;
clock_t time = 0;
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
    c++;
    if (depth <= 0) {
        return evaluate(state);
    }
    std::vector<GameState> possible_state;
    clock_t t;
    t = clock();
    state.findPossibleAction(possible_state);
    t = clock() - t;
    time += t;
    if (possible_state.empty()) {
        GameState temp(state);
        temp.finalScoring();
        return evaluate(temp);
    }

    if (state.whoes_turn == state.computer) {
        for (const GameState &next_state : possible_state) {
            int a, value;
            // if (next_state.whoes_turn == state.whoes_turn) {
            //     value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
            // } else {
            //     value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
            // }
            value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
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
            // if (next_state.whoes_turn == state.whoes_turn) {
            //     value = minimaxValue(next_state, depth - 2, alpha, beta, &a);
            // } else {
            //     value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
            // }
            value = minimaxValue(next_state, depth - 1, alpha, beta, &a);
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
        c = 0;
        time = 0;
        GameState state(house);
        state.whoes_turn = true;
        clock_t t;
        t = clock();
        std::cout << minimaxDecision(state, depthMAX) << std::endl;
        std::cout << "深度" << depthMAX << "次數" << c << std::endl;
        t = clock() - t;
        printf ("It took me %d clicks (%f seconds).\n",time,((float)time)/CLOCKS_PER_SEC);
    }
    return;
}

}  // namespace ai
