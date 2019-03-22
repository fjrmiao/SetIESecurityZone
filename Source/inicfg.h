#define DEFAULT_CONFIG_FILE_PATH ".\\setIEzone.ini"

struct structSiteMap{
	int Count;
	LPCSTR PartA[65535];
	LPCSTR PartB[65535];
};

struct structOptionDWORD{
	int Count;
	LPCSTR key[65535];
	DWORD Value[65535];
};

struct structZone{
	int ZoneID;
	struct structOptionDWORD OptionDW[];
	struct structSiteMap Site[];
};



struct structZonecConfig{
	int ZoneCount;
	struct structZone Zone[];
};

class IniConfig{

//PRIVATE
	private:

	LPCSTR lpConfigFilePath;//current config file path
	
	Initialize(){
		if(NULL!=lpConfigFilePath){
			printf("DO SOMETHING ABOUT READING INI FILE");
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
