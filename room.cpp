#include "room.h"

void room_gen(Room &room,int x, int y){
    room.visited=false;
    //int top[20]={0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4};
    int top[20]={0,1,2,3,4,0,1,2,3,4,0,1,2,3,0,1,2,3,1,1};
    //int bot[20]={6,6,7,7,7,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10};
    int bot[20]={6,7,8,9,10,6,7,8,9,10,7,8,9,10,7,8,9,10,9,10};
    int tx = top[rand()%20];//rand()%5;
    int ty = top[rand()%20];//rand()%5;
    int bx = bot[rand()%20];//rand()%5+6;
    int by = bot[rand()%20];//rand()%5+6;
    int r=0;
    //bx = bx-tx>3?bx:tx+3;
    r = rand()%2;
    if(bx-tx<4){
        bx = r==0?tx+4:bx;
        tx = r==0?tx:bx-4;
    }
    //by = by-ty>3?by:ty+3;
    if(by-ty<4){
        by = r==1?ty+4:by;
        ty = r==1?ty:by-4;
    }
    room.x=tx;room.y=ty;
    room.w=(bx)-(tx);room.h=(by)-(ty);
    room.neighbor_count=0;
    if (y>0){room.neighbors[room.neighbor_count]=((y-1)*16)+x;room.neighbor_count++;}    //top
    if (x<15){room.neighbors[room.neighbor_count]=(y*16)+x+1;room.neighbor_count++;}      //right
    if (y<15){room.neighbors[room.neighbor_count]=((y+1)*16)+x;room.neighbor_count++;}    //bottom
    if (x>0){room.neighbors[room.neighbor_count]=(y*16)+x-1;room.neighbor_count++;}      //left
    //printf("x:%d\ty:%d\tw:%d\th:%d\n",room.x,room.y,room.w,room.h);
    //for(int i=0;i<room.neighbor_count;i++){
    //    printf("neightbor %d:%d\n",i,room.neighbors[i]);
    //}
}



