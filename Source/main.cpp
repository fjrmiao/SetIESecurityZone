#include <iostream>
#include "iezone.h"
/****************************** 
 * Develop by DEV-C++ 5.11    * 
 ******************************/


int main(int argc, char** argv) {
	SetIEZoneOption(2,"Flags",67);
	SetIEZoneOption(2,"1200",0);
	SetIEZoneOption(2,"1201",0);
	SetIEZoneOption(2,"1208",0);
	SetIEZoneOption(2,"1405",0);
	SetIEZoneOption(2,"2000",0);
	SetZoneMap("www","example.com",2);
	return 0;
}
