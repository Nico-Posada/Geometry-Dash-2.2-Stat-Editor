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

***OF THESE STATS, THE FOLLOWING WILL NOT STICK ON RESTART***
 - ORBS
 - DIAMONDS
 - ALL TYPES OF SHARDS
 - BASEMENT KEYS (and chests you open with the fake keys)

# HOW TO USE
- Download and install Visual Studio along with all the necessary C++ packages
- Open the .sln file, set the mode to 'Release' and the platform to 'x86'
- Build project, and enjoy modding your stats

# TODO
- Been working on a way to hard unlock (they stay unlocked on restart) all items in the game. So far, I've been able to unlock all Star challenges and Demon challenges along with a few miscellaneous items, but it's no where near enough, so I'll leave that off to the side until I can figure out a better solution
