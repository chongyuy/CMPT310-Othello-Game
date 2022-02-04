//
// Created by chongyuyuan on 2020/3/18.
//

#include "heuMCTS.h"
#include <map>
#include <random>
int Monte_Carlo_Tree_Search_with_heu(Reversi &R, int user_tile){
    int weight[8][8] = {20,-3,11,8,8,11,-3,20,
                        -3,-7,-4,1,1,-4,-7,-3,
                        11,-4,2,2,2,2,-4,11,
                        8,1,2,-3,-3,2,1,8,
                        8,1,2,-3,-3,2,1,8,
                        11,-4,2,2,2,2,-4,11,
                        -3,-7,-4,1,1,-4,-7,-3,
                        20,-3,11,8,8,11,-3,20};
    int user_decision = user_tile;
    int computer_decision = 3 - user_decision;

    vector<int> possible_move = R.get_vaildindex(computer_decision);
    //for DEBUG
//    for(int i = 0;i<possible_move.size();i++){
//        cout<<possible_move[i]<<endl;
//    }
    map<int,int> score_sum = {};
    for(int i : possible_move){
        score_sum[i] = weight[i/10][i%10]*5 + R.get_tailtoflip((i/10),(i%10),computer_decision).size() ;
    }

    //for DEBUG
//    map<int, int>::iterator iter;
//    iter = score_sum.begin();
//    for( iter = score_sum.begin(); iter != score_sum.end(); iter++) {
//        cout << iter->first << " : " << iter->second << endl;
//    }
    for(int i : possible_move){
        Reversi X = R;
        vector<int> copy_possible_move = R.get_vaildindex(computer_decision);
        X.set_tail((i/10),(i%10),computer_decision);
        X.flip_the_tail((i/10),(i%10),computer_decision);
        //play 1000 times in one possible index
        for(int j = 0;j<150;j++){
            //if the game ends
            if(X.checkWin(computer_decision)!=3){
                if(X.checkWin(computer_decision) == computer_decision){
                    score_sum[i] = score_sum[i] + 100;
                } else if (X.checkWin(computer_decision) == (3-computer_decision)){
                    score_sum[i] = score_sum[i] - 100;
                }
                else{
                    score_sum[i] = score_sum[i] - 0;
                }
                continue;
            }
            //if the game did not end, then computer play with itself
            Reversi X_copy = X;
            //every k is for one role to play one step, there's totally 64 grid, so 70 will be enough
            //computer decision is still stand for computer and user decision is stand
            int whos_turn = user_decision;
            for(int k = 0;k<100;k++){
                //if there's no available index for current player to play, then move to another player;
                if(X_copy.get_vaildindex(whos_turn).empty()){
                    whos_turn = 3-whos_turn;
                    continue;
                }
                else{
                    vector<int> copy_poss_move = X_copy.get_vaildindex(whos_turn);
                    shuffle(copy_poss_move.begin(),copy_poss_move.end(), std::mt19937(std::random_device()()));
                    X_copy.set_tail((copy_poss_move[0]/10),(copy_poss_move[0]%10),whos_turn);
                    X_copy.flip_the_tail((copy_poss_move[0]/10),(copy_poss_move[0]%10),whos_turn);

//                    vector<int> copy_poss_move = X_copy.get_vaildindex(whos_turn);

//                    for(int c : copy_poss_move){
//                        if(X_copy.get_tailtoflip((c/10),(c%10),whos_turn).size()>largest_flip){
//                            largest_flip = X_copy.get_tailtoflip((c/10),(c%10),whos_turn).size();
//                            largest_index = c;
//                        }
//                    }
//                    X_copy.set_tail((largest_index/10),(largest_index%10),whos_turn);
//                    X_copy.flip_the_tail((largest_index/10),(largest_index%10),whos_turn);
                    //if the winner has been already decided
                    if(X_copy.checkWin(computer_decision)!=3){
                        if(X_copy.checkWin(computer_decision) == computer_decision){
                            score_sum[i] = score_sum[i] + 100;
                        } else if (X_copy.checkWin(computer_decision) == (3-computer_decision)){
                            score_sum[i] = score_sum[i] - 100;
                        }
                        else{
                            score_sum[i] = score_sum[i] - 0;
                        }
                        break;
                    }
                    //else if the winner has not been decided, continue to play with itself
                    whos_turn = 3-whos_turn;
                }

            }
        }
    }
    map<int, int>::iterator iter;
    iter = score_sum.begin();
    int temp1 = iter->second;
    int temp2 = iter->first;
    for( iter = score_sum.begin(); iter != score_sum.end(); iter++) {
//        cout << iter->first << " : " << iter->second << endl;
        if(iter->second>temp1){
            temp1 = iter->second;
            temp2 = iter->first;
        }
    }
    return temp2;
}