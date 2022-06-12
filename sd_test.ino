#include <SD.h>

#define PIN_SD_SS 4

File file;

void setup ()
{
	SD.begin( PIN_SD_SS );
	SD.remove( "log.csv" );
	file = SD.open ( "log.csv", FILE_WRITE );
	if (file) 
	{
		file.write("Test");
		file.close();
	}
}
