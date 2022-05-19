S.W.I.N.E. HD Remaster HDBEEFUP
fork of https://github.com/hdbeefup/SWINECLASSIC (Classic HD Remaster)
hdbeefup.github.io

This project consists of:
1. Basic know-how to patch game yourself (get cheat console, camera tweak)
2. Injection / Wrapping based Game and Editor tweaks (cheat console input, camera tweak, unlimiter, WASD, etc)

# FIRST RUN:
Start the game by using swinechdb.exe. 

To use MODS, create copy of base folder, or just drag and drop mod into gamedata folder.
Edit swinehdbconfig.ini to activate some other mod.
You can also use hex editor, to edit copy of swinechdb.exe, create copy of swinehdbconfig.ini and overwrite anything until .ini,
for example swinehdbconfGG.ini is acceptable, however something that goes over the character limit will be problematic (swinehdbconfig-somemodiuseoften.ini)

# Troubleshooting:
1. Use OBS with Display (whole screen-monitor) capture, Or XBOX Game bar (Windows 10 WIN+G).
* If Software recorders fail to catch it (e.g. Dual graphics card, or can't record desktop), pickup a cheap HDMI Capture card (~10$).
* Upload video online & contact me / create github issue. In some cases you might need to mention hardware you have.

# BUGS:
1. With cheat patch applied, chat in multiplayer will be disabled (this is because it's a simple reverse logic patch)
2. Too high, instane values in for Camera zoom will be problematic in some "cutscenes" and start of missions.

# Features:
* CREATE YOUR OWN TANK LIST + UNIT UNLIMITER. Yes, you now can have more tanks, so if you mod something in, you can keep it for whole campaing, plus you can easily pick out any tank make it purchasable, 
show before mission corresponding to the list you made
* EASY TO HAVE MULTIPLE MODS, WITH NO COLLISION TO EATCH OTHER, NO UNINSTALLING OR REINSTALLING NEEDED. Have fun your own way, all the way with ease ;)
!! WASD
!! DISABLE MAP ROTATION

# Known issues:

------------------------------------------------------------------------------------------------------------
# How To Compile:

You can compile this with these steps:

1) Firstly run premake5.bat
2) Open `build\SWINEClassicHD.sln` with Microsoft Visual Studio 2015 or 2019 [Any Edition, can be Community or Enterprise]
(If you want to use it with an older version, just change the platform toolset setting.)
3) Right click on Solution 'SWINEClassicHD' > Build or just CTRL+SHIFT+B. (Or, you can open its contents by clicking the triangle at left. dllmain.cpp is the main code. Make the edits you want, you're free!)
!Make sure you're building with Release and Win32 option. See the upper toolbar for them.
4) Look for the "Output" panel. If it says "Build: 1 succeeded, 0 failed," and stuff, your .asi file has been successfully built. (It will be built into `(Project folder)\Release` folder.)
5) Now, copy it to your `*GAME LOCATION*\scripts` folder. (Use Ctrl+C, Ctrl+V / Cmd+C, Cmd+V / Strg+C, Strg+V; Right-Click > Copy; via xcopy command on CMD; or how do you like it.)
6) Copy the swinehdbconfig.ini from main folder into `*GAME LOCATION*\scripts` folder, too.
7) Run Game and see what happens. :)
If not get this https://github.com/ThirteenAG/Ultimate-ASI-Loader/ and put into "GAME LOCATION" folder (main one near game launcher / exectutable) rename dll file to d3d8 And try again.
