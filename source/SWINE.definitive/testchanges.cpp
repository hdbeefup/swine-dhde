#include "stdafx.h"

std::string relEdition = {"~~~### S.W.I.N.E. Super Remaster. Darius (DW5) ### bads.tm ### github.com/hdbeefup ### (C) 2016-2021 ~~~ Source code available under GPL3 License (ᵔ◡ᵔ)"};

// base adress ??

char multiplayerIP;
float CamMaxZoomIn, CamMaxZoomOut, CamMaxAngleUp, CamMaxAngleDown, CamMapLimit;
int SWINEEdi;
bool bEnableExperimentResPW, bModdedTanklist, bEnableCheats, bMapRotate, bUseWASD, bDevMode;

void Init()
{
	OutputDebugStringA("Hello HDBEEFUP!");
	auto BaseAddressptr = (uintptr_t)GetModuleHandle(NULL);
	OutputDebugStringA("Hello HDBEEFUP!");

	CIniReader iniReader("swinechdb.ini"); /// HDB Settings

	bModdedTanklist = iniReader.ReadInteger("Mods", "TanklistMod", 0);
	bEnableExperimentResPW = iniReader.ReadInteger("Patchworks", "EnableExperimentResPW", 0);
	bEnableCheats = iniReader.ReadInteger("Patchworks", "EnableCheats", 0);
	bMapRotate = iniReader.ReadInteger("Patchworks", "TESTNoMapRotate", 0);
	bUseWASD = iniReader.ReadInteger("Patchworks", "TESTRipArrowsUseWASD", 0);

	// Mods
	int ColorMM = iniReader.ReadInteger("Mods", "ColorMainMenu", 0xF0F0F0); // COLOR
	int ColorHOV = iniReader.ReadInteger("Mods", "ColorMainMenuHOV", 0xFFFFFF); // COLOR HOVER
	injector::WriteMemory<int>(BaseAddressptr+0xEA74F, ColorMM, true); // COLOR
	injector::WriteMemory<int>(BaseAddressptr+0xEA754, ColorHOV, true); // COLOR HOVER

	std::string MPMasterlist = iniReader.ReadString("Mods", "MultiplayerMaster", "nat.kite-games.com"); // Multiplayer hub
    injector::WriteMemory<DWORD>(BaseAddressptr+0x73F52, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
    injector::WriteMemory<DWORD>(BaseAddressptr+0x73F63, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com
    injector::WriteMemory<DWORD>(BaseAddressptr+0x73F92, (DWORD)((char*)strdup(MPMasterlist.c_str())), true); // master.gamespy.com

	// Camera 
	CamMaxZoomIn = iniReader.ReadFloat("Camera", "MaxZoomIn", 10.0f);
	CamMaxZoomOut = iniReader.ReadFloat("Camera", "MaxZoomOut", 20.0f);
	CamMaxAngleUp = iniReader.ReadFloat("Camera", "MaxAngleUp", -1.13f);
	CamMaxAngleDown = iniReader.ReadFloat("Camera", "MaxAngleDown", -0.7f);
	CamMapLimit = iniReader.ReadFloat("Camera", "MapCameraLimit", 48.0f);

	//injector::WriteMemory<DWORD>(0x43A85E, (DWORD)Takeover, true);
	
	std::string TakeoverMD = "S.W.I.N.E. Definitive %s Edition v%d.%d.%d | dw5 | Compiled at " __DATE__ ", " __TIME__ " |"; // %s must be first otherwise crash| S.W.I.N.E. %s v%d.%d.%d
	injector::WriteMemory<DWORD>(BaseAddressptr + 0x6DB46, (DWORD)((char*)strdup(TakeoverMD.c_str())), true); // @ 6CF46 Relative Virtual Address... fancyyy
	
	//injector::WriteMemory<unsigned char>(0x43a82d, 11, true); // SWINE Edition (byte)

 /* ====== Mods ====== */
  injector::WriteMemory<unsigned char>(BaseAddressptr+0xDF7AB, 0x85, true); // Enable Cheats 0x9bf7ab || DF7AB direct, less direct 0xDF7DB

  //std::string fdb_unitsini = "gamedata\\" + basepath + "\\units.ini";
  //injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)strdup(fdb_unitsini.c_str())), true);

  //injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)"gamedata/units.ini"), true);
  //injector::WriteMemory<DWORD>(0x496add, (DWORD)((char*)"gamedata/units.ini"), true);

	 
  injector::WriteMemory<float>(BaseAddressptr+0xCDD71, CamMaxZoomIn, true); // Max zoom in DEF: 11
  injector::WriteMemory<float>(BaseAddressptr+0xCD874, CamMaxZoomIn, true); // Max zoom in DEF: 11
  injector::WriteMemory<float>(BaseAddressptr+0xCDD78, CamMaxZoomOut, true); // Max zoom out DEF: 22
  injector::WriteMemory<float>(BaseAddressptr+0xCD87B, CamMaxZoomOut, true); // Max zoom out DEF: 22
  injector::WriteMemory<float>(BaseAddressptr+0xCDD63, CamMaxAngleUp, true); // Max angle up DEF: -1.13
  injector::WriteMemory<float>(BaseAddressptr+0xCD866, CamMaxAngleUp, true); // Max angle up DEF: -1.13
  injector::WriteMemory<float>(BaseAddressptr+0xCDD6A, CamMaxAngleDown, true); // Max angle down DEF: -0.7
  injector::WriteMemory<float>(BaseAddressptr+0xCD86D, CamMaxAngleDown, true); // Max angle down DEF: -0.7
  //injector::WriteMemory<float>(0x4CB3D5, CamMapLimit, true); // Map Cameralimit DEF: 48 || hd remaster does not have it
   
  if (bModdedTanklist)
  {
	  OutputDebugStringA("Using UNIT UNLIMITER");

	  int i, tanks = 0, characters = 0;
	  std::string strDL;
	  /*			 <~!DEVS!~>				 */
	  std::ifstream file("tanks.txt");
	  //if (bDevMode) { std::ifstream file("gamedata\\" + basepath + "\\tanks.txt"); } else { std::ifstream file("gamedata\\" + basepath + "\\tanks.txt"); }

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

	  //OutputDebugStringA("-----TANKS COUNTED: " + tanks);
	  char debugMsg[256];
	  sprintf(debugMsg, "-------TANKS COUNTED: %d", tanks);
	  OutputDebugStringA(debugMsg);

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA0C3, tanks, true); // @ 13 E94C3  ICON? HOW MANY TANKS DO WE HAVE FOR USE IN CAMPAIGN? (/p-01)
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA0FF, tanks, true); // @ 13 E94FF

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA1A4, tanks, true); // @ 13 E95A4
	  //X injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEA2DD, tanks, true); // @ E96DD new own units YUP
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA350, tanks, true); // @ 13 E9750
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA385, tanks, true); // @ 13 E9785

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEF8F5, tanks, true); // @ 13 EECF5
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEF94A, tanks, true); // @ 13 EED4A
	  //X injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF014F, tanks, true); // @ EF54F causes bugged icons

	  //X injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF08C9, tanks, true); // @ EFCC9 this disabled allows to buy things but still bugged icons ingame market
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF08E6, tanks, true); // @ 13 EFCE6 NEAR MARKET CLASS

	  //X injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF323F, tanks, true); // @ F263F class name not found
	  //X injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF3E0B, tanks, true); // @ F320B new own units fix? also ingame market prices

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF4B32, tanks, true); // @ 13 F3F32
	  //X injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF4B42, tanks, true); // @ F3F42 this disabled. buys into void

	 //?injector::WriteMemory<unsigned char>(BaseAddressptr + 0x9B28D, tanks, true); // @ 9A68D ?? 11
	 
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA270, tanks, true); // @ 13 E9670 new (ICON (e.g. briefing) max 127 | aka near '%s - %s'

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEFD91, tanks, true); // @ EF191 THIS IS A VERY GOOD BOY

	  
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xBD53A, tanks, true); // @ BC93A "LASS" method
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xBD52C, tanks, true); // @ BC92C "LASS" method

	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB5351, tanks, true); // @ B4751 "BUFF" method
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB53F6, tanks, true); // @ B47F6 "BUFF" method
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB549B, tanks, true); // @ B489B "BUFF" method
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB5A87, tanks, true); // @ B4E87 "BUFF" method HOP
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB5B2C, tanks, true); // @ B4F2C "BUFF" method
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB8427, tanks, true); // @ B7827 "BUFF" method hop
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB8ED7, tanks, true); // @ B82D7 "BUFF" method hop
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB8C21, tanks, true); // @ B8021 "BUFF" method hop
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB87E8, tanks, true); // @ B7BE8 "BUFF" method hop
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xB7D6C, tanks, true); // @ xxB7D6Cxxx "BUFF" method hop
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0XB6451, tanks, true); // @ B5851 "BUFF" method hop
	  //*/
	  

	  // -- REVISI PROBLM?
	   
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xBE103, tanks, true); // @ BC93A "ffs" method nhv
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xC53BD, tanks, true); // @ BC92C "ffs" method nhv
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xC5A3E, tanks, true); // @ BC93A "ffs" method nhv
	  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xD406E, tanks, true); // @ BC92C "ffs" method nhv
	  
	  

	  if (bEnableExperimentResPW) {
		 // injector::WriteMemory<unsigned char>(BaseAddressptr + 0xE876E, tanks, true); // @  "ffs" method PROBLEM IN BRIEFING??
  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xE8D02, tanks, true); // @  "ffs" method SEEMS PROBLEMAIC, INSTEAD OF INSTACRASH, WHEN THIS IS DISABLED, MUSIC PLAYS INSTEAD BUT CRASHES LATER

		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xED5DF, tanks, true); // @  "ffs" method nice guess but no
		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xED620, tanks, true); // @  "ffs" method SEEMS LIKE NEED MUST TO HAVE

		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xED6B6, tanks, true); // @  "ffs" method must NEED have MARKET
		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xED9B8, tanks, true); // @  "ffs" method (no effect?)

		  //injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEF997, tanks, true); // @ EED97 invalid child
		  //injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF019B, tanks, true); // @ EF59B font leak?
		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF08E6, tanks, true); // @ EFCE6 nothing 0 impact SEEMS LIKE NEED MUST TO HAVE


		  // -- REVISI PROBLM?


		 // injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEF89F, tanks, true); // @ EEC9F breaks same icon for every (ICON)
		 // injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF4868, tanks, true); // @ F3C68 breaks: first tank is every tank (PRICE)
	   //injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA137, tanks, true); // @ E9537 --breaks briefing enemy side tank icons--
  }

	  OutputDebugStringA("Start NYULing!");


	  int nyulstringlen = strDL.size();
	  char* aNyulDzsip = new char[nyulstringlen + 1];
	  std::copy(strDL.begin(), strDL.end(), aNyulDzsip);
	  aNyulDzsip[nyulstringlen] = '\0';
	  
	  // calls to spot where campaign units are listed

	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF4B49, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA2EA, (DWORD)aNyulDzsip, true); // EA2EA 
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF488C, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF3E20, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF3254, (DWORD)aNyulDzsip, true);


	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF906, (DWORD)aNyulDzsip, true); // MARKET 2
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF8B0, (DWORD)aNyulDzsip, true); // MARKET 1

	  if (bEnableExperimentResPW)
	  {
		  //injector::WriteMemory<DWORD>(BaseAddressptr + 0x9ADFD, (DWORD)aNyulDzsip, true); // hI i WaNnA CrAsH note: before tank counter implementation
		 // injector::WriteMemory<DWORD>(BaseAddressptr + 0xEFB6D, (DWORD)aNyulDzsip, true); // MARKET 3 CRASH
		//  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF058D, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
		 // injector::WriteMemory<DWORD>(BaseAddressptr + 0xF071F, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
	  }

	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA1BC, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA14E, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA0DA, (DWORD)aNyulDzsip, true);

	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF0160, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF95B, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA35D, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA392, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA116, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF08D0, (DWORD)aNyulDzsip, true);
	  //injector::WriteMemory<DWORD>(0x5431B8, (DWORD)aNyulDzsip, true); // 0x5431B8 .. 0x5431b0 not worth to use
	  OutputDebugStringA("==UNLIMITER END==");
 }
  
}


BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        Init();
    }
    return TRUE;
}
