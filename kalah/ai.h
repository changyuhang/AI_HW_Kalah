#ifndef AI_H_
#define AI_H_
typedef struct {
    int house[14];
    int action;
    bool more_action;
}nextState;
extern int total_seeds;
int evaluate(const int house[]);
int listSuccessors(const int house[], int successor[], bool isMaxPlayer);
bool cmp(const nextState& a, const nextState& b);
int minimaxDecision(const int house[], int depth);
int minimax(const int house[], int depth, int alpha, int beta, int *action,
            bool whoes_turn);

#endif  // AI_H_
