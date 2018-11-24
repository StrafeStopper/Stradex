# This is the codex for map level design

Collision Type | Notes
---------------|-------
00             | This tile will not do anything if stepped in
01             | This tile will stop the player if it attempts to walk into it
02             | This tile with allow the player to trigger an event while standing in it.
 _             | Objects and triggers will be linked



Tile ID | Tile name  | Collision type
--------|------------|----------------
 00     | TILE_BLACK | 01
 01     | TILE_GREY  | 00
 02     | TILE_BLUE  | 02
 03     | TILE_RED   | 00
 04     | TILE_GREEN | 00
