#include "block.h"
int block::init(){
    tiles = (uint8_t*)malloc(sizeof(uint8_t)*121*256);
    if(tiles){return 1;}
    return 0;
}

int block::gen_rooms(){
    int xx,yy,ww,hh,room_id;
    int wall,floor;
    int tilenum=0;
    for(int ry=0;ry<16;ry++){
        for(int rx=0;rx<16;rx++){
            wall = rand()%4+1;
            floor = rand()%6+32;
            room_id = ry*16+rx;
            room_gen(rooms[room_id],rx,ry);
            for(int y=0;y<11;y++){
                for(int x=0;x<11;x++){
                    tilenum=ry*(11*176)+(rx*11)+(y*176)+x;
                    tiles[tilenum]=0;
                    xx=rooms[room_id].x;
                    yy=rooms[room_id].y;
                    ww=rooms[room_id].w;
                    hh=rooms[room_id].h;
                    if(x>=xx && y>=yy && x<=xx+ww && y<=yy+hh){
                        tiles[tilenum]=wall;//marks walls
                    }
                    if(x>xx && x<xx+ww && y>yy && y<yy+hh){
                        tiles[tilenum]=floor;//marks floors
                    }
                    //if(x==5 && y==5){
                    //    tiles[tilenum]=5;//marks center
                    //}
                }//for x
            }//for y
        }//for rx
    }//for ry
    return 0;
}

int block::check_neighbors(std::vector<int> &N_stack, int current){
    for(int i=0;i<rooms[current].neighbor_count;i++){
        if(!rooms[rooms[current].neighbors[i]].visited){N_stack.emplace_back(rooms[current].neighbors[i]);}
    }
    return N_stack.size();
}
int block::make_hall(int current,int next){
    int A=0,Ax=0,Ay=0,B=0,dir=0;
    int cx = current%16;
    int cy = current/16;
    int nx = next%16;
    int ny = next/16;
    int roomoffset=0;
    if(cx<nx){A=current;Ax=cx;Ay=cy;B=next;dir=0;}
    if(cx>nx){B=current;A=next;Ax=nx;Ay=ny;dir=0;}
    if(cy<ny){A=current;Ax=cx;Ay=cy;B=next;dir=1;}
    if(cy>ny){B=current;A=next;Ax=nx;Ay=ny;dir=1;}
    if(dir==0){ //Horizontal
        int startx = rooms[A].x+rooms[A].w;
        int endx = rooms[B].x+1;

        int tyofA = rooms[A].y+1;
        int byofA = rooms[A].y+rooms[A].h-2;
        int tyofB = rooms[B].y+1;
        int byofB = rooms[B].y+rooms[B].h-2;
        int ty = tyofA>tyofB?tyofA:tyofB;
        int by = byofA<byofB?byofA:byofB;
        int length = (11-startx)+endx;
        int ky = (5-ty>by-5)?ty:by;
        roomoffset=Ay*(11*176)+(Ax*11);
        for(int x=0;x<length;x++){
            if(tiles[roomoffset+((ky-1)*176)+startx+x]==0){tiles[roomoffset+((ky-1)*176)+startx+x]=1;}
            tiles[roomoffset+(ky*176)+startx+x]=35;
            if(tiles[roomoffset+((ky+1)*176)+startx+x]==0){tiles[roomoffset+((ky+1)*176)+startx+x]=1;}
        }
    }
    else {      //vertical
        int starty = rooms[A].y+rooms[A].h;
        int endy = rooms[B].y+1;

        int lxofA = rooms[A].x+1;
        int rxofA = rooms[A].x+rooms[A].w-2;
        int lxofB = rooms[B].x+1;
        int rxofB = rooms[B].x+rooms[B].w-2;
        int lx = lxofA>lxofB?lxofA:lxofB;
        int rx = rxofA<rxofB?rxofA:rxofB;
        int length = (11-starty)+endy;
        int kx = (5-lx>rx-5)?lx:rx;
        roomoffset=Ay*(11*176)+(Ax*11);
        for(int y=0;y<length;y++){
            if(tiles[roomoffset+((starty+y)*176)+kx-1]==0){tiles[roomoffset+((starty+y)*176)+kx-1]=1;}
            tiles[roomoffset+((starty+y)*176)+kx]=35;
            if(tiles[roomoffset+((starty+y)*176)+kx+1]==0){tiles[roomoffset+((starty+y)*176)+kx+1]=1;}
        }
    }
    return 0;
}

int block::gen_halls(int n=0){
    std::stack<int> stackA;
    int current = n;
    rooms[current].visited=true;
    int visited_rooms=1;
    std::vector<int> N_stack;
    while(visited_rooms<256){
        //check neighbors
        check_neighbors(N_stack,current);
        //select unvisited neighbor
        if(N_stack.size()){
            n = N_stack[rand()%N_stack.size()];
            N_stack.clear();
            stackA.push(current);
            make_hall(current,n);
            current = n;
            rooms[current].visited=true;
            visited_rooms++;
        }
        else if (stackA.size()>1){
            current=stackA.top();
            stackA.pop();
        }
    }
    return 0;
}

int block::build(int x,int y,int w,int h){
    neighbor_count=0;
    if (y>0){neighbors[neighbor_count]=((y-1)*w)+x;neighbor_count++;}    //top
    if (x<w-1){neighbors[neighbor_count]=(y*w)+x+1;neighbor_count++;}      //right
    if (y<h-1){neighbors[neighbor_count]=((y+1)*w)+x;neighbor_count++;}    //bottom
    if (x>0){neighbors[neighbor_count]=(y*w)+x-1;neighbor_count++;}      //left
    visited = false;
    init();
    gen_rooms();
    gen_halls(rand()%256);
    return 0;
}

int block::print_block(){
    for(int y=0;y<176;y++){
        for(int x=0;x<176;x++){
            if(tiles[y*176+x]!=1){
                printf("%d",(int)tiles[y*176+x]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
