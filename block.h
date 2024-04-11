#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <stack>
#include <vector>
#include <cstdint>
#include "room.h"

typedef class block{
public:
    int neighbors[4];
    int neighbor_count=0;
    bool visited = false;

    uint8_t* tiles;
    Room rooms[256];
    int start_x=0,start_y=0;
public:
    block(){init();}
    ~block(){if(tiles){free(tiles);}}
    int init();
    int gen_rooms();
    int make_hall(int current,int next);
    int gen_halls(int n);
    int build(int x,int y,int w,int h);
    int print_block();
    int check_neighbors(std::vector<int> &N_stack, int current);
}Block;



#endif // BLOCK_H
