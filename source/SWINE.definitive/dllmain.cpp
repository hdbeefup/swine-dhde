#include "stdafx.h"

const char* relEdition = {"~~~### S.W.I.N.E. Super Remaster. Darius (DW5) ### bads.tm ### github.com/hdbeefup ### (C) 2016-2021 ~~~ Source code available under GPL3 License (ᵔ◡ᵔ)"};

// base adress ??

char multiplayerIP;
float CamMaxZoomIn, CamMaxZoomOut, CamMaxAngleUp, CamMaxAngleDown, CamMapLimit;
int SWINEEdi;
bool bEnableExperimentResPW, bModdedTanklist, bEnableCheats, bMapRotate, bUseWASD, bDevMode;

void Init()
{
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
	std::string TakeoverMD = "%s S.W.I.N.E. v%d.%d.%d Super Remaster | dw5 | Compiled at " __DATE__ ", " __TIME__ " |"; // S.W.I.N.E. %s v%d.%d.%d
	//injector::WriteMemory<DWORD>(BaseAddress-0x28F77, (DWORD)((char*)strdup(TakeoverMD.c_str())), true);
	injector::WriteMemory<DWORD>(BaseAddressptr + 0x6DB46, (DWORD)((char*)strdup(TakeoverMD.c_str())), true); // Relative Virtual Address... fancyyy
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

	  //injector::WriteMemory<DWORD>(0x409ef4, (DWORD)((char*)strdup(fdb_menuxxx.c_str())), true);
	  //char* aNyulDzsip = strDL;

	  // also theres lil glitch making SP: 13, starting mission lets you use unspemt (eg. had 1000, spent 10, remains 3, inmission you can spend rest 900)
	  // increasing via cheats, causes anif error for some tanks. clicking too fast into 3rd slider, same. plus glitched icons, sometimes uses even background graphics.

	 /* injector::WriteMemory<unsigned char>(0x41995c, tanks, true); // ICON? HOW MANY TANKS DO WE HAVE FOR USE IN CAMPAIGN? (/p-01)
	  injector::WriteMemory<unsigned char>(0x419c62, tanks, true); // ICON (e.g. briefing) max 127
	  injector::WriteMemory<unsigned char>(0x42878e, tanks, true); // MARKET STORE CLASS NAMES. Max 127
	  injector::WriteMemory<unsigned char>(0x42480f, tanks, true); // market BUY SIDE AVAILABLE FOR PURCHASE (too much might give a crash). 
	  *///^causes money glitch. selling something will give buy side anif error IF too many characters in unit mask
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

	  int nyulstringlen = strDL.size();
	  char* aNyulDzsip = new char[nyulstringlen + 1];
	  std::copy(strDL.begin(), strDL.end(), aNyulDzsip);
	  aNyulDzsip[nyulstringlen] = '\0';
	  
	  // calls to spot where campaign units are listed
	  //injector::WriteMemory<DWORD>(BaseAddressptr + 0xEFB6D, (DWORD)aNyulDzsip, true); // MARKET 3 CRASH
	  //injector::WriteMemory<DWORD>(BaseAddressptr + 0xF058D, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF4B49, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA2EA, (DWORD)aNyulDzsip, true); // EA2EA 
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF488C, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF3E20, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF3254, (DWORD)aNyulDzsip, true);
	  //injector::WriteMemory<DWORD>(BaseAddressptr + 0x9ADFD, (DWORD)aNyulDzsip, true); // hI i WaNnA CrAsH
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF906, (DWORD)aNyulDzsip, true); // MARKET 2 crash
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF8B0, (DWORD)aNyulDzsip, true); // MARKET 1 crash aka both

	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA1BC, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA14E, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA0DA, (DWORD)aNyulDzsip, true);
	  //injector::WriteMemory<DWORD>(BaseAddressptr + 0xF071F, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF0160, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEF95B, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA35D, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA392, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEA116, (DWORD)aNyulDzsip, true);
	  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF08D0, (DWORD)aNyulDzsip, true);
	  //injector::WriteMemory<DWORD>(0x5431B8, (DWORD)aNyulDzsip, true); // 0x5431B8 .. 0x5431b0 not worth to use

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