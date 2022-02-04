#include <iostream>
#include <string>
#include "Reversi.h"
#include "MCTS.h"
#include "heuMCTS.h"
using namespace std;
void user_play(Reversi &R,int tile);
int main() {
    cout<<"**     welcome to ChongyuYuan(301354567)'s Reversi game (it's)     **"<<endl<<endl;
    cout<<"if you want to play against computer, enter 1, if you want to watch AI(with heuristics) play against AI(without heuristics), enter 2: "<<endl;
    int x;
    while(true){
        cin>>x;
        if(cin.fail()){
            cout<<"not a number, please enter again!"<<endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        if(x!=1&&x!=2){
            cout<<"not a correct number, please enter again!"<<endl;
            continue;
        }
        else{
            break;
        }
    }
    if(x == 2){
        cout<<"if you want AI(with heuristics) to play black(X), choose 2 and play first, if you want AI(with heuristics) to play white(O), choose 1 and play later:"<<endl;
        int user_decision;
        while(true){
            cin>>user_decision;
            if(cin.fail()){
                cout<<"not a number, please enter again!"<<endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            if(user_decision!=1&&user_decision!=2){
                cout<<"not a correct number, please enter again!"<<endl;
                continue;
            }
            else{
                break;
            }
        }
//    Reversi R;
//    R.init();
//    R.display();
//    R.set_tail(4,2,1);
//    R.flip_the_tail(4,2,1);
//    R.display();
//    int x = Monte_Carlo_Tree_Search_with_heu(R,2);
//    Monte_Carlo_Tree_Search_with_heu(R,1);
//    for(int i = 0;i<8;i++){
//        for(int j = 0;j<8;j++){
//            R.set_tail(i,j,1);
//        }
//    }
//    R.display();
//
        int computer = 0;
        int player = 0;
        int tie = 0;
        for(int x = 0;x<20;x++){
            Reversi R;
            R.init();
            R.display();
            int computer_decision = 3-user_decision;
            if(user_decision == 1){
                int whos_turn = 2;
                while(true){
                    if(whos_turn == computer_decision){
                        if(R.get_vaildindex(computer_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"AI without heuristics has no where to play, it's turn to AI with heuristics!"<<endl;
                            continue;
                        }
                        int computer_think_result = Pure_Monte_Carlo_Tree_Search(R,1);
                        R.set_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.flip_the_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"AI without heuristics win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                computer ++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"AI with heuristics win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                player ++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                tie ++;
                                break;
                            }

                        }
                    }
                    else{
                        if(R.get_vaildindex(user_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"AI with heuristics have no where to play,it's turn to AI without heuristics!"<<endl;
                            continue;
                        }
//                user_play(R,user_decision);
                        int computer_think_result2 = Monte_Carlo_Tree_Search_with_heu(R,2);
                        R.set_tail((computer_think_result2/10),(computer_think_result2%10),user_decision);
                        R.flip_the_tail((computer_think_result2/10),(computer_think_result2%10),user_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"AI without heuristics win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                computer ++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"AI with heuristics win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                player++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                tie++;
                                break;
                            }
                        }
                    }
                }
            }
            else{
                int whos_turn = 2;
                while(true){
                    if(whos_turn == computer_decision){
                        if(R.get_vaildindex(computer_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"computer has no where to play, it's turn to you!"<<endl;
                            continue;
                        }
                        int computer_think_result = Pure_Monte_Carlo_Tree_Search(R,2);
                        R.set_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.flip_the_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                computer++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                player++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                tie++;
                                break;
                            }

                        }
                    }
                    else{
                        if(R.get_vaildindex(user_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"you have no where to play,it's turn to computer!"<<endl;
                            continue;
                        }
//                user_play(R,user_decision);
                        int computer_think_result2 = Monte_Carlo_Tree_Search_with_heu(R,1);
                        R.set_tail((computer_think_result2/10),(computer_think_result2%10),user_decision);
                        R.flip_the_tail((computer_think_result2/10),(computer_think_result2%10),user_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                computer++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                player++;
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                tie++;
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout<<"computer wins: "<<computer<<endl;
        cout<<"player wins: "<<player<<endl;
        cout<<"ties: "<<tie<<endl;
    }
    else{
        cout<<"if you want to play black(X), choose 2 and play first, if you want to play white(O), choose 1 and play later:"<<endl;
        int user_decision;
        while(true){
            cin>>user_decision;
            if(cin.fail()){
                cout<<"not a number, please enter again!"<<endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            if(user_decision!=1&&user_decision!=2){
                cout<<"not a correct number, please enter again!"<<endl;
                continue;
            }
            else{
                break;
            }
        }
//    Reversi R;
//    R.init();
//    R.display();
//    R.set_tail(4,2,1);
//    R.flip_the_tail(4,2,1);
//    R.display();
//    int x = Monte_Carlo_Tree_Search_with_heu(R,2);
//    Monte_Carlo_Tree_Search_with_heu(R,1);
//    for(int i = 0;i<8;i++){
//        for(int j = 0;j<8;j++){
//            R.set_tail(i,j,1);
//        }
//    }
//    R.display();
//
            Reversi R;
            R.init();
            R.display();
            int computer_decision = 3-user_decision;
            if(user_decision == 1){
                int whos_turn = 2;
                while(true){
                    if(whos_turn == computer_decision){
                        if(R.get_vaildindex(computer_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"computer has no where to play, it's turn to you!"<<endl;
                            continue;
                        }
                        int computer_think_result = Monte_Carlo_Tree_Search_with_heu(R,1);
                        R.set_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.flip_the_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }

                        }
                    }
                    else{
                        if(R.get_vaildindex(user_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"you have no where to play,it's turn to computer!"<<endl;
                            continue;
                        }
//                user_play(R,user_decision);
                        user_play(R,1);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                        }
                    }
                }
            }
            else{
                int whos_turn = 2;
                while(true){
                    if(whos_turn == computer_decision){
                        if(R.get_vaildindex(computer_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"computer has no where to play, it's turn to you!"<<endl;
                            continue;
                        }
                        int computer_think_result = Monte_Carlo_Tree_Search_with_heu(R,2);
                        R.set_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.flip_the_tail((computer_think_result/10),(computer_think_result%10),computer_decision);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }

                        }
                    }
                    else{
                        if(R.get_vaildindex(user_decision).empty()){
                            whos_turn = 3-whos_turn;
                            cout<<"you have no where to play,it's turn to computer!"<<endl;
                            continue;
                        }
//                user_play(R,user_decision);
                        user_play(R,2);
                        R.display();
                        whos_turn = 3-whos_turn;
                        if(R.checkWin(computer_decision)!=3){
                            if(R.checkWin(computer_decision) == computer_decision){
                                cout<<"computer win!!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == user_decision){
                                cout<<"player win!!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                            if(R.checkWin(computer_decision) == 0){
                                cout<<"it's a tie!"<<endl;
                                cout<<"black count: "<<R.get_blackcount();
                                cout<<"white count: "<<R.get_whitecount();
                                break;
                            }
                        }
                    }
                }
            }
    }

    return 0;
}
void user_play(Reversi &R, int tile){
    int where_to_play;
    cout<<"please enter the 2-digits index of row and column that you want to play on(e.g. 37 means you want to play on row 3 and column 7):"<<endl;
    while(true){
        cin>>where_to_play;
        if(cin.fail()){
            cout<<"error: not a number, please enter again!"<<endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        if(!R.is_onboard((where_to_play/10),(where_to_play%10))){
            cout<<"error: not on the board, please enter again!"<<endl;
            continue;
        }
        if(R.getboard()[where_to_play/10][where_to_play%10] == 1){
            cout<<"error: there's already \"O\" on it, please enter again!"<<endl;
            continue;
        }
        if(R.getboard()[where_to_play/10][where_to_play%10] == 2){
            cout<<"error: there's already \"X\" on it, please enter again!"<<endl;
            continue;
        }
        if(!R.isvaildmove((where_to_play/10),(where_to_play%10),tile)){
            cout<<"error: it's not a valid move, please enter again!"<<endl;
            continue;
        }
        else{
            break;
        }
    }
    R.set_tail((where_to_play/10),(where_to_play%10),tile);
    R.flip_the_tail((where_to_play/10),(where_to_play%10),tile);
}
