//
// Created by chongyuyuan on 2020/3/18.
//

#ifndef A5_REVERSI_H
#define A5_REVERSI_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Reversi{
private:
    const static int board_size = 8;
    int board[board_size][board_size];
    int white_count;
    int black_count;

public:
    Reversi(){
        init();
    };//constructor
    Reversi(const Reversi &rhs){
        for(int i = 0;i<board_size;i++){
            for(int j = 0;j<board_size;j++){
                board[i][j] = rhs.board[i][j];
            }
        }
        white_count = rhs.white_count;
        black_count = rhs.black_count;
    };//copy constructor

    void init();
    void set_tail(int x, int y, int tile);
    int get_board_size(){
        return board_size;
    }
    int **getboard(){
        int **copy_board = new int*[board_size];
        for(int i = 0;i<board_size;i++){
            copy_board[i] = new int[board_size];
        }

        for(int i = 0;i<board_size;i++){
            for(int j = 0;j<board_size;j++){
                copy_board[i][j] = board[i][j];
            }
        }
        return copy_board;
    }
    bool is_onboard(int x,int y);
    vector<int> get_tailtoflip(int x,int y, int tile);
    vector<int> get_vaildindex(int tile);
    bool isvaildmove(int x,int y, int tile);
    void flip_the_tail(int x, int y, int tile);
    int checkWin(int tail);
    int get_whitecount();
    int get_blackcount();
    void display();

};
#endif //A5_REVERSI_H
