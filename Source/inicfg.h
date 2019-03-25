#define DEFAULT_CONFIG_FILE_PATH ".\\setIEzone.ini"

struct structSiteMap{
	int Count;
	LPCSTR *PartA;
	LPCSTR *PartB;
};

struct structOptionDWORD{
	int Count;
	LPCSTR *key;
	DWORD *Value;
};

struct structZone{
	int ZoneID;
	struct structOptionDWORD *OptionDW;
	struct structSiteMap *Site; 
	
};

struct structTempDWList{
	DWORD dw;
	struct structTempDWList *next;
};

struct structTempStrList{
	DWORD dw;
	LPCSTR str;
	struct structTempStrList *next;
};

struct structZonecConfig{
	int ZoneCount;
	struct structZone *Zone;
};

class IniConfig{

//PRIVATE
	private:

	LPCSTR lpConfigFilePath;//current config file path

	
	Str2DWList(struct structTempDWList *pDWListH,char *lpListStr){
		char lpSpliterChar[] = "|";
        LPCSTR lpTempSplitedChar= strtok(lpListStr,lpSpliterChar);
        struct structTempDWList *pDWList;
        pDWList = pDWListH;
        pDWListH->dw =0;
        while(lpTempSplitedChar){
            pDWListH->dw++;
            pDWList->next =  new struct structTempDWList();
            pDWList=pDWList->next;
            pDWList->dw = atoi(lpTempSplitedChar);
            lpTempSplitedChar=strtok(NULL,lpSpliterChar);
        }	
		pDWList->next =NULL;	
	}
	
	Str2StrList(struct structTempStrList *pStrListH,char *lpListStr){
		char lpSpliterChar[] = "|";
        LPCSTR lpTempSplitedChar= strtok(lpListStr,lpSpliterChar);
        struct structTempStrList *pStrList;
        pStrList = pStrListH;
        pStrListH->dw =0;
        while(lpTempSplitedChar){
            pStrListH->dw++;
            pStrList->next =  new struct structTempStrList();
            pStrList=pStrList->next;
            pStrList->str = lpTempSplitedChar;
            lpTempSplitedChar=strtok(NULL,lpSpliterChar);
        }	
		pStrList->next =NULL;	
	}
	
	SetZonebyDWList(struct structZonecConfig *ZoneCfg,struct structTempDWList *pDWListH){
		struct structTempDWList *pDWList;
		DWORD iTempCount = 0;
		ZoneCfg->ZoneCount=pDWListH->dw;
		ZoneCfg->Zone = new struct structZone[ZoneCfg->ZoneCount];
		pDWList = pDWListH;
		while(NULL != pDWList->next){
			pDWList = pDWList->next;
			ZoneCfg->Zone[iTempCount++].ZoneID =pDWList->dw;
		}	
	}
	

	Initialize(){
		if(NULL!=lpConfigFilePath){
			
			//read ini file common section
			char lpZoneList[256];
			char lpOptionList[256];
			DWORD iZoneListSize = GetPrivateProfileString("Common","Zone","",lpZoneList,256,lpConfigFilePath);
			DWORD iOptionListSize = GetPrivateProfileString("Common","Option","",lpOptionList,256,lpConfigFilePath);	
			
			//process zone key
			struct structTempDWList pDWZoneListH;
			Str2DWList(&pDWZoneListH,lpZoneList);
			SetZonebyDWList(&ZoneCfg,&pDWZoneListH);
			
			//process option key
			struct structTempStrList pStrOptionListH;
			Str2StrList(&pStrOptionListH,lpOptionList);
			//SetZonebyDWList(&ZoneCfg,&pDWZoneListH);
			
			printf("***DO SOMETHING ABOUT add option info to struct zonecfg***"); 
			printf("%s,%s",lpZoneList,lpOptionList);
			
			system("pause");
		}
	}


//PUBLIC
	public:
	
	struct structZonecConfig ZoneCfg;
	
	IniConfig(LPCSTR lpFileName){
		//if file exist,read the file;or return empty object;  
		DWORD dwAttr = GetFileAttributes(lpFileName);
		if (INVALID_FILE_ATTRIBUTES == dwAttr || 0 != (dwAttr & FILE_ATTRIBUTE_DIRECTORY)){
			lpConfigFilePath=NULL;
			return;
		}
		lpConfigFilePath=lpFileName;
		Initialize();
	}
	
	IniConfig(){
		//use default config file
		IniConfig(DEFAULT_CONFIG_FILE_PATH);
	} 
	
	
	LPCSTR getCfgFilePath(){
		//get current config file path,
		return lpConfigFilePath;
	} 
	
};
