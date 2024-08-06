#ifndef STRATEGIES_H
#define STRATEGIES_H

//always cooperate
int always_nice(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//always defect
int always_mean(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//start with cooperating, then do what your opponent did on its last move
int tit_for_tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//start with cooperation, if opponent is defecting a second time(even not in a row), defect one time.
int nice_not_twice(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//play at random
int random(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//start by collaborating, but as soon as your opponent defect, always defect
int you_didnt(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//start being mean, then look at all the past moves, do what was the most common move of your opponent
int i_remember(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//do: nice-mean-nice-mean-mean-nice-mean-mean-mean-nice...
int increasing(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//defect only if your opponent defected twice in a row
int titfor2tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//start with nice-mean-nice-nice, then if opponent was ever mean, it acts as titfortat, otherwise as always mean.
int detective(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//Start by cooperating, if opp cooperates, it does the same as last move. If opp defect, it does the opposite of last move
int simpleton(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//As detective, but keeps studying the last 4 opponent moves
int super_detective(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//It alternates (every 3 moves) between acting as: alwaysmean, youdidnt and increasing
int mean_schizophrenic(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//It alternates (every 3 moves) between acting as: alwaysnice, titfor2tat, nicenottwice
int nice_schizophrenic(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//It plays the opposite move of the opponent. It's the opposite of titfortat
int twin_for_tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

//Tit for tat but if opponent plays 20 defect moves, be always mean
int not_forever(int *prev_moves, int n_prev_moves, int tot_moves, int current_player);

#endif // STRATEGIES_H