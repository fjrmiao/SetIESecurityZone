#include <windows.h>
#include <winreg.h>
#include <string.h>

/***************************************************************************************************
 * Abstract from RegCreateKeyEx,RegSetValueEx,etc.                                                 *
 * Example:                                                                                        *
 *  SetRegKeyValue(HKEY_CURRENT_USER,path,key,REG_DWORD,(CONST BYTE*)&value,sizeof(DWORD));        *
 * Meaning:                                                                                        *
 *  Set key=value in HKEY_CURRENT_USER\path                                                        *
 ***************************************************************************************************/
WINAPI SetRegKeyValue(HKEY hKeyMain,LPCSTR lpSubKey, LPCSTR lpValueName,DWORD dwType,CONST BYTE *lpData,DWORD dwDataSize){
	HKEY hKey;
	RegCreateKeyEx(hKeyMain,TEXT(lpSubKey), 0, NULL,REG_OPTION_NON_VOLATILE,(REGSAM)NULL,NULL , &hKey,NULL) ;
	RegCloseKey(hKey);
	RegOpenKeyEx(hKeyMain,TEXT(lpSubKey), (DWORD)NULL, KEY_WRITE, &hKey) ;
	RegSetValueEx(hKey,TEXT(lpValueName),0,dwType,lpData,dwDataSize);
	RegCloseKey(hKey);
}  

/**********************************************
 * Set IE zone options                        *
 * Example:                                   *
 *    SetIEZoneOption(2,"Flags",67);          *
 * Meaning:                                   *
 *    Set Zone2's Option "Flags" = 67         *
 **********************************************/
int SetIEZoneOption(int iZoneID,LPCSTR lpKey,DWORD lpValue){
	char cstrFullZonePath [65535];
	sprintf( cstrFullZonePath, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\%i" , iZoneID );
	SetRegKeyValue(HKEY_CURRENT_USER,cstrFullZonePath,lpKey,REG_DWORD,(CONST BYTE*)&lpValue,sizeof(DWORD));
	
}

/*******************************************
 * Add a site to a IE zone                 *
 * Example:                                *
 *  SetZoneMap("www","example.com",2);     *
 * Meaning:                                *
 *  Add www.example.com to zone 2          *
 *******************************************/
int SetZoneMap(LPCSTR lpSitePart1,LPCSTR lpSitePart2,DWORD iZoneID){
	char cstrFullZonePath [65535];
	sprintf( cstrFullZonePath, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\ZoneMap\\Domains\\%s\\%s" , lpSitePart2,lpSitePart1 );
	SetRegKeyValue(HKEY_CURRENT_USER,cstrFullZonePath,"*",REG_DWORD,(CONST BYTE*)&iZoneID,sizeof(DWORD));
}
