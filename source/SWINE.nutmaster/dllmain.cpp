#include "stdafx.h"
#include <time.h> // for random easter egg secret logo.avi

//char* Takeover = "S.W.I.N.E. Classic HD Remaster %s v%d.%d.%d © 2020 dariusworks";
//char* Takeover = "%s S.W.I.N.E. v%d.%d Classic Remaster POC PREVIEW | bads.team/swinechd | Compiled at " __DATE__ ", " __TIME__ " |";
//char* Splashfile = "gamedata/base/interface/bg/default/splash.tga";
//char* Backdropfile = "gamedata/base/interface/bg/default/backdrop.tga";
char* relEdition = {"~~~### S.W.I.N.E. Classic HD Remaster. Darius (DW5) ### bads.tm ### github.com/hdbeefup ### (C) 2016-2021 ~~~ Source code available under GPL3 License (ᵔ◡ᵔ)"};
char* TheOtherSide = { "Greetings from the other side! Nice to see you poking around ^_^ | I guess it's not obselete after all, and While yes things were happening slow, but i've been tinkering a long while with swine, years before Kite games made their debut. Never got a chance, or spare time to focus on this lil project, It technically shouldn't take longer than a week. In any case here's a lesson you shouldn't forget, work on things now, do things you enjoy, see where you fit the best, and screw every other thing keeping you busy, and doesn't even profit you in any meaningful way. Oh and don't waste time, watch stuff at 1.5x video speed or whatever you find suitable, it saves time and its like free real estate (doesn't impact in any way..) And with this being done, with no Kite Kindness in sight, This is my goodbye to S.W.I.N.E. community :c" };

/*
S.W.I.N.E. Classic Remaster
STOCKHOLM Chain (compatibility through hungarian gibberish)
developed by
Darius Bads (bads.tm, dw5, hdbeefup)

special thanks to:
Balazs Benics (steakhal)
Anıl Gezergen (nlgzrgn)
Malwin Hamm (Hans Rudel)

Compile:
For dev, feel free to use scripts folder, 
make sure to edit <~!DEVS!~> spots and swap commented swap out RTM lines
This also means swinechd and other goodies will be in scripts folder too.
It also should be as easy as opening it up in Visual Studio.

STOCKHOLM Chain is made to be compatible as possible, while MODERNA Is fully English-fied
Working on MODERNA requires some additional work (e.g. ports) in order to have no game crashes (e.g. Nyul Dzsip doesn't exist in Moderna, you need to use Rabbit Jeep)
However on MODERNA you could find lot more mods. Plus more Quality of Life improvements, even than HD Remaster. It also provides easier file structure to work with.
Assuming kite games would finally make S.W.I.N.E. Open source some day, or atleast release 2001 compatible map editor
you could create your own maps, more impressive (and pushing game engine to its limits) campaigns, create new assets, tanks, 3d models.
For example, wouldn't it be cool to have Race swap mod? Basically You can play Rabbit campaign and missions as Pigs. It's more extra fun to be had.
If it was possible MODERNA would also try to improve few maps, where mistakes were made by original game developers.
Plus extracted game data requires some fixes due to glitched filename output.
*/

char hdLang, basepath, multiplayerIP;
float CamMaxZoomIn, CamMaxZoomOut, CamMaxAngleUp, CamMaxAngleDown, CamMapLimit;
int SWINEEdi;
bool bEnableExperimentResPW, bModdedTanklist, bCustomLang;

void Init()
{
	CIniReader iniReader("swinechd.ini"); /// CHD Settings
	std::string basepath = iniReader.ReadString("Mods", "Basepath", "base"); // E.g. "base" for original, or "basemods"

	bModdedTanklist = iniReader.ReadInteger("Mods", "TanklistMod", 0);
	bEnableExperimentResPW = iniReader.ReadInteger("Patchworks", "EnableExperimentResPW", 1);
	bCustomLang = iniReader.ReadInteger("Patchworks", "ExternalLanguageAssets", 0);
	int ResX = iniReader.ReadInteger("Patchworks", "FResX", 0);
	int ResY = iniReader.ReadInteger("Patchworks", "FResY", 0);

	// Mods
	std::string MPPeercht = iniReader.ReadString("Mods", "MultiplayerPeerchat", "65.112.87.187"); // Peerchat
	std::string MPMasterlist = iniReader.ReadString("Mods", "MultiplayerMaster", "65.112.87.186"); // Peerchat
	int ColorMM = iniReader.ReadInteger("Mods", "ColorMainMenu", 0xF0F0F0); // COLOR
	int ColorHOV = iniReader.ReadInteger("Mods", "ColorMainMenuHOV", 0xFFFFFF); // COLOR HOVER
	injector::WriteMemory<int>(0x41809D, ColorMM, true); // COLOR
	injector::WriteMemory<int>(0x418098, ColorHOV, true); // COLOR HOVER


	// Camera 
	CamMaxZoomIn = iniReader.ReadFloat("Camera", "MaxZoomIn", 10.0f);
	CamMaxZoomOut = iniReader.ReadFloat("Camera", "MaxZoomOut", 20.0f);
	CamMaxAngleUp = iniReader.ReadFloat("Camera", "MaxAngleUp", -1.13f);
	CamMaxAngleDown = iniReader.ReadFloat("Camera", "MaxAngleDown", -0.7f);
	CamMapLimit = iniReader.ReadFloat("Camera", "MapCameraLimit", 48.0f);

	if (!ResX || !ResY)
		std::tie(ResX, ResY) = GetDesktopRes();

	//injector::WriteMemory<DWORD>(0x43A85E, (DWORD)Takeover, true);
	std::string TakeoverMD = "%s S.W.I.N.E. v%d.%d Classic Remaster SHv2 | dw5 | Running: " + basepath + " @" + std::to_string(ResX) + "x" + std::to_string(ResY) + " | Compiled at " __DATE__ ", " __TIME__ " |";
	injector::WriteMemory<DWORD>(0x43A85E, (DWORD)((char*)strdup(TakeoverMD.c_str())), true);
	injector::WriteMemory<unsigned char>(0x43a82d, 11, true); // SWINE Edition (byte)
	injector::WriteMemory<DWORD>(0x416921, (DWORD)((char*)"Auto"), true); // options to show screen res text

/* == Process background textures because SR Juniors */
	// preferably read swine logs, and identify that way rather than if 1 doesn't exist, redo all
	//priority:
	//splash
	//backdrop
	//rab briefing, pig briefing
	//market, mp titleroom
	//other multiplay

	/* if scripts folder (Dev) */

	std::string bgimages[14] = {
	"splash.tga",
	"backdrop.tga",
	"rabbit_briefing.tga",
	"pig_briefing.tga",
	"rabbit_market.tga",
	"pig_market.tga",

	"rabbit_titleroom.tga",
	"pig_titleroom.tga",
	"rabbit_chatroom.tga",
	"pig_chatroom.tga",
	"pig_chatroom_nohost.tga",
	"rabbit_chatroom_nohost.tga",
	"pig_stagingroom.tga",
	"rabbit_stagingroom.tga"
	};

	/*			 <~!DEVS!~>				 */

	/*RTM */ if (!std::filesystem::exists("gamedata/" + basepath + "/interface/bg/" + std::to_string(ResX) + "x" + std::to_string(ResY) + "/splash.tga")) {
	/*DEV */ //if (!std::filesystem::exists("../gamedata/" + basepath + "/interface/bg/" + std::to_string(ResX) + "x" + std::to_string(ResY) + "/splash.tga")) {

		int msgboxID = MessageBox(
			NULL,
			(LPCWSTR)L"We need to process few images for your screen resolution.\n [Cancel] exits game, [Try again] IGNORES, [Continue] fixes issue",
			(LPCWSTR)L"S.W.I.N.E. Classic Remaster",
			MB_ICONERROR | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

		switch (msgboxID)
		{
		case IDCANCEL:
			exit(3);
			break;
		case IDTRYAGAIN:

			break;
		case IDCONTINUE:
			for (int i = 0; i < 14; i++) {
				/*			 <~!DEVS!~>				 */
				//DEVTEST: std::string commandexstr = "pause && echo convert ../gamedata/" + basepath + "/interface/bg/1920x1080/" + bgimages[i].c_str() + " -resize " + std::to_string(ResX) + "x" + std::to_string(ResY) + "! ../gamedata/" + basepath + "/interface/bg/" + std::to_string(ResX) + "x" + std::to_string(ResY) + "/" + bgimages[i].c_str() + ">>conout.log";
				/*DEV*/ //std::string commandexstr = "../tools/convert ../gamedata/" + basepath + "/interface/bg/1920x1080/" + bgimages[i].c_str() + " -resize " + std::to_string(ResX) + "x" + std::to_string(ResY) + "! ../gamedata/" + basepath + "/interface/bg/" + std::to_string(ResX) + "x" + std::to_string(ResY) + "/" + bgimages[i].c_str();
				/*RTM*/ std::string commandexstr = "title " + std::to_string(i) + "/14& tools\\convert gamedata\\" + basepath + "\\interface\\bg\\1920x1080\\" + bgimages[i].c_str() + " -resize " + std::to_string(ResX) + "x" + std::to_string(ResY) + "! gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\" + bgimages[i].c_str();
				const char* commandex = commandexstr.c_str();

				std::string resfoldstr = "mkdir gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\";
				const char* resfold = resfoldstr.c_str();
				system(resfold);
				system(commandex);
			}

			break;
		};
	}





	/* ====== GAME BASICS/CORE ====== */
	// makes sure game isn't in 800x600 in main menu and other screens (videos still would be in custom res, this makes menu screens too)
		//MUST HAVE, high power (centers screen menu UI to center, game in fullscreen)
	injector::WriteMemory(0x42cd94, ResX, true); // 800
	injector::WriteMemory(0x42cd8f, ResY, true); // 600

// game renderer window whatever native (not whatever push 0x, binary thx to gist by kris7t, keeps same res even if entering options)
// MUST HAVE, high power (opening game settings, graphics, it will force windowed into that resoliution)
	injector::WriteMemory(0x5580a0, ResY, true); // 600 0x258 5802
	injector::WriteMemory(0x55809c, ResX, true); // 800 0x320 2003

  // After ending mission, doesn't go to 800x600 (e.g. tutorial and the rest) MUST HAVE
	injector::WriteMemory(0x4330f6, ResX, true); // 800
	injector::WriteMemory(0x4330f1, ResY, true); // 600

// game window (and likely video too). Seems to unrestrict mouse cursor rendering boundries after first click
	injector::WriteMemory(0x42cd73, ResX, true); // 800
	injector::WriteMemory(0x42cd6e, ResY, true); // 600

  // [REM] in game 3d renderer screen res (weird numbers) OR NOTHING
	injector::WriteMemory(0x43adef, ResX, true); // 800 0x320 2003
	injector::WriteMemory(0x43ae03, ResY, true); // 600 0x258 5802

// [REM] After exiting mission, keeps fullscreen. NOPE. not that.
	injector::WriteMemory(0x433125, ResX, true); // 800
	injector::WriteMemory(0x433120, ResY, true); // 600

// Ignore other resoliutions (jne to jmp 75->EB) - LEGACY
	//injector::WriteMemory(0x430B34, 0xEB, true);

// [REM] no idea, nothing, or lets window mode keep res?
	injector::WriteMemory(0x4308ed, ResX, true); // 800
	injector::WriteMemory(0x4308e8, ResY, true); // 600

 // [REM] mouse? -- no idea actually (negative, doesnt let keep same res in windowed?)
	injector::WriteMemory(0x42e922, ResX, true); // 800
	injector::WriteMemory(0x42e91d, ResY, true); // 600

	// [REM] unknown needs tests
	injector::WriteMemory(0x42cd6e, ResY, true); // 600 0x258 5802
	injector::WriteMemory(0x42cd73, ResX, true); // 800 0x320 2003

	//injector::WriteMemory<int>(0x, 5, true);

   // UI Placement de-centerizator MUST HAVE
	injector::WriteMemory(0x42e93e, ResX, true); // 800
	injector::WriteMemory(0x42e92d, ResY, true); // 600

  // Rab/Pig head faces on corner
	injector::WriteMemory(0x42ac56, ResX / 2 + 150, true); // 544 (220hex) | 990
	injector::WriteMemory(0x42ac51, ResY / 2 + 50, true); // 344 (158hex)  | 575

	/* ====== GAME USER INTERFACE ====== */

	/* Title screen */
  // everything looks good, worth it. swine background and menu ui is proper. character not in corner tho. 

	std::string splashstr = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\splash.tga";  injector::WriteMemory<DWORD>(0x42d0c2, (DWORD)((char*)strdup(splashstr.c_str())), true);
	std::string backdropstr = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\backdrop.tga";  injector::WriteMemory<DWORD>(0x42e89f, (DWORD)((char*)strdup(backdropstr.c_str())), true);

	/* ====== Quality of life ====== */
	injector::WriteMemory<DWORD>(0x4fcb16, (DWORD)((char*)strdup(MPPeercht.c_str())), true); // peerchat.gamespy.com
	injector::WriteMemory<DWORD>(0x5016BE, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
	injector::WriteMemory<DWORD>(0x50183f, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
	injector::WriteMemory<DWORD>(0x50f01b, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
	injector::WriteMemory<DWORD>(0x50f02e, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
	injector::WriteMemory<DWORD>(0x41B640, (DWORD)((char*)"Internet game - GameSpy Emu"), true);

	std::string fdb_videofldr = "gamedata\\video";
	injector::WriteMemory<DWORD>(0x42eed7, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);
	injector::WriteMemory<DWORD>(0x497408, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);
	injector::WriteMemory<DWORD>(0x42e57a, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);
	injector::WriteMemory<DWORD>(0x42e2db, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);
	injector::WriteMemory<DWORD>(0x42ecd6, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);
	injector::WriteMemory<DWORD>(0x42c804, (DWORD)((char*)strdup(fdb_videofldr.c_str())), true);

	injector::WriteMemory<DWORD>(0x42c82a, (DWORD)((char*)"s"), true); // VIDEO_S
	injector::WriteMemory<DWORD>(0x42e313, (DWORD)((char*)"s"), true);
	injector::WriteMemory<DWORD>(0x42e5a3, (DWORD)((char*)"s"), true);
	injector::WriteMemory<DWORD>(0x42ecf3, (DWORD)((char*)"s"), true);
	injector::WriteMemory<DWORD>(0x42eefd, (DWORD)((char*)"s"), true);
	injector::WriteMemory<DWORD>(0x497415, (DWORD)((char*)"s"), true);

	// This patch is optional; " gamespy" to anything
	//auto GSStrings = hook::pattern("20 47 61 6D 65 53 70 79");
	//injector::WriteMemory<DWORD>(GSStrings.get_first(22), (DWORD)((char*)" GameEmu"), true);

	 /* ====== Patches ====== */
	injector::WriteMemory<DWORD>(0x446320, (DWORD)((char*)""), true); // No _hq.tga Requirement does a thing (allows transperancy)
	injector::WriteMemory<DWORD>(0x4463dd, (DWORD)((char*)""), true); // No _hq.tga Requirement not required but might help out

	/* SP: BRIEFING */
	  // Mission briefing (info) UI and background placement [SCREENS]
	injector::WriteMemory(0x43090f, ResX, true); // 800
	injector::WriteMemory(0x4308fb, ResY, true); // 600
	std::string pigbrief = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_briefing.tga"; injector::WriteMemory<DWORD>(0x419164, (DWORD)((char*)strdup(pigbrief.c_str())), true);
	std::string rabbrief = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_briefing.tga"; injector::WriteMemory<DWORD>(0x419140, (DWORD)((char*)strdup(rabbrief.c_str())), true);

	/* SP UI TEXT */
	injector::WriteMemory(0x41938F, -(((ResY * 8) / 100) - ResY), true); // CANCEL 7xx
	injector::WriteMemory(0x419394, -(((ResX * 5) / 100) - ResX), true); // CANCEL 553
	injector::WriteMemory(0x41943e, -(((ResY * 8) / 100) - ResY), true); // START on hover CANCEL = crash
	injector::WriteMemory(0x419443, -(((ResX * 5) / 100) - ResX), true); // START
	injector::WriteMemory(0x4194f7, -(((ResY * 8) / 100) - ResY), true); // REPLAY
	injector::WriteMemory(0x4194fc, -(((ResX * 5) / 100) - ResX), true); // REPLAY
	//injector::WriteMemory(0x419569, ResX / 2 - 35 , true); // MISSION DESC instant crash
	injector::WriteMemory(0x41956B, -(((ResX * 52) / 100) - ResX), true); // MISSION DESC
	//injector::WriteMemory(0x4195d0, ResY / 2 , true); // MISSION DESC (from file data) crash
	injector::WriteMemory(0x4195d2, -(((ResX * 53) / 100) - ResX), true); // MISSION DESC (from file data)

	injector::WriteMemory(0x419e62, -(((ResY * 71) / 100) - ResY), true); // Mission image Y
	injector::WriteMemory<unsigned char>(0x419617, -(((ResY * 88) / 100) - ResY), true); // Terittory Props Y (not higher/is not 128)
	injector::WriteMemory<unsigned char>(0x419569, -(((ResY * 88) / 100) - ResY), true); // mission desc Y
	injector::WriteMemory<unsigned char>(0x4195D0, ResY / 8 + 15, true); // mission desc FD TXT Y
	injector::WriteMemory<unsigned char>(0x41967D, ResY / 8 + 15, true); // territory info TXT Y
  //injector::WriteMemory<unsigned char>(0x41967f, ResY / 8 - 10, true); // territory info TXT x
	if ((ResY / 8 + 15 >= 128)) {
		injector::WriteMemory<unsigned char>(0x419617, -(((ResY * 90) / 100) - ResY), true); // Terittory Props Y
		injector::WriteMemory<unsigned char>(0x419569, -(((ResY * 90) / 100) - ResY), true); // mission desc Y
		injector::WriteMemory<unsigned char>(0x4195D0, 127, true); // mission desc FD TXT Y
		injector::WriteMemory<unsigned char>(0x41967D, 127, true); // territory info TXT Y
	}

	injector::WriteMemory(0x419734, -(((ResY * 28) / 100) - ResY), true); // expected TXT (Y)
	injector::WriteMemory(0x419788, -(((ResY * 28) / 100) - ResY), true); // new own TXT (Y)
	injector::WriteMemory(0x419790, -(((ResX * 6) / 100) - ResX), true); // new own TXT X
	injector::WriteMemory(0x4198ba, -(((ResY * 24) / 100) - ResY), true); // expected units icons (y)

	/* SHOP MARKET SCREEN */
	std::string rabshop = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_market.tga";
	injector::WriteMemory<DWORD>(0x42372e, (DWORD)((char*)strdup(rabshop.c_str())), true);
	std::string pigshop = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_market.tga";
	injector::WriteMemory<DWORD>(0x423752, (DWORD)((char*)strdup(pigshop.c_str())), true);

	//injector::WriteMemory(0x TT, ResX - 130, true); // TT

	injector::WriteMemory<unsigned char>(0x42474e, -(((ResY * 94) / 100) - ResY), true); // ANIF Viewer Y (byte) 36 orig. BS SPACER?
	injector::WriteMemory(0x424750, -(((ResX * 81) / 100) - ResX), true); // ANIF Viewer X
	if (ResY > 600) {
		//IF ASPECT (X/Y is > whatever is not 4:3)
		injector::WriteMemory<unsigned char>(0x42474e, 127, true); //anif view y 
		injector::WriteMemory(0x424750, (-(((ResX * 65) / 100) - ResX)), true); // ANIF Viewer X
	}

	injector::WriteMemory(0x42400A, ResX / 5 + 50, true); // stats (numb) from tank X (anif)
	injector::WriteMemory(0x423fa1, ResX / 5, true); // stats (descriptors) from tank X (anif)
	injector::WriteMemory(0x423F74, 50, true); // stats (numb) from tank X (also pads)
	injector::WriteMemory(0x4240B8, -(((ResY * 30) / 100) - ResY), true); // unit cost sp Y
	injector::WriteMemory(0x42418E, -(((ResY * 30) / 100) - ResY), true); // current sp Y
	injector::WriteMemory(0x424071, -(((ResY * 31) / 100) - ResY), true); // tank desc Y
	injector::WriteMemory(0x424158, -(((ResY * 30) / 100) - ResY), true); // upgrade cost y
	injector::WriteMemory(0x42410e, -(((ResY * 31) / 100) - ResY), true); // upgrade desc Y
	injector::WriteMemory(0x42415d, -(((ResX * 11) / 100) - ResX), true); // upgrade cost x
	injector::WriteMemory(0x424113, -(((ResX * 40) / 100) - ResX), true); // upgrade desc x
	injector::WriteMemory(0x423cee, -(((ResY * 15) / 100) - ResY), true); // buy upgrades Y
	injector::WriteMemory(0x423d98, -(((ResY * 15) / 100) - ResY), true); // drop upgrades Y
	injector::WriteMemory(0x4246db, -(((ResY * 20) / 100) - ResY), true); // UPGRADES in tank Y
	injector::WriteMemory(0x4246e6, -(((ResX * 57) / 100) - ResX), true); // UPGRADES in tank X
	injector::WriteMemory(0x4245E0, -(((ResY * 9) / 100) - ResY), true); // UPGRADES for tank Y
	injector::WriteMemory(0x4245eb, -(((ResX * 71) / 100) - ResX), true); // UPGRADES for tank X
	injector::WriteMemory(0x423E58, -(((ResX * 5) / 100) - ResX), true); // CANCEL X
	injector::WriteMemory(0x423E4C, -(((ResY * 8) / 100) - ResY), true); // CANCEL Y
	injector::WriteMemory(0x423F08, -(((ResX * 5) / 100) - ResX), true); // OK X
	injector::WriteMemory(0x423F03, -(((ResY * 8) / 100) - ResY), true); // OK Y

	/**/
	// MY ARMY
	injector::WriteMemory(0x423C44, -(((ResY * 27) / 100) - ResY), true); // SELL (tank) Y
	injector::WriteMemory(0x423B9A, -(((ResY * 27) / 100) - ResY), true); // BUY (tank) Y
	injector::WriteMemory(0x423906, -(((ResY * 37) / 100) - ResY), true); // UNITSSD <-. Y
	injector::WriteMemory(0x423978, -(((ResY * 37) / 100) - ResY), true); // SCROLL UNITSSD Y
	injector::WriteMemory(0x4239E2, -(((ResY * 37) / 100) - ResY), true); // UNITSSD .-> Y

	// WAREHAUS
	injector::WriteMemory(0x42389A, -(((ResX * 10) / 100) - ResX), true); // WAREHOUSE X
	injector::WriteMemory(0x423A4C, -(((ResY * 37) / 100) - ResY), true); // BUYSD <-. Y
	injector::WriteMemory(0x423a51, -(((ResX * 18) / 100) - ResX), true); // BUYSD <-. X
	injector::WriteMemory(0x424415, -(((ResX * 18) / 100) - ResX), true); // BUYSD available tanks to buy X 
	injector::WriteMemory(0x423AA8, -(((ResX * 10) / 100) - ResX), true); // SCROLL BUYSD X
	injector::WriteMemory(0x423aba, -(((ResX * 10) / 100) - ResX), true); // SCROLL BUYSD X (pigs)
	injector::WriteMemory(0x423ac3, -(((ResY * 37) / 100) - ResY), true); // SCROLL BUYSD Y
	injector::WriteMemory(0x423B32, -(((ResX * 4) / 100) - ResX), true); // BUYSD .-> X
	injector::WriteMemory(0x423b2d, -(((ResY * 37) / 100) - ResY), true); // BUYSD .-> Y
	//::WriteMemory(0x424416 // (BUY) AVAILABLE UNITS X - bs worthless, in bytes, default value 2. thanks storm kids!
	//(resets to 0 so one above takes more standart 256, 512 and gives proper nice value), actually whatever not needed, just hardcoded values in weirder fashion.
	// TODO: Missing ANIF like MOVINGFORCE ELITE
	// unit row 004247FC - 244 default / 444 allows movingforce
	// unit desc text area and linebreaks 0042406C

	/* MP titleroom todo: reset coords*/
	std::string fdb_mpshots = "gamedata\\" + basepath + "\\interface\\any\\mp_%02d.tga";
	injector::WriteMemory<DWORD>(0x404511, (DWORD)((char*)strdup(fdb_mpshots.c_str())), true);
	//injector::WriteMemory<DWORD>(0x404511, (DWORD)((char*)"gamedata/base/interface/any/mp_%02d.tga"), true);
	std::string fdb_mprabtitler = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_titleroom.tga";
	injector::WriteMemory<DWORD>(0x404b79, (DWORD)((char*)strdup(fdb_mprabtitler.c_str())), true); // titleroom
	std::string fdb_mppigtitler = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_titleroom.tga";
	injector::WriteMemory<DWORD>(0x404b9d, (DWORD)((char*)strdup(fdb_mppigtitler.c_str())), true); // titleroom

	/* Multiplayer UI TEXT WIP*/
	injector::WriteMemory(0x405acf, ResY / 2 - 20, true); // CHAT ui text
	injector::WriteMemory(0x405b16, ResY / 2 - 10, true); // Players UI txt
	injector::WriteMemory(0x405b1b, ResX / 2 + 80, true); // Players UI txt

	injector::WriteMemory(0x405B61, ResY / 2 + 80, true); // Players list box element
	injector::WriteMemory(0x405B66, ResX / 2 + 80, true); // Players list box element

	injector::WriteMemory(0x405C1A, ResY / 2 + 80, true); // 
	injector::WriteMemory(0x405C1F, ResX / 2 + 80, true); // Chat box element

	/*
	injector::WriteMemory(0x405b1b, ResY / 2 + 80, true); //
	injector::WriteMemory(0x405b1b, ResX / 2 + 80, true); // Browser element
	injector::WriteMemory(0x405b1b, ResY / 2 + 80, true); // Game info browser element (game desc, host players, ping)
	injector::WriteMemory(0x405b1b, ResX / 2 + 80, true); // JoinCreateRefreshCancel element

	 */

	 /* MP chatroom*/
	std::string fdb_mprabchat = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_chatroom.tga";  injector::WriteMemory<DWORD>(0x41ef54, (DWORD)((char*)strdup(fdb_mprabchat.c_str())), true); // chatroom
	std::string fdb_mppigchat = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_chatroom.tga";  injector::WriteMemory<DWORD>(0x41efab, (DWORD)((char*)strdup(fdb_mppigchat.c_str())), true); // chatroom

	std::string fdb_mprabchatnh = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_chatroom_nohost.tga";  injector::WriteMemory<DWORD>(0x41ef7f, (DWORD)((char*)strdup(fdb_mprabchatnh.c_str())), true); // chatroom nohost
	std::string fdb_mppigchatnh = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_chatroom_nohost.tga";  injector::WriteMemory<DWORD>(0x41efd5, (DWORD)((char*)strdup(fdb_mppigchatnh.c_str())), true); // chatroom nohost

	/* MP staging */
	std::string fdb_mprabstg = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\rabbit_chatroom.tga";  injector::WriteMemory<DWORD>(0x401d7a, (DWORD)((char*)strdup(fdb_mprabstg.c_str())), true); // chatroom
	std::string fdb_mppigstg = "gamedata\\" + basepath + "\\interface\\bg\\" + std::to_string(ResX) + "x" + std::to_string(ResY) + "\\pig_chatroom.tga";  injector::WriteMemory<DWORD>(0x401d9b, (DWORD)((char*)strdup(fdb_mppigstg.c_str())), true); // chatroom
   /* ====== Language ====== */
	// graphics and sounds overide

if (bCustomLang) {

	/*			 <~!DEVS!~>				 */
	/* devs*/ //CIniReader langReader("..\\gamedata\\" + basepath + "\\messages.ini"); /// Language Texts
	/* rtm*/ CIniReader langReader("gamedata\\" + basepath + "\\messages.ini"); /// Language Texts

	//457  lines of localization, for faster development and testing 9 is good enough. however .c_str used everywhere else before doesn't play nice here.
char* readlocalizeto[9] = {
"SWINE_OK",
"SWINE_CANCEL",
"SWINE_START",
"SWINE_BACK",
"SWINE_NEXT",
"SWINE_YES",
"SWINE_NO",
"SWINE_SKIP",
"SWINE_QUIT"};

int writelocalizeaddr[9] = {
0x4144e7,
0x403fd4,
0x41946a,
0x414c97,
0x487605,
0x47dd84,
0x4177ef,
0x48757d,
0x417f81
};

	for (int i = 0; i < 9; i++) {
		std::string translx = langReader.ReadString("messages", readlocalizeto[i], "unlocalized");
		const char* transwrite = translx.c_str();

		injector::WriteMemory<DWORD>(writelocalizeaddr[i], (DWORD)transwrite, true);
		//injector::WriteMemory<DWORD>(0x417f81, (DWORD)transwriter, true); //#1
	}

}
  // if russian, override font

  // Load basepath lang.ini
  // text strings override


 /* ====== Mods ====== */
  injector::WriteMemory<unsigned char>(0x42cc68, 0xEB, true); // Disable tamper check (JMP)


  srand(time(NULL)); // we don't want same numbers all the time, needs time.h
  int egger = rand() % 100;
  if (egger < 15){
	// if egger is below chance, the tank will hit the target
  injector::WriteMemory<DWORD>(0x42e352, (DWORD)"/logogg.avi", true); //#1
  injector::WriteMemory<DWORD>(0x42E5D0, (DWORD)"/logogg.avi", true); //#2
  }

  std::string fdb_unitsini = "gamedata\\" + basepath + "\\units.ini";
  injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)strdup(fdb_unitsini.c_str())), true);
  injector::WriteMemory<DWORD>(0x496add, (DWORD)((char*)strdup(fdb_unitsini.c_str())), true);

  std::string fdb_unitstxtini = "gamedata\\" + basepath + "\\units_txt.ini";
  injector::WriteMemory<DWORD>(0x496b11, (DWORD)((char*)strdup(fdb_unitstxtini.c_str())), true);

  std::string fdb_tutotxtini = "gamedata\\" + basepath + "\\tutorial_txt.ini";
  injector::WriteMemory<DWORD>(0x49902e, (DWORD)((char*)strdup(fdb_tutotxtini.c_str())), true);

  std::string fdb_missionsini = "gamedata\\" + basepath + "\\missions.ini";
  injector::WriteMemory<DWORD>(0x496a3e, (DWORD)((char*)strdup(fdb_missionsini.c_str())), true);

  std::string fdb_missionstxtini = "gamedata\\" + basepath + "\\missions_txt.ini";
  injector::WriteMemory<DWORD>(0x496a6f, (DWORD)((char*)strdup(fdb_missionstxtini.c_str())), true);

  std::string fdb_tipstxtini = "gamedata\\" + basepath + "\\tips_txt.ini";
  injector::WriteMemory<DWORD>(0x402313, (DWORD)((char*)strdup(fdb_tipstxtini.c_str())), true);
  injector::WriteMemory<DWORD>(0x48738d, (DWORD)((char*)strdup(fdb_tipstxtini.c_str())), true);

  std::string fdb_objtxtini = "gamedata\\" + basepath + "\\objects.ini";
  injector::WriteMemory<DWORD>(0x4cad0d, (DWORD)((char*)strdup(fdb_objtxtini.c_str())), true);

  //injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)"gamedata/units.ini"), true);
  //injector::WriteMemory<DWORD>(0x496add, (DWORD)((char*)"gamedata/units.ini"), true);

  injector::WriteMemory<float>(0x4CB3A9, CamMaxZoomIn, true); // Max zoom in DEF: 10
  injector::WriteMemory<float>(0x4CB3B3, CamMaxZoomOut, true); // Max zoom out DEF: 20
  injector::WriteMemory<float>(0x4CB395, CamMaxAngleUp, true); // Max angle up DEF: -1.13
  injector::WriteMemory<float>(0x4CB39F, CamMaxAngleDown, true); // Max angle down DEF: -0.7
  injector::WriteMemory<float>(0x4CB3D5, CamMapLimit, true); // Map Cameralimit DEF: 48

  std::string fdb_panelstatus = "gamedata\\" + basepath + "\\interface\\panel\\status.tga";  injector::WriteMemory<DWORD>(0x409598, (DWORD)((char*)strdup(fdb_panelstatus.c_str())), true);
  //injector::WriteMemory<DWORD>(0x409598, (DWORD)((char*)"gamedata/basemod/interface/panel/status.tga"), true); //panel status (must have _hq in name w/o 446320)
  std::string fdb_paneltga = "gamedata\\" + basepath + "\\interface\\panel\\panel.tga";  injector::WriteMemory<DWORD>(0x4082ba, (DWORD)((char*)strdup(fdb_paneltga.c_str())), true);
  std::string fdb_panelai = "gamedata\\" + basepath + "\\interface\\panel\\panel_ai.tga";  injector::WriteMemory<DWORD>(0x40873a, (DWORD)((char*)strdup(fdb_panelai.c_str())), true);
  std::string fdb_panelspec = "gamedata\\" + basepath + "\\interface\\panel\\panel_spec.tga";  injector::WriteMemory<DWORD>(0x408ba8, (DWORD)((char*)strdup(fdb_panelspec.c_str())), true);
  std::string fdb_panelmapgroup = "gamedata\\" + basepath + "\\interface\\panel\\map_group.tga";  injector::WriteMemory<DWORD>(0x409090, (DWORD)((char*)strdup(fdb_panelmapgroup.c_str())), true);


  std::string fdb_menuload = "gamedata\\" + basepath + "\\interface\\menu\\loading.tga"; injector::WriteMemory<DWORD>(0x409ef4, (DWORD)((char*)strdup(fdb_menuload.c_str())), true);
 injector::WriteMemory<DWORD>(0x40a531, (DWORD)((char*)strdup(fdb_menuload.c_str())), true); injector::WriteMemory<DWORD>(0x40aef4, (DWORD)((char*)strdup(fdb_menuload.c_str())), true);
  std::string fdb_menuloadico = "gamedata\\" + basepath + "\\interface\\menu\\loading_icons.tga"; injector::WriteMemory<DWORD>(0x4aed1d, (DWORD)((char*)strdup(fdb_menuloadico.c_str())), true);
  std::string fdb_menurabbase = "gamedata\\" + basepath + "\\interface\\menu\\rabbit_menu_base.tga"; injector::WriteMemory<DWORD>(0x42db63, (DWORD)((char*)strdup(fdb_menurabbase.c_str())), true);
  std::string fdb_menurabbmsg = "gamedata\\" + basepath + "\\interface\\menu\\rabbit_message.tga"; injector::WriteMemory<DWORD>(0x474975, (DWORD)((char*)strdup(fdb_menurabbmsg.c_str())), true);
  std::string fdb_menupigbase = "gamedata\\" + basepath + "\\interface\\menu\\pig_menu_base.tga"; injector::WriteMemory<DWORD>(0x42dee0, (DWORD)((char*)strdup(fdb_menupigbase.c_str())), true);
  std::string fdb_menupigmsg = "gamedata\\" + basepath + "\\interface\\menu\\pig_message.tga"; injector::WriteMemory<DWORD>(0x474990, (DWORD)((char*)strdup(fdb_menupigmsg.c_str())), true);
  std::string fdb_menuselect = "gamedata\\" + basepath + "\\interface\\menu\\selection.tga"; injector::WriteMemory<DWORD>(0x4cabfc, (DWORD)((char*)strdup(fdb_menuselect.c_str())), true);
  //std::string fdb_menuxxx = "gamedata/" + basepath + "/interface/menu/loading.tga"; injector::WriteMemory<DWORD>(0x409ef4, (DWORD)((char*)strdup(fdb_menuxxx.c_str())), true);

  /* ==== UNLIMITER ====*/

  //injector::WriteMemory<unsigned char>(0x4287bd, 0x74, true); // Unit unlimiter (BUG: Unit icons)
 
  if (bModdedTanklist)
  {

	  int i, tanks = 0, characters = 0;
	  std::string strDL;
	  /*			 <~!DEVS!~>				 */
	  //std::ifstream file("tanks.txt");
	  std::ifstream file("gamedata\\" + basepath + "\\tanks.txt");
	  std::string str2;
	  while (std::getline(file, str2)) {
		  //check characters
		  for (i = 0; str2[i] != '\0'; i++) {
			  if (str2[i] != '\0') {
				  characters++;
			  }
		  }
		  strDL.append(str2);                       // "Writing "
		  strDL.append((64 - characters), '\0');                    // ".........."

		  tanks++; /* CONFIRMED: TANKS COUNTER AND WRITING WORKS PROPERLY AS IT SHOULD, thus problem is with final write, not reading*/
		  characters = 0;
	  }

	  //injector::WriteMemory<DWORD>(0x409ef4, (DWORD)((char*)strdup(fdb_menuxxx.c_str())), true);
	  //char* aNyulDzsip = strDL;

	  // also theres lil glitch making SP: 13, starting mission lets you use unspemt (eg. had 1000, spent 10, remains 3, inmission you can spend rest 900)
	  // increasing via cheats, causes anif error for some tanks. clicking too fast into 3rd slider, same. plus glitched icons, sometimes uses even background graphics.

	  injector::WriteMemory<unsigned char>(0x41995c, tanks, true); // ICON? HOW MANY TANKS DO WE HAVE FOR USE IN CAMPAIGN? (/p-01)
	  injector::WriteMemory<unsigned char>(0x419c62, tanks, true); // ICON (e.g. briefing) max 127
	  injector::WriteMemory<unsigned char>(0x42878e, tanks, true); // MARKET STORE CLASS NAMES. Max 127
	  injector::WriteMemory<unsigned char>(0x42480f, tanks, true); // market BUY SIDE AVAILABLE FOR PURCHASE (too much might give a crash). 
	  //^causes money glitch. selling something will give buy side anif error IF too many characters in unit mask
	  // DO NOT DUPLICATE (e.g. Service, fuel, ammo)
	  //injector::WriteMemory<unsigned char>(0x42420B, tanks, true); // <!-- Problem maker, and a very useless one market icon loader !instant crash, lower value like 14 does nothing. high invalid child parameter.
	  // seems to allow to have third slider? nah

	  // not effective 
		   //injector::WriteMemory<unsigned char>(0x418ee6, 14, true); // the very TEST - nothing?
	  //injector::WriteMemory<unsigned char>(0x418faf, tanks, true); // the very TEST - font index err
	  //injector::WriteMemory<unsigned char>(0x4233d2, tanks, true); // the very TEST - exiting font index err
	  //injector::WriteMemory<unsigned char>(0x42480f, tanks, true); // the very TEST %sp nothing
	  //injector::WriteMemory<unsigned char>(0x428ced, tanks, true); // the very TEST nothing
	  //injector::WriteMemory<unsigned char>(0x4ed5e7, tanks, true); // the very TEST  nothing, althought fast clicking to 3rd row crashes

	  //char* aNyulDzsip = { "Nyul dzsip\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul pancelauto\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul light tank\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul loveg\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul raketas pancelkocsi\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul raketas\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul mozsar\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul aknarako\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul vontato\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Ammo\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Fuel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Service\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Nyul movingforce\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Spy\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno dzsip\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno pancelauto\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno normal tank\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno loveg\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno hard tank\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno raketas\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno mozsar\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno aknarako\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno vontato\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Ammo\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Fuel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Service\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0Diszno movingforce\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" };
	  //char* aNyulDzsip = { ((char*)strdup(strDL.c_str())) };


	  int nyulstringlen = strDL.size();
	  char* aNyulDzsip = new char[nyulstringlen + 1];
	  std::copy(strDL.begin(), strDL.end(), aNyulDzsip);
	  aNyulDzsip[nyulstringlen] = '\0';

	  // calls to spot where campaign units are listed
	  injector::WriteMemory<DWORD>(0x4199ef, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419a50, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419aae, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419b51, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419b84, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419cc8, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419d72, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x419dad, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x424238, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x4242b4, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x424330, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x425004, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x42545e, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x4287aa, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x429068, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(0x429947, (DWORD)aNyulDzsip, true);
	  //injector::WriteMemory<DWORD>(0x5431B8, (DWORD)aNyulDzsip, true); // 0x5431B8 .. 0x5431b0 not worth to use

  }

  /* tests */
  if (bEnableExperimentResPW)
  {
	  // something here centers warehouse headquartes, makes it look problem free, noticed after implementing experimental patches when finishing with this project for good.

	  // no idea
	  injector::WriteMemory(0x406486, ResX, true); // 800 0x320 2003
	  injector::WriteMemory(0x40647a, ResY, true); // 600 0x258 5802

	// no idea
	  injector::WriteMemory(0x4110f9, ResX, true); // 800
	  injector::WriteMemory(0x4110f4, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x411115, ResX, true); // 800
	  injector::WriteMemory(0x411104, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4111f3, ResX, true); // 800
	  injector::WriteMemory(0x4111EE, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41120f, ResX, true); // 800
	  injector::WriteMemory(0x4111fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4112f3, ResX, true); // 800
	  injector::WriteMemory(0x4112ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41130f, ResX, true); // 800
	  injector::WriteMemory(0x4112fe, ResY, true); // 600

	  // no idea
	  injector::WriteMemory(0x4113f3, ResX, true); // 800
	  injector::WriteMemory(0x4113ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41140f, ResX, true); // 800
	  injector::WriteMemory(0x4113fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4114f3, ResX, true); // 800
	  injector::WriteMemory(0x4114ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41150f, ResX, true); // 800
	  injector::WriteMemory(0x4114fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4115f3, ResX, true); // 800
	  injector::WriteMemory(0x4115ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41160f, ResX, true); // 800
	  injector::WriteMemory(0x4115fe, ResY, true); // 600 0x258 5802

	// no idea 
	  injector::WriteMemory(0x4116f3, ResX, true); // 800
	  injector::WriteMemory(0x4116ee, ResY, true); // 600

	  // no idea 
	  injector::WriteMemory(0x41170f, ResX, true); // 800
	  injector::WriteMemory(0x4116fe, ResY, true); // 600

	/* ^ no specialities */

	// no idea
	  injector::WriteMemory(0x4117f3, ResX, true); // 800
	  injector::WriteMemory(0x4117ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41180f, ResX, true); // 800
	  injector::WriteMemory(0x4117fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4118f3, ResX, true); // 800
	  injector::WriteMemory(0x4118ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x41190f, ResX, true); // 800
	  injector::WriteMemory(0x4118fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x4119f3, ResX, true); // 800
	  injector::WriteMemory(0x4119ee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x411a0f, ResX, true); // 800
	  injector::WriteMemory(0x4119fe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x411af3, ResX, true); // 800
	  injector::WriteMemory(0x411aee, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x411b0f, ResX, true); // 800
	  injector::WriteMemory(0x411afe, ResY, true); // 600

	// no idea
	  injector::WriteMemory(0x42f057, ResX, true); // 800
	  injector::WriteMemory(0x42f046, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f14b, ResX, true); // 800
	  injector::WriteMemory(0x42f146, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f167, ResX, true); // 800
	  injector::WriteMemory(0x42f156, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f25b, ResX, true); // 800
	  injector::WriteMemory(0x42f256, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f277, ResX, true); // 800
	  injector::WriteMemory(0x42f266, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f36b, ResX, true); // 800
	  injector::WriteMemory(0x42f366, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f387, ResX, true); // 800
	  injector::WriteMemory(0x42f376, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f47b, ResX, true); // 800
	  injector::WriteMemory(0x42f476, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f497, ResX, true); // 800
	  injector::WriteMemory(0x42f486, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f58b, ResX, true); // 800
	  injector::WriteMemory(0x42f586, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f5a7, ResX, true); // 800
	  injector::WriteMemory(0x42f596, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f693, ResX, true); // 800
	  injector::WriteMemory(0x42f68e, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x42f6af, ResX, true); // 800
	  injector::WriteMemory(0x42f69e, ResY, true); // 600

  // no idea near mp
	  injector::WriteMemory(0x42f8b8, ResX, true); // 800
	  injector::WriteMemory(0x42f8b3, ResY, true); // 600

  // no idea mp
	  injector::WriteMemory(0x42f8da, ResX, true); // 800
	  injector::WriteMemory(0x42f8c6, ResY, true); // 600

  // no idea near direct ip
	  injector::WriteMemory(0x42faee, ResX, true); // 800
	  injector::WriteMemory(0x42fae9, ResY, true); // 600

  // no idea mp direct ip
	  injector::WriteMemory(0x42fb0a, ResX, true); // 800
	  injector::WriteMemory(0x42faf9, ResY, true); // 600

  // no idea lan
	  injector::WriteMemory(0x42fc3e, ResX, true); // 800
	  injector::WriteMemory(0x42fc39, ResY, true); // 600

  // no idea lan
	  injector::WriteMemory(0x42fc5a, ResX, true); // 800
	  injector::WriteMemory(0x42fc49, ResY, true); // 600

  // no idea gamespy
	  injector::WriteMemory(0x42fd80, ResX, true); // 800
	  injector::WriteMemory(0x42fd7b, ResY, true); // 600

  // no idea gamespy
	  injector::WriteMemory(0x42fd9c, ResX, true); // 800
	  injector::WriteMemory(0x42fd8b, ResY, true); // 600

  // no idea gamespy
	  injector::WriteMemory(0x42fec0, ResX, true); // 800
	  injector::WriteMemory(0x42febb, ResY, true); // 600

  // no idea gamespy
	  injector::WriteMemory(0x42fedc, ResX, true); // 800
	  injector::WriteMemory(0x42fecb, ResY, true); // 600

  // no idea chatroom
	  injector::WriteMemory(0x430730, ResX, true); // 800
	  injector::WriteMemory(0x43072b, ResY, true); // 600

  // no idea chatroom
	  injector::WriteMemory(0x43074c, ResX, true); // 800
	  injector::WriteMemory(0x43073b, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x430a2b, ResX, true); // 800
	  injector::WriteMemory(0x430a26, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x430a4d, ResX, true); // 800
	  injector::WriteMemory(0x430a39, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x430e46, ResX, true); // 800
	  injector::WriteMemory(0x430e41, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x430e68, ResX, true); // 800
	  injector::WriteMemory(0x430e54, ResY, true); // 600

  // no idea
	  injector::WriteMemory(0x4334d4, ResX, true); // 800
	  injector::WriteMemory(0x4334cf, ResY, true); // 600

  // no idea

	  injector::WriteMemory(0x433ac4, ResX, true); // 800
	  injector::WriteMemory(0x433abf, ResY, true); // 600
  }
/* ======================== END INDEX IGNORE ======================= */

// LATER CODE STRUCTURES

	/* === MYSTERY / PLAYGOUND === */


	/* nothing responsible here for initial start main menu mouse grab injector::WriteMemory(0x4331FB, ResX, true); // 800 - 320

	injector::WriteMemory(0x41321a, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x413e8e, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41442a, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x415e9e, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41567e, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x414bda, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41fd61, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41ffab, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x429109, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x418a58, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41b784, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41a89f, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41676e, ResY, true); // 600 - 258 (near 1cc - 460)
	injector::WriteMemory(0x41727e, ResY, true); // 600 - 258 (near 1cc - 460) */

}


BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        Init();
    }
    return TRUE;
}