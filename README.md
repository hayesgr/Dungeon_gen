# Dungeon_gen
Creating a dungeon is fairly strait forward.<br />
Dungeon dung;<br />
Map_Width = 64;<br />
Map_Height = 64;<br />
dung.init(Map_Width,Map_Height);<br />
dung.gen_blocks();<br />
dung.gen_halls(0); //The 0 can be replaced with a random number from 0 to 255 it selects which room to start the depeth first search<br />
<br />
A 64x64 Dungeon produces a dungeon with 1024 x 1024 rooms.<br />
The dungeon it can produce can look like this. <br />
![alt text](https://github.com/hayesgr/Dungeon_gen/blob/main/DungeonExtreme01.png?raw=true)
