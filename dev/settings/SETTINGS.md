# Settings
## The current max settings size is 100 lines.
## This size will be updated as needed

#### Use this codex to changed settings until the options menu works properly.
#### The number shown is the array index value in the program.
#### Add one to the index value for its line position in the settings file
#### Each settings value gets its own line

00. WINDOW_WIDTH
  * Ex. 1280
  * Keep the aspect ratio to `16:9`

01. WINDOW_HEIGHT
  * Ex. 720
  * Keep the aspect ratio to `16:9`

02. PLAYER_VEL
  * Default for `PERSPECTIVE_STYLE = 0` is `191`
  * Default for `PERSPECTIVE_STYLE = 1` is `4`
  * Multiply by `50` for `PERSPECTIVE_STYLE` of `0`
  * Divide by `50` for `PERSPECTIVE_STYLE` of `1`

03. PERSPECTIVE_STYLE
  * 0 = birds eye (3rd person)
  * 1 = platform
