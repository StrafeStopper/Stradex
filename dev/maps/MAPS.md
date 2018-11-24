# This is the codex for map level design
## Below are a few tables that explain types and numbers:


Collision Type | Notes
---------------|-------
00             | This tile will not do anything if stepped in
01             | This tile will stop the player if it attempts to walk into it
02             | This tile with allow the player to trigger an event while standing in it
  _            | Objects and triggers will be linked



Tile ID | Tile name  | Collision type
--------|------------|----------------
 00     | TILE_BLACK | 01
 01     | TILE_GREY  | 00
 02     | TILE_BLUE  | 02
 03     | TILE_RED   | 00
 04     | TILE_GREEN | 00


Each number in the map matrix represents a tile type

Ex. 01 to render a grey tile

Tiles with a collision type will behave as described in the above table

The current map size is 67 * 24. Meaning that the first row will have 67 tiles and 24 rows for a complete map. A complete map will have 1608 tiles in total. Even a single missing tile or incorrect tile type will cause an error to occur. Make the calculations properly in order to design a working map. The engine does not need to be compiled after a map edit has been made.

Below is an example of a map that is 5 * 5. 25 tiles in total:

Example map | 5 * 5 | _ | _ | _ |
------------|-------|---|---|---|
00 | 00 | 00 | 00 | 00
00 | 01 | 01 | 01 | 00
00 | 01 | 01 | 01 | 00
00 | 01 | 01 | 01 | 00
00 | 00 | 00 | 00 | 00
