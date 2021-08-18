S.W.I.N.E. Classic Remaster Beta 1 - Stockholm chain
Based on 2001-1.9 (Free christmas giveaway) version
hdbeefup.github.io

# S.W.I.N.E. Classic Remaster
STOCKHOLM Chain (compatibility through hungarian gibberish)
developed by
Darius Bads (bads.tm, dw5)

special thanks to:
Balazs Benics (steakhal)
Anıl Gezergen (nlgzrgn)
Malwin Hamm (Hans Rudel)

# FIRST RUN:
Start the game by using releasepigz.exe. 

To use MODS, create copy of base folder, or just drag and drop mod into gamedata folder.
Edit swinechd.ini to activate some other mod.
You can also use hex editor, to edit releasepigz.exe, create copy of swinechd.ini and overwrite anything until .ini,
for example swin2chd.ini is acceptable, however something that goes over the character limit will be problematic (swinechd-somemodiuseoften.ini)

# Troubleshooting:
1. Use OBS with Display (whole screen-monitor) capture, Or XBOX Game bar (Windows 10).
* If Software recorders fail to catch it (e.g. Dual graphics card, or can't record desktop), pickup a cheap HDMI Capture card (~10$).
* Upload video online & contact me. In some cases you might need to mention hardware you have.
2. 1920x1080 is the source for images, 800x600 is kept for clarity/sharpness if someone were to use it in such "old-school" screen. Don't delete these folders, especially 1920x1080.
3. Can't run on Windows XP/Vista - Due to some newer C++ and Microsoftisms, at the moment builds are targeting Windows 7. 
Porting project to other compilers or older Visual Studio might help. (Yes, there will be WinXP and older if possible support)

# Features:
* BETTER FOLDER STRUCTURE
* MODDING DETECTION-REJECTION REMOVAL
* INI SWAPLESS MODDABILITY (so next gen, insta-kills SWITCH, TUSTK, etc)
* IMAGES NOT ENDING WITH _HQ.TGA STILL CAN HAVE TRANSPERANCY AND STUFF
* AUTO SCREEN RESOLIUTION - Game automatically starts according to your screen resoliution, however not all things scale nicely (cough cough Headquarters, Briefing)
* EASILY WRITE IN GAMESPY COMPATIBLE MULTIPLAYER - By default QTRACKER is provided, but you can easily change it to your needs ;)
* CREATE YOUR OWN TANK LIST + UNIT UNLIMITER. Yes, you now can have more tanks, so if you mod something in, you can keep it for whole campaing, plus you can easily pick out any tank make it purchasable, 
show before mission corresponding to the list you made
* EASY TO HAVE MULTIPLE MODS, WITH NO COLLISION TO EATCH OTHER, NO UNINSTALLING OR REINSTALLING NEEDED. Have fun your own way, all the way with ease ;)
* Enjoy Max screen real estate without "in your face" GUI.

# Features not implemented:
* Complete translation, no hungarian leftovers. Use Rabbit Jeep, instead of Nyul Dzsip. Complete change of file structure, and mission map file fixes (MODERNA Chain)
  + Translation engine (change UI language to what is defined in messages.ini) for STOCKHOLM Chain
* Multiplayer UI Scaling

# Known issues:
1. Being in fullscreen (not windowed fullscreen), there is an mouse and right click (e.g. where unit should go indicator) inaccuracy, mouse might not work.
In that case you might want to change to some other resoliution, then change back.

and yes, windowed fullscreen is the one which works best, but doesn't scroll camera if your mouse is on the corner/edges

2. Initial main menu has a centered 800x600 mouse cursor render area. Click on anything (settings, credits) and you'll see cursor outside it.

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
6) Copy the SWINEExtraOptionsSettings.ini from main folder into `*GAME LOCATION*\scripts` folder, too.
7) Run Game and see what happens. :)
If not get this https://github.com/ThirteenAG/Ultimate-ASI-Loader/ and put into "GAME LOCATION" folder (main one near game launcher / exectutable) rename dll file to d3d8 And try again.


# Dev history
```Development was made using free time. Thus it was super slow. 
Experimentation and tinkering attempts were made ~2017-2018 through less direct ventures. 
This beefup can be finished under a month, rather than over a year.
Hardest and most frustrating part, is guessing which address is for what. 
It's like being blind and trying your best. Plus for no apperant reason, game glitches out 
(similar to how if you can crash by quickly going to third row on headquarters, or turn SP into 13 for no reason when using unlimiter)

First commit related to S.W.I.N.E. HDBEEFUP was made on Apr 11, 2020
Apr 12 was mostly to index every address related to screen resolution 800x600

May 12, 2020 Implemented Splash and Backdrop files (hardcoded to base for now). Made Character faces appear at bottom corner

Jun 20, 2020 Compilation time was implemented to Title screen game name. Other background images like briefing, headquarters was implemented. Including hard coded scaling guessing.

Oct 27, 2020 Fix mouse rotation spin bug. SWINE Edition byte, after mission end, game doesn't go 800x600, disabling tamper (modding) check

Dec 5, Dec 7, 2020 Cleanup, ingame menu, folders, button coordinates

Dec 18, 2020 Close enough to being ready. Reads swinechd.ini for basepath, and is used for mods.

Fed 10, 2021 Fixed slashes, Better scaling experiments

Feb 16, 2021 Partially proper scaling for UI Elements (text buttons). Anif (tank spin in headquarters) coordination.

Feb 17, 2021 Briefing and market scaling, perfecting using math for 800x600 and other resolutions (would be better if background texture wasn't baked in with overlay transparencies). Unlimiter experiment

Apr 11, 2021 Close to POC version. Nice videos folder

May 22, 2021 RTMPigs used as background upscale, fix BUY/SELL button on lower screen resolutions. POC is released.

Jul 13, 2021 Code cleanup and planning.

August 4, 2021 Tanks.txt reader and chunked output implemented, But for integration with game it needs more improvements. Eventually solution was found and game works without problems.

August 7, 2021 Attempts with localization, but technical hassle again, thus idea was scrapped.
Project is finished.```


![](https://img.itch.zone/aW1nLzY2OTM2OTYucG5n/original/G0KgeD.png)
![](https://img.itch.zone/aW1nLzY2OTM2OTUucG5n/original/8JIEq8.png)
![](https://img.itch.zone/aW1nLzY2OTM2OTMuanBn/original/O3cx9s.jpg)
![](https://img.itch.zone/aW1nLzY2OTM2ODYucG5n/original/3hiF6l.png)
![](https://img.itch.zone/aW1nLzY2OTM2ODUucG5n/original/oCM2og.png)