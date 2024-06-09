# Geometry Dash Stats Editor
Stats editor for Geometry Dash. The game blew up in popularity for some reason, and I figured it would be a fun game to try to mod.
There are many different public mods out there that do many different things, but one thing I noticed is that most of them involve byte patching functions, so I decided to avoid that route and take a more sophisticated approach to things.

# Updates
## 2.206
Game updated to 64-bit architecture. Offsets changed a bit and the method to retreive stats was slightly changed but nothing too major. Tool is up to date again!

## 2.203
RopTop revamped how stats are stored, but the tool has been updated to support that and now works as intended again!

# What you can edit
The following stats can be modified:
 - TOTAL JUMPS
 - TOTAL ATTEMPTS
 - COMPLETED LEVELS
 - COMPLETED ONLINE LEVELS
 - DEMONS
 - STARS
 - MAP PACKS COMPLETED
 - COINS
 - PLAYERS DESTROYED
 - LIKED/DISLIKED LEVELS
 - RATED LEVELS
 - USER COINS
 - DIAMONDS
 - ORBS
 - COMPLETED DAILY LEVELS
 - SHADOW SHARDS
 - POISON SHARDS
 - FIRE SHARDS
 - ICE SHARDS
 - LAVA SHARDS
 - BASEMENT KEYS
 - TOTAL ORBS COLLECTED
 - EARTH SHARDS
 - BLOOD SHARDS
 - METAL SHARDS
 - LIGHT SHARDS
 - SOUL SHARDS
 - MOONS
 - DOUBLE DIAMONDS
 - COMPLETED GAUNTLETS
 - COLLECTED LIST REWARDS

***THESE STATS WON'T SAVE WHEN YOU RESTART THE GAME***
 - ORBS
 - DIAMONDS
 - ALL TYPES OF SHARDS
 - BASEMENT KEYS (AND CHESTS YOU OPEN WITH THESE)

# How to build (check releases if you don't want to build)
- Download and install Visual Studio 2022 along with all the necessary C++ packages
- Run BUILD.bat (edit if needed), and enjoy editing your stats
- Executable file will be located in the `build` directory
