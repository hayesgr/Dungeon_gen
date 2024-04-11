#ifndef ROOM_H
#define ROOM_H
#include<cstdio>
#include<cstdlib>

typedef struct rm{
    int x,y,w,h;
    int neighbors[4];
    int neighbor_count=0;
    bool visited = false;
}Room;

void room_gen(Room &room,int x, int y);
#endif // ROOM_H
