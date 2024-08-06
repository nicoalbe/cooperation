#include <random>
#include <ctime>
#include "strategies.h"
/*
    0 is cooperating
    1 is defecting

    prev_moves is an array of dimensions [2][n_prev_moves]
    in position prev_moves[i][j] is stored the jth move of strategy i. (i can be one or two)
    current_player tells you if the strategy is playing as player one or player two
*/
int always_nice(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    return choice;
}

int always_mean(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=1;
    return choice;
}

//first move is cooperating, then always do what your opponent did in its previous move
int tit_for_tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves==0) return 0;

    int oppontent_player=1-current_player;
    choice=prev_moves[oppontent_player*tot_moves+n_prev_moves-1];
    
    return choice;
}

//start with cooperation, if opponent is defecting a second time(even not in a row), defect one time.
int nice_not_twice(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves<2) return 0;

    int oppontent_player=1-current_player;
    int opponent_last_move=prev_moves[oppontent_player*tot_moves+n_prev_moves-1];

    //check if opponent just defected in last turn
    if(opponent_last_move==1){
        //if opponent defected, check is it's his second time defecting (even number of total defects)
        int defects_count=0;
        for(int k=0;k<n_prev_moves;k++){
            if(prev_moves[oppontent_player*tot_moves+k]==1)
                defects_count++;
        }
        if(defects_count%2==0){
            //defect only if he's defecting for a second time
            choice=1;
        }else{
            choice=0;
        }
    } else {
        choice=0;
    }
    
    return choice;
}

int random(int *prev_moves, int n_prev_moves, int tot_moves, int current_player) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    return dist(gen);
}

//start by collaborating, but as soon as your opponent defect, always defect
int you_didnt(int *prev_moves, int n_prev_moves, int tot_moves, int current_player) {
    int choice=0;
    if(n_prev_moves==0) return 0;

    int oppontent_player=1-current_player;
    int defects_count=0;
    for(int k=0;k<n_prev_moves;k++){
        if(prev_moves[oppontent_player*tot_moves+k]==1)
            defects_count++;
    }
    if(defects_count>0) choice=1;

    return choice;
}

//start being mean, then look at all the past moves, do what was the most common move of your opponent
int i_remember(int *prev_moves, int n_prev_moves, int tot_moves, int current_player) {
    int choice=0;
    if(n_prev_moves==0) return 1;

    int oppontent_player=1-current_player;
    int defects_count=0;
    for(int k=0;k<n_prev_moves;k++){
        if(prev_moves[oppontent_player*tot_moves+k]==1)
            defects_count++;
    }

    if(defects_count>=(n_prev_moves/2)) choice=1;
    else choice=0;

    return choice;
}

int increasing(int *prev_moves, int n_prev_moves, int tot_moves, int current_player) {
    int choice=0;
    
    //k is the consecutive mean counter
    int k=0,k_count=0;
    int moves[tot_moves];
    for(int i=0;i<tot_moves;i++){
        if(k_count==k){
            moves[i]=0;
            k++;
            k_count=0;
        }
        else{
            moves[i]=1;
            k_count++;
        }
    }
    choice=moves[n_prev_moves];
    return choice;
}

//defect only if your opponent defected twice in a row
int titfor2tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves<2) return 0;

    int oppontent_player=1-current_player;
    int opp_last_choice=prev_moves[oppontent_player*tot_moves+n_prev_moves-1];
    int opp_second_last_choice=prev_moves[oppontent_player*tot_moves+n_prev_moves-2];

    if(opp_last_choice * opp_second_last_choice==0){
        choice=0;
    }else{
        choice=1;
    }
    
    return choice;
}

//start with nice-mean-nice-nice, then if opponent was ever mean, it acts as titfortat, otherwise as always mean.
int detective(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves<4){
        //study opponent
        int moves[4]={0,1,0,0};
        choice=moves[n_prev_moves];
    } else{
        //how did opponent played in the first 4 moves?
        int oppontent_player=1-current_player;
        bool opp_nice=true;
        for(int i=0;i<4;i++){
           if(prev_moves[oppontent_player*tot_moves+i]==1){
                opp_nice=false;
           }
        }
        if(opp_nice){
            choice=always_mean(prev_moves, n_prev_moves, tot_moves, current_player);
        }else{
            choice=tit_for_tat(prev_moves, n_prev_moves, tot_moves, current_player);
        }
    }
    return choice;
}

//Start by cooperating, if opp cooperates, it does the same as last move. If opp defect, it does the opposite of last move
int simpleton(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){

    int choice=0;
    if(n_prev_moves==0) return 0;

    int oppontent_player=1-current_player;
    int opp_last_choice=prev_moves[oppontent_player*tot_moves+n_prev_moves-1];
    int my_last_choice=prev_moves[current_player*tot_moves+n_prev_moves-1];

    if(opp_last_choice==0){
        choice=my_last_choice;
    }else{
        choice=1-my_last_choice;
    }

    return choice;
}

//As detective, but keeps studying the last 4 opponent moves
int super_detective(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves<4){
        //study opponent
        int moves[4]={0,1,0,0};
        choice=moves[n_prev_moves];
    } else{
        //how did opponent played in the last 4 moves?
        int oppontent_player=1-current_player;
        bool opp_nice=true;
        for(int i=1;i<=4;i++){
           if(prev_moves[oppontent_player*tot_moves+n_prev_moves-i]==1){
                opp_nice=false;
           }
        }
        if(opp_nice){
            choice=always_mean(prev_moves, n_prev_moves, tot_moves, current_player);
        }else{
            choice=tit_for_tat(prev_moves, n_prev_moves, tot_moves, current_player);
        }
    }
    return choice;
}

//It alternates (every 3 moves) between acting as: alwaysmean, youdidnt and increasing
int mean_schizophrenic(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    int personality=n_prev_moves%9;
    
    if(personality<3){
        choice=always_mean(prev_moves, n_prev_moves, tot_moves, current_player);
    }else if(personality<6){
        choice=you_didnt(prev_moves, n_prev_moves, tot_moves, current_player);
    }else{
        choice=increasing(prev_moves, n_prev_moves, tot_moves, current_player);
    }

    return choice;
}

//It alternates (every 3 moves) between acting as: alwaysnice, titfor2tat, nicenottwice
int nice_schizophrenic(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    int personality=n_prev_moves%9;
    
    if(personality<3){
        choice=always_nice(prev_moves, n_prev_moves, tot_moves, current_player);
    }else if(personality<6){
        choice=titfor2tat(prev_moves, n_prev_moves, tot_moves, current_player);
    }else{
        choice=nice_not_twice(prev_moves, n_prev_moves, tot_moves, current_player);
    }

    return choice;
}

//It plays the opposite move of the opponent. It's the opposite of titfortat
int twin_for_tat(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves==0) return 0;

    int oppontent_player=1-current_player;
    choice=1-prev_moves[oppontent_player*tot_moves+n_prev_moves-1];
    
    return choice;
}

//Tit for tat but if opponent plays 20 defect moves, be always mean
int not_forever(int *prev_moves, int n_prev_moves, int tot_moves, int current_player){
    int choice=0;
    if(n_prev_moves==0) return 0;

    int oppontent_player=1-current_player;
    choice=prev_moves[oppontent_player*tot_moves+n_prev_moves-1];

    int defects_count=0;
    for(int k=0;k<n_prev_moves;k++){
        if(prev_moves[oppontent_player*tot_moves+k]==1)
            defects_count++;
    }
    if(defects_count>=20) choice=1;
    
    return choice;
}