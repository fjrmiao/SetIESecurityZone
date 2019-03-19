#include <iostream>
#include <windows.h>
#include <winreg.h>
#include <string.h>
/****************************** 
 * Develop by DEV-C++ 5.11    * 
 ******************************/

WINAPI SetRegKeyValue(HKEY hKeyMain,LPCSTR lpSubKey, LPCSTR lpValueName,DWORD dwType,CONST BYTE *lpData,DWORD dwDataSize){
	HKEY hKey;
	RegCreateKeyEx(hKeyMain,TEXT(lpSubKey), 0, NULL,REG_OPTION_NON_VOLATILE,(REGSAM)NULL,NULL , &hKey,NULL) ;
	RegCloseKey(hKey);
	RegOpenKeyEx(hKeyMain,TEXT(lpSubKey), (DWORD)NULL, KEY_WRITE, &hKey) ;
	RegSetValueEx(hKey,TEXT(lpValueName),0,dwType,lpData,dwDataSize);
	RegCloseKey(hKey);
}  

int SetIEZoneOption(int iZoneID,LPCSTR lpKey,DWORD lpValue){
	char cstrFullZonePath [65535];
	sprintf( cstrFullZonePath, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\%i" , iZoneID );
	SetRegKeyValue(HKEY_CURRENT_USER,cstrFullZonePath,lpKey,REG_DWORD,(CONST BYTE*)&lpValue,sizeof(DWORD));
	
}

int SetZoneMap(LPCSTR lpSitePart1,LPCSTR lpSitePart2,DWORD iZoneID){
	char cstrFullZonePath [65535];
	sprintf( cstrFullZonePath, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\ZoneMap\\Domains\\%s\\%s" , lpSitePart2,lpSitePart1 );
	SetRegKeyValue(HKEY_CURRENT_USER,cstrFullZonePath,"*",REG_DWORD,(CONST BYTE*)&iZoneID,sizeof(DWORD));
}
int main(int argc, char** argv) {
	DWORD dwValue = 2;
	SetIEZoneOption(2,"Flags",67);
	SetIEZoneOption(2,"1200",0);
	SetIEZoneOption(2,"1201",0);
	SetIEZoneOption(2,"1208",0);
	SetIEZoneOption(2,"1405",0);
	SetIEZoneOption(2,"2000",0);
	SetZoneMap("www","example.com",2);
	return 0;
}
