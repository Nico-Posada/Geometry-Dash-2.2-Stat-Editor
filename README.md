# 2.2 IS OUT!!!!
The method for reading the game's stats hasnt been changed, but a few of the offsets did change, so those have been updated. New stats were added so you can modify those too.

# Geometry Dash Stat Editor
Stat editor for Geometry Dash. Game blew up in popularity for some reason, and I figured it would be a fun game to try to mod.
There are many different public mods out there that do many different things, but one thing I noticed is that most of them involve byte patching functions, so I decided to avoid that route and take a more sophisticated approach to things.

# What You Can edit
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
 - ACH1 (not sure what these are exactly but they're there)
 - ACH2
 - ACH3
 - ACH4
 - ACH5
 - ACH6
 - ACH7
 - ACH8
 - ACH9
 - ACH10
 - COMPLETED GAUNTLETS
 - COLLECTED LIST REWARDS

***OF THESE STATS, THE FOLLOWING WILL NOT STICK ON RESTART***
 - ORBS
 - DIAMONDS
 - ALL TYPES OF SHARDS
 - BASEMENT KEYS (and chests you open with the fake keys)

# HOW TO USE
- Download and install Visual Studio along with all the necessary C++ packages
- Open the .sln file, set the mode to 'Release' and the platform to 'x86'
- Build project, and enjoy modding your stats
- Executable file will be located in the `build` directory
