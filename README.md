# Gomoku - Unreal Engine 4 example game with C++

Please check out the Release branch

## Project hours
Project started Sep 16, 2019 and finished Sep 26, 2019
Total hours: __~24__

## Goals:
1. Engine version – 4.20 or higher.
2. Field size should be 8x8 or bigger.
3. Game board should be displayed in 3d – nothing fancy needed, just some squares and
tokens, select any 3d models you see fit. Using simple cones or spheres will be
sufficient, but complications are welcome.
4. Human player should be playing against an AI, player always moves first (is the first one
to make a move).
5. There should be an option for human player to undo his/her last move three times (three
‘lives’).
6. Add some sounds (free ones from internet is okay).
7. BP and C++
8. UI

## Achievments
1. Engine version is 4.23.
2. Field size can be configured to be from 8x8 up to 50x50 (arbitrary limit).
3. Game board and tokens were made using in-built BSP shapes exported to 3D static meshes.
4. Human player makes the first move, AI currently only tries to block the player.
5. N/A
6. N/A
7. C++ only
8. Log messages on screen

### Drawbacks
*There is no actual game state - the game can be continued even after win/lose condition is reached and restarted only through the editor.
