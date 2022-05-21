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

		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA0C3, tanks, true); // @ E94C3
		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA0FF, tanks, true); // @ E94FF

		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEA1A4, tanks, true); // @ E95A4
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEA2DD, tanks, true); // @ E96DD
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEA350, tanks, true); // @ E9750
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEA385, tanks, true); // @ E9785

		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEF8F5, tanks, true); // @ EECF5
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xEF94A, tanks, true); // @ EED4A
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF014F, tanks, true); // @ EF54F

	  // 
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF08C9, tanks, true); // @ EFCC9
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF08E6, tanks, true); // @ EFCE6
	  // 
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF323F, tanks, true); // @ F263F
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF3E0B, tanks, true); // @ F320B
	  //
		  injector::WriteMemory<unsigned char>(BaseAddressptr+ 0xF4B32, tanks, true); // @ F3F32
		  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF4B42, tanks, true); // @ F3F42

		  if (bEnableExperimentResPW) {
			  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEF89F, tanks, true); // @ EEC9F breaks same icon for every
			  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xF4868, tanks, true); // @ F3C68 breaks: first tank is every tank
			  injector::WriteMemory<unsigned char>(BaseAddressptr + 0xEA137, tanks, true); // @ E9537  breaks briefing enemy side tank icons
		  }


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
		  injector::WriteMemory<DWORD>(BaseAddressptr + 0x9ADFD, (DWORD)aNyulDzsip, true); // hI i WaNnA CrAsH note: before tank counter implementation
		  injector::WriteMemory<DWORD>(BaseAddressptr + 0xEFB6D, (DWORD)aNyulDzsip, true); // MARKET 3 CRASH
		  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF058D, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
		  injector::WriteMemory<DWORD>(BaseAddressptr + 0xF071F, (DWORD)aNyulDzsip, true); // CRASH ON INGAME BUY
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