# This is the codex for map level design

Collision types:

  0. No collision
      * This tile will not do anything if stepped in

  1. Physical clip collision
      * This tile will stop the player if it attempts to walk into it

  2. Activation trigger collision
      * This tile with allow the player to trigger an event while standing in it
      * Objects and triggers will be linked

Tile ID | Tile name  | Collision type
--------|------------|----------------
 00     | TILE_BLACK | 1
 01     | TILE_GREY  | 0
 02     | TILE_BLUE  | 2
 03     | TILE_RED   | 0
 04     | TILE_GREEN | 0
