#include "stdafx.h"

const char* relEdition = { "~~~### S.W.I.N.E. Super Remaster Editor BEEFUP. Darius (DW5) ### bads.tm ### github.com/hdbeefup ### (C) 2016-2021 ~~~ Source code available under GPL3 License (ᵔ◡ᵔ)" };

// base adress ??

char multiplayerIP;
float CamMaxZoomIn, CamMaxZoomOut, CamMaxAngleUp, CamMaxAngleDown, CamMapLimit;
int SWINEEdi;
bool bEnableExperimentResPW, bModdedTanklist, bEnableCheats, bMapRotate, bUseWASD, bDevMode, bModdedTanklistCombined;

void Init()
{
	DWORD BaseAddress = (DWORD)GetModuleHandle(NULL);

	CIniReader iniReader("swinechdb.ini"); /// HDB Settings

	bModdedTanklist = iniReader.ReadInteger("Mods", "TanklistMod", 0);
	bModdedTanklistCombined = iniReader.ReadInteger("Mods", "TanklistModCombine", 0);
	bEnableExperimentResPW = iniReader.ReadInteger("Patchworks", "EnableExperimentResPW", 1);
	bEnableCheats = iniReader.ReadInteger("Patchworks", "EnableCheats", 0); // IF ANY OF THESE ARE TRUE, USE OUR SWINECHDB.EXE INSTEAD :)
	bMapRotate = iniReader.ReadInteger("Patchworks", "TESTNoMapRotate", 0); // otherwise unused code blob :>
	bUseWASD = iniReader.ReadInteger("Patchworks", "TESTRipArrowsUseWASD", 0);

	std::string TakeoverMD = "HDBEEFUP for SWINE Map Editor | dw5 | Compiled at " __DATE__ ", " __TIME__ " | ";
		//injector::WriteMemory<DWORD>(0x43A85E, (DWORD)((char*)strdup(TakeoverMD.c_str())), true);

 /* ====== Mods ====== */
	injector::WriteMemory<unsigned char>(0x42cc68, 0xEB, true); // Disable tamper check (JMP)

	//std::string fdb_unitsini = "gamedata\\" + basepath + "\\units.ini";
	//injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)strdup(fdb_unitsini.c_str())), true);

	//injector::WriteMemory<DWORD>(0x42cc50, (DWORD)((char*)"gamedata/units.ini"), true);

	//injector::WriteMemory<float>(0x4CB3A9, CamMaxZoomIn, true); // Max zoom in DEF: 10

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

if (!bModdedTanklistCombined){
	/*
std::string strDLD; std::copy(strDL.begin(), strDL.end(), strDLD);
std::string strDLN; std::copy(strDL.begin(), strDL.end(), strDLN);

/// for pigs:
      //strDLD.append("Ammo");
      //strDLD.append("Fuel");
      //strDLD.append("Service");
      strDLD.append("Akna");
      strDLD.append("Lato szem");
      strDLD.append("Lato kisszem");
      strDLD.append("Diszno zaszlo");
      strDLD.append("Zsiros Korom");
      strDLD.append("Nyalas Szaj");
	  	int nyulstringlenD = strDLD.size();
		char* aNyulDzsipD = new char[nyulstringlenD + 1];
		std::copy(strDLD.begin(), strDLD.end(), aNyulDzsipD);
		aNyulDzsipD[nyulstringlenD] = '\0';

		// calls to spot where campaign units are listed
		injector::WriteMemory<DWORD>(0x4199ef, (DWORD)aNyulDzsipD, true);
		
/// for rabbits:
      //strDLN.append("Ammo");
      //strDLN.append("Fuel");
     // strDLN.append("Service");
      strDLN.append("Akna");
      strDLN.append("Lato szem");
      strDLN.append("Lato kisszem");
      strDLN.append("Nyul zaszlo");
      strDLN.append("Kero");
      strDLN.append("Fogas Wili");
      strDLN.append("Point Roger");
      strDLN.append("Spy");
		int nyulstringlenN = strDLN.size();
		char* aNyulDzsipN = new char[nyulstringlenN + 1];
		std::copy(strDLN.begin(), strDLN.end(), aNyulDzsipN);
		aNyulDzsipN[nyulstringlenN] = '\0';

		// calls to spot where campaign units are listed
		injector::WriteMemory<DWORD>(0x4199ef, (DWORD)aNyulDzsipN, true);*/
} else {
	  
		//? injector::WriteMemory<unsigned char>(0x41995c, tanks, true); // ICON? HOW MANY TANKS DO WE HAVE FOR USE IN CAMPAIGN? (/p-01)

		int nyulstringlen = strDL.size();
		char* aNyulDzsip = new char[nyulstringlen + 1];
		std::copy(strDL.begin(), strDL.end(), aNyulDzsip);
		aNyulDzsip[nyulstringlen] = '\0';

		// calls to spot where campaign units are listed
		injector::WriteMemory<DWORD>(0x4199ef, (DWORD)aNyulDzsip, true);
		injector::WriteMemory<DWORD>(0x4199ef, (DWORD)aNyulDzsip, true);
		//injector::WriteMemory<DWORD>(0x5431B8, (DWORD)aNyulDzsip, true); // 0x5431B8 .. 0x5431b0 not worth to use
}

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