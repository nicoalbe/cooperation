#include <iostream>
#include <fstream>
#include <string>
#include "strategies.h"
using namespace std;
/*
    WHEN ADDING A NEW STRATEGY:
    1) increase the const int tot_strategies
    2) add a case in switch(n_strategy)
    3) add name in strategies_names
*/

const int tot_moves=100;
const int tot_strategies=16;

int callStrategy(int n_strategy, int *prev_moves, int n_prev_moves, int current_player){
    int choice=0;
    switch(n_strategy){
        case 0:
            choice=always_nice(prev_moves, n_prev_moves, tot_moves, current_player);
        break;
        case 1:
            choice=always_mean(prev_moves, n_prev_moves, tot_moves, current_player);
        break;
        case 2:
            choice=tit_for_tat(prev_moves, n_prev_moves, tot_moves, current_player);
            break;
        case 3:
            choice=nice_not_twice(prev_moves, n_prev_moves, tot_moves, current_player);
            break;
        case 4:
            choice=random(prev_moves, n_prev_moves, tot_moves, current_player);
            break;
        case 5:
            choice=you_didnt(prev_moves, n_prev_moves, tot_moves, current_player);
            break;
        case 6:
            choice=i_remember(prev_moves, n_prev_moves, tot_moves, current_player);
            break;
        case 7:
            choice=increasing(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 8:
            choice=titfor2tat(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 9:
            choice=detective(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 10:
            choice=simpleton(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 11:
            choice=super_detective(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 12:
            choice=mean_schizophrenic(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 13:
            choice=nice_schizophrenic(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 14:
            choice=twin_for_tat(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
        case 15:
            choice=not_forever(prev_moves,n_prev_moves,tot_moves,current_player);
            break;
    }
    return choice;
}

int main() {
    string strategies_names[tot_strategies]={
        "always nice",
        "always mean",
        "tit for tat",
        "nice not twice",
        "random",
        "you didn't",
        "I remember",
        "increasing",
        "titfor2tat",
        "detective",
        "simpleton",
        "superdetective",
        "mean schizophrenic",
        "nice schizophrenic",
        "twin for tat",
        "not forever"
    };
    ofstream games("games.txt");

    
    //start tournament
    int choice_one,choice_two;
    //store in scores[i][j] how many points strategy i did playing with strategy j
    int scores[tot_strategies*tot_strategies];
    for(int i=0;i<tot_strategies;i++)
        for(int j=0;j<tot_strategies;j++)
            scores[i*tot_strategies+j]=0;
    //store in moves[i][j] the jth move of strategy i (one or two) in the game 
    int moves[tot_moves*2];
    for(int i=0;i<tot_strategies;i++){
        for(int j=i;j<tot_strategies;j++){
            games<<strategies_names[i]<<" vs "<<strategies_names[j]<<endl;
            for(int k=0;k<tot_moves;k++){
                //each one make your choice
                choice_one=callStrategy(i,moves,k,0);
                choice_two=callStrategy(j,moves,k,1);
                //store the choices
                moves[0*tot_moves+k]=choice_one;
                moves[1*tot_moves+k]=choice_two;

                games<<choice_one<<" - "<<choice_two<<endl;

                //compute points
                if(choice_one+choice_two==0){
                    //both cooperate
                    scores[i*tot_strategies+j]+=3;
                    scores[j*tot_strategies+i]+=3;
                } else if(choice_one+choice_two==2){
                    //both defect
                    scores[i*tot_strategies+j]+=1;
                    scores[j*tot_strategies+i]+=1;
                } else if(choice_one==1){
                    //one defect while two cooperates
                    scores[i*tot_strategies+j]+=5;
                    scores[j*tot_strategies+i]+=0;

                } else {
                    //one cooperate while two defects
                    scores[i*tot_strategies+j]+=0;
                    scores[j*tot_strategies+i]+=5;
                }
            }
            if(i==j){
                scores[i*tot_strategies+i]=scores[i*tot_strategies+i]/2;
            }
            games<<"scores"<<endl;
            games<<strategies_names[i]<<": "<<scores[i*tot_strategies+j]<<endl;
            games<<strategies_names[j]<<": "<<scores[j*tot_strategies+i]<<endl<<endl;
        }
    }
    games.close();

    /*IMPORTANT: For implementation choices, 
    the score of each strategy when playing against itself (as one and  as two)
    is calculated as the average of the scores of one and two.
    Most of the time this choice is correct, as the two players with the same strategy make the same points,
    but is not always true, like in the case of the random strategy.
    */

    //compute average points
    double average_points[tot_strategies];
    double average_temp=0;
    for(int i=0;i<tot_strategies;i++){
        average_temp=0;
        for(int j=0;j<tot_strategies;j++){
            average_temp+=scores[i*tot_strategies+j];
        }
        average_points[i]=average_temp/tot_strategies;
    }

    //bubble sort! (in decreasing order)
    bool swapped=true;
    int int_tmp;
    string s_tmp;
    while(swapped){
        swapped=false;
        for(int i=0;i<tot_strategies-1;i++){
            if(average_points[i]<average_points[i+1]){
                swapped=true;
                
                int_tmp=average_points[i];
                average_points[i]=average_points[i+1];
                average_points[i+1]=int_tmp;

                s_tmp=strategies_names[i];
                strategies_names[i]=strategies_names[i+1];
                strategies_names[i+1]=s_tmp;
            }
        }
    }
    
    ofstream results("results.txt");

    for(int i=0;i<tot_strategies;i++){
        results<<"#"<<i+1<<": "<<strategies_names[i]<<" with "<<average_points[i]<<" points";
        results<<endl;
    }
    results.close();

    return 0;
}
