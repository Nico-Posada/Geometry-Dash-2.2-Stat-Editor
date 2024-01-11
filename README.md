# Update 2.203
RopTop revamped how stats are stored, so going to have to rereverse that, will remove this once I get it updated again.

# 2.2 IS OUT!!!!
The method for reading the game's stats hasnt been changed, but a few of the offsets did change, so those have been updated.  
The new stats were added so you can modify those too.

# Geometry Dash Stats Editor
Stats editor for Geometry Dash. The game blew up in popularity for some reason, and I figured it would be a fun game to try to mod.
There are many different public mods out there that do many different things, but one thing I noticed is that most of them involve byte patching functions, so I decided to avoid that route and take a more sophisticated approach to things.

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

# HOW TO BUILD (Check releases if you don't want to build)
- Download and install Visual Studio 2022 along with all the necessary C++ packages
- Run BUILD.bat (edit if needed), and enjoy editing your stats
- Executable file will be located in the `build` directory
