#ifndef DUNGEON_H
#define DUNGEON_H
#include "block.h"

typedef class dungeon{
public:
    int width=0,height=0;
    uint8_t* tiles;
    Block *blocks;
public:
    dungeon(){}
    ~dungeon(){if(tiles){free(tiles);}if(blocks){free(blocks);}}
    int init(int w,int h);
    int gen_blocks();
    int check_neighbors(std::vector<int> &N_stack, int current);
    int make_hall(int current,int next);
    int gen_halls(int n);
    int print();
}Dungeon;
#endif // DUNGEON_H
