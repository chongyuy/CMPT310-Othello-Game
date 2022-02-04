//
// Created by chongyuyuan on 2020/3/18.
//
#include <string.h>
#include "Reversi.h"
void Reversi::init(){
    black_count = 0;
    white_count = 0;
    for(int i = 0;i<board_size;i++){
        for(int j = 0;j<board_size;j++){
            board[i][j] = 0;
        }
    }
    board[board_size/2-1][board_size/2-1] = 1;//1 denote white and 2 denote black
    board[board_size/2][board_size/2] = 1;
    board[board_size/2-1][board_size/2] = 2;
    board[board_size/2][board_size/2-1] = 2;
}
void Reversi::display() {
    cout<<"   0   1   2   3   4   5   6   7"<<endl;
    cout<<" *********************************"<<endl;
    for(int i = 0;i<board_size;i++){
        cout<<i;
        cout<<"|";
        for(int j = 0;j<board_size;j++){

            if(board[i][j] == 0){
                cout<<"   |";
            }
            else{
                if(board[i][j] == 1){
                    cout<<" O |";
                }
                if(board[i][j] == 2){
                    cout<<" X |";
                }
            }
        }
        cout<<endl;
        cout<<" *********************************";
        cout<<endl;
    }
}
int Reversi::get_whitecount() {
    for(int i = 0;i<board_size;i++){
        for(int j = 0;j<board_size;j++){
            if(board[i][j] == 1){
                white_count ++;
            }
        }
    }
    return white_count;
}
int Reversi::get_blackcount() {
    for(int i = 0;i<board_size;i++){
        for(int j = 0;j<board_size;j++){
            if(board[i][j] == 2){
                black_count ++;
            }
        }
    }
    return black_count;
}
bool Reversi::is_onboard(int x, int y) {
    if(x>=0 && x<=7 && y>=0 && y<=7){
        return true;
    }
    else{
        return false;
    }
}
void Reversi::set_tail(int x, int y, int tile) {
        board[x][y] = tile;
}
vector<int> Reversi::get_tailtoflip(int x,int y, int tile) {
    vector<int> tile_to_flip;
    int othertail = 3 - tile;
    int dir[][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    for(int i = 0;i<8;i++){
        int xtemp = x;
        int ytemp = y;
        xtemp += dir[i][0];
        ytemp += dir[i][1];
        if(is_onboard(xtemp,ytemp) && board[xtemp][ytemp] == othertail){
            xtemp += dir[i][0];
            ytemp += dir[i][1];
            if(!is_onboard(xtemp,ytemp)){
                continue;
            }
            while(board[xtemp][ytemp] == othertail){
                xtemp += dir[i][0];
                ytemp += dir[i][1];
                if(!is_onboard(xtemp,ytemp)){
                    break;
                }
            }
            if(!is_onboard(xtemp,ytemp)){
                continue;
            }
            if(board[xtemp][ytemp] == tile){
                while(true){
                    xtemp -= dir[i][0];
                    ytemp -= dir[i][1];
                    if(xtemp == x && ytemp == y){
                        break;
                    }
                    tile_to_flip.push_back(xtemp * 10 + ytemp);
                }
            }
        }
    }
    return tile_to_flip;
}
bool Reversi::isvaildmove(int x, int y, int tile) {
    if(board[x][y] != 0||!is_onboard(x,y)){
        return false;
    }
    if(get_tailtoflip( x, y, tile).size() == 0){
        return false;
    }
    return true;
}
vector<int> Reversi::get_vaildindex(int tile) {
    vector<int> vaild_index;
    for(int i = 0;i<board_size;i++){
        for(int j = 0;j<board_size;j++){
            if(isvaildmove(i,j,tile)){
                vaild_index.push_back(i*10 + j);
            }
        }
    }
    return vaild_index;
}
int Reversi::checkWin(int tail) {
    if(get_vaildindex(tail).empty() && get_vaildindex((3-tail)).empty()){
        if(get_whitecount()>get_blackcount()){
            return 1;//if white wins, return 1
        }
        else if (get_whitecount() < get_blackcount()){
            return 2;//if black wins, return 2
        } else{
            return 0;//if it's a tie, return 0
        }
    }
    return 3;//If the winner has not yet been determined, return 3;
}
void Reversi::flip_the_tail(int x, int y, int tile) {
    vector<int> tail_need_flip = get_tailtoflip(x,y,tile);
    for(int i = 0;i<tail_need_flip.size();i++){
        int xtemp = tail_need_flip[i] / 10;
        int ytemp = tail_need_flip[i] % 10;
        set_tail(xtemp,ytemp,tile);
    }
}