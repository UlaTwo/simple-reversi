# simple-reversi
This is simple implementation of the game "Reversi".
Using language: C.
Data of creating: 7.12.17

## Compiling the code

gcc -std=c11 -pedantic -Wall -Wextra -Werror reversi.c -o reversi

## Running the game

### Playing from the terminal
./reversi

### Playing from the file
< file-name.in ./reversi
example:
< test1.in ./reversi

## Game description
Reversi is a strategy board game for two players, played on an 8×8 uncheckered board. 
Players take turns placing disks on the board (with black or white color).
During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed
and another disk of the current player's color are turned over to the current player's color. 
more: [Wikipedia page](https://en.wikipedia.org/wiki/Reversi)

## Program description
The game is played by human and computer. 
In every turn human can write:
place on the board where he want to put his disk (example: "a1")
"=" if he want to give up his turn

As the result program writes in the same line:
the place on the board which computer chose in this turn and the number of points 
(number of dark disks subtract number of white disks)
(example: a1 c3 -3)
If the move that player chose is not permitted, computer write: "?"

## Computer algorithm
Computer is choosing this move, which gives him more dark disks on the board after this turn. 
If there is more than one possibility, he choose first one (in left upper corner )


