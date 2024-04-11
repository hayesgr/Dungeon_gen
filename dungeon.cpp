#include"dungeon.h"

int dungeon::init(int w,int h){
    width=w;height=h;
    blocks = (Block*)malloc(sizeof(Block)*w*h);
    if(!blocks){return -1;}
    tiles = (uint8_t*)malloc(sizeof(uint8_t)*(w*176)*(h*176));
    if(!tiles){return -2;}
    return 0;
}

int dungeon::gen_blocks(){
    //printf("genblocks\n");
    int tw=width*176;   //tile width
    //int th=height*176;  //tile height
    int bid=0;          //Block id
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            bid = y*width+x;
            blocks[bid].build(x,y,width,height);
            for(int j=0;j<176;j++){
                for(int i=0;i<176;i++){
                    tiles[(y*tw*176)+(x*176)+(j*tw)+i]=blocks[bid].tiles[j*176+i];
                }
            }
        }
    }
    //printf("fin genblocks\n");
    return 0;
}

int dungeon::make_hall(int current,int next){
    //printf("make_hall\n");
    int arr[16]={5,16,27,38,49,60,71,82,93,104,115,126,137,148,159,170};
    int Ax=0,Ay=0,dir=0;
    int cx = current%width;
    int cy = current/width;
    int nx = next%width;
    int ny = next/width;
    int tw = width*176;
    int flr=0,st=0,ed=11;          //floor,start,stop
    int k=0,p=0;
    if(cx<nx){Ax=cx;Ay=cy;dir=0;}
    if(cx>nx){Ax=nx;Ay=ny;dir=0;}
    if(cy<ny){Ax=cx;Ay=cy;dir=1;}
    if(cy>ny){Ax=nx;Ay=ny;dir=1;}
    if(dir==0){ //Horizontal
        //printf("Horizontal\n");
        int ry = arr[rand()%16];
        p=(Ay*tw*176)+(Ax*176);
        k=p+(ry*tw)+171;
        for(int ii=0;ii<11;ii++){
            if(flr==0 && tiles[k+ii]<5){st=ii;flr=1;}
            if(flr==1 && tiles[k+ii]>31){ed=ii;break;}
        }
        for(int i=st;i<ed;i++){
            if (tiles[p+((ry-1)*tw)+171+i]==0){tiles[p+((ry-1)*tw)+171+i]=1;}
            tiles[p+(ry*tw)+171+i]=35;
            if(tiles[p+((ry+1)*tw)+171+i]==0){tiles[p+((ry+1)*tw)+171+i]=1;}
        }
    }
    else {      //vertical
        //printf("Vertical\n");
        int rx = arr[rand()%16];
        p=(Ay*tw*176)+(Ax*176);
        k=p+rx;
        for(int i=0;i<11;i++){
            if(flr==0 &&tiles[k+((171+i)*tw)]<5){st=i;flr=1;}
            if(flr==1 && tiles[k+((171+i)*tw)]>31){ed=i;break;}
        } 
        for(int i=st;i<ed;i++){
            if (tiles[p+((171+i)*tw)+rx-1]==0){tiles[p+((171+i)*tw)+rx-1]=1;}
            tiles[p+((171+i)*tw)+rx]=35;
            if (tiles[p+((171+i)*tw)+rx+1]==0){tiles[p+((171+i)*tw)+rx+1]=1;}
        }
    }
    return 0;
}
int dungeon::check_neighbors(std::vector<int> &N_stack, int current){
    for(int i=0;i<blocks[current].neighbor_count;i++){
        if(!blocks[blocks[current].neighbors[i]].visited){N_stack.emplace_back(blocks[current].neighbors[i]);}
    }
    return N_stack.size();
}


int dungeon::gen_halls(int n=0){
    //printf("gen_halls\n");
    std::stack<int> stackA;
    int current = n;
    blocks[current].visited=true;
    int visited_blocks=1;
    std::vector<int> N_stack;
    while(visited_blocks<width*height){
        //check neighbors
        check_neighbors(N_stack,current);
        //select unvisited neighbor
        if(N_stack.size()){
            n = N_stack[rand()%N_stack.size()];
            N_stack.clear();
            stackA.push(current);
            make_hall(current,n);
            current = n;
            blocks[current].visited=true;
            visited_blocks++;
        }
        else if (stackA.size()>1){
            current=stackA.top();
            stackA.pop();
        }
    }
    //printf("fin gen_halls\n");
    return 0;
}

int dungeon::print(){
    for(int y=0;y<height*176;y++){
        for(int x=0;x<width*176;x++){
            if(tiles[y*(176*width)+x]!=1){
                printf("%d",(int)tiles[y*(176*width)+x]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
