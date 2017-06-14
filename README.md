# lemin

## Objectif ##

Send the mithy ants from the start to end!

`make`

`./lem-in [-v]`

or

`./lem-in [-v] < example/files`

with option -v it will give you more information about what really is happening inside my code.

1st step:
declare number of ants

2nd step:
define rooms with coordinates.

example:

> room1 0 0

define the starting room by adding `##start` before the declaration of your starting room.
Same for the ending room with the commant `##end`

3rd step:
link some room.

example:

> room1-room2

4th step:
just send a empty line

5th step:

You will see what those mighty ants did.

example:

> L1-room1

the first ants is in room1
