# Dungeon_gen
Creating a dungeon is fairly strait forward.
Dungeon dung;
Map_Width = 64;
Map_Height = 64;
dung.init(Map_Width,Map_Height);
dung.gen_blocks();
dung.gen_halls(0); //The 0 can be replaced with a random number from 0 to 255 it selects which room to start the depeth first search

A 64x64 Dungeon produces a dungeon with 1024 x 1024 rooms.
 
