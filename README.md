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

## How it works
I will start with the basics.
If you try to take a million rooms and randomly drop them in a map the size of this you will get collisions. You will have two choices. To either move them or try again.
The more rooms you have in the map the more checks you need to do for collisions. You could divide the space up into a grid and then only check the rooms in that area.
That is still slow.

A faster method will be to generate a random room set it down in the Top Left corner with an offset and then the next room slightly off set from it and repeat filling in the area you want when you get to the side drop down below the rooms above them.
You have two choice either create an offset based on room above them or just leave them in a row above all the prior rooms. Either way this is going to have issues in future steps when trying to connect paths to each room. You can have two many rooms beside each other along with rooms that don't aline easily to connect to one another.

A better method is two set the rooms in a grid and use a random offset in the space assigned for each room. Lets say this space for a room is 11x11 and rooms sizes can range from 3x3 to 11x11 they don't have to be the same width and height.
![alt text](https://github.com/hayesgr/Dungeon_gen/blob/main/RoomBlocks.png?raw=true)
You still have some issues. If 2 rooms 3x3 were placed next to one another one at the top and one at the bottom you couldn't connect them simply with a strait path. You would need a corner. That would mean you need a far more complex path generator. That will consume a lot of time. The solution to this is a guaranteed connection point or at least one for starting at. We make tile 5,5 in side each room area guaranteed to be a floor tile. This means every room in a row will share one tile that is on the same Y axis and every room in a column will have at least one tile in the same X axis. This is the method used here. You are probably thinking weight a moment if that is the case all the paths connecting rooms would line up. As I said it is a start point I offset the halls connecting the rooms. For vertical floors I move the left of right and horizontal halls I move them up or down.<br />
![alt text](https://github.com/hayesgr/Dungeon_gen/blob/main/RoomOffset.png?raw=true)

In connecting the rooms in the grid I use a depth first search method. You can't use it to connect all 1 million rooms it woul take a lot longer than I am currently doing it in. So we use a divide and conguer method.
The program generates blocks each block has 256 rooms. It connects all those together. Then we make multiple of the blocks as you see above 64x64. We then connect the blocks together using depth first search also.
To keep the randome appearance up we select between the various rooms on that side and use the guaranteed connection position.

The dungeon generator has a bit more functionality and uses. First you can generate much larger maps. 256x256 blocks will net you a dungeon with 16.7+ million rooms. You can also create dungeons as small as 1x1 that will have 256 rooms.
Those connection points use to connect rooms can also be used as vertical connections. That means you can use it to create vertical dungeons as well.
Because of the block being used you can also make modifications to it allowing you to drop in premade areas.
You could even have outdoor types if you turned off the path generation for that level.
One could also modify the system to instead of generating the rooms to select prefabricated rooms and place them in.

The performance of it allows means the player won't be waiting forever for you to generate stuff.

If you use the same seed in srand you will get the same dungeon. If you use time(NULL) in srand it will be randomized.
You can use that fact for generating the levels you can travel back and forth from.
