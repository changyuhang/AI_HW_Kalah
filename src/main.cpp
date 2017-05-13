#include "game_state_class.h"
#include "ai_class.h"
#include <string>

int getNextAction(GameState state) {
    int action;
    while (std::cin >> action) {
        if (action >= state.player_store[state.human]) {
            std::cout << "You cannot take seeds from house#";
        } else if (state.house[action] == 0) {
            std::cout << "There is no seed in house#";
        } else {
            std::cout << "Your choice is house#";
            std::cout << action << "." << std::endl;
            break;
        }
        std::cout << action << "." << std::endl;
    }
    return action;
}

int main(int argc, char const *argv[]) {
    int seeds;
    int depth;
    int house[14] = {};
    std::string playerFirst;
    bool player;        // false = human, true = computer

    std::cout << "The number of the seeds in one bowl at the beginning:";
    while (std::cin >> seeds) {
        if (seeds > 0) break;
        std::cout << "輸入錯誤！請重新輸入大於0的數字:";
    }
    std::cout << "The depth:";
    while (std::cin >> depth) {
        if (depth > 0) break;
        std::cout << "輸入錯誤！請重新輸入大於0的數字:";
    }
    std::cout << "Who plays first? The human or the computer?";
    while (std::cin >> playerFirst) {
        if (playerFirst == "human") {
            player = false;
            break;
        } else if (playerFirst == "computer") {
            player = true;
        }
        std::cout << "輸入錯誤！請輸入human或是computer:";
    }

    GameState state(seeds);
    while (!state.noFurtherAction()) {
        bool more_action;
        state.printState();
        if (player) {
            std::cout << "ai" << std::endl;
            more_action = state.nextState(ai::minimaxDecision(state, depth));
        } else {
            std::cout << "human" << std::endl;
            more_action = state.nextState(getNextAction(state));
        }
        if (more_action == false) {
            player = !player;
        }
    }

    return 0;
}
