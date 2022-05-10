#include <SPI.h>
#include <SD.h>

#ifdef __cplusplus
extern "C"{
#endif 

#include <time.h>
#include <string.h>

#ifdef __cplusplus
}
#endif

#define PIN_SD_CS 0 /* digital pin to which sd-card cs slot is connected on the board */
#define PIN_LED 0 /* digital pin to which a red led is connected */

#define PIN_CO A0 /* analog pin for CO */
#define PIN_CH4 A0 /* analog pin for methane */
#define PIN_O3 A0 /* analog pin for ozone */
#define PIN_CO2 A0 /* analog pin for carbon dioxide */

#define ms 5000 /* writing interval in milliseconds */

File file;
char header[] = "UTC_secs,CO_ppm,CH4_ppm,O3_ppb,CO2_ppm\n" /* currently 39 bytes */
char buf[50];
time_t utc_secs;
unsigned int CO;
unsigned int CH4;
unsigned int O3;
unsigned int CO2;

void setup()
{
	pinMode ( PIN_LED, OUTPUT );

	if ( !SD.begin( PIN_SD_CS ) )
	{
		digitalWrite ( PIN_LED, HIGH );
		while ( 1 );
	}

	SD.remove ( "log.csv" );
	
	file = SD.open ( "log.csv", FILE_WRITE );

	if ( file )
	{
		file.write(header, 39);
	}
}

void loop()
{
	buf = "";

#ifdef __cplusplus
extern "C"{
#endif 	
	
	/* utc time */
	utc_secs = time(NULL); /* seconds since January 1, 1970 */
	sprintf ( buf, "%ld", utc_secs );

#ifdef __cplusplus
}
#endif

	/* carbon monoxide in ppm */
	CO = analogRead ( PIN_CO );
#ifdef __cplusplus
extern "C"{
#endif 
	sprintf ( buf, "%u", CO );
#ifdef __cplusplus
}
#endif

	/* methane in ppm */
	CH4 = analogRead ( PIN_CH4 );
#ifdef __cplusplus
extern "C"{
#endif 
	sprintf ( buf, "%u", CH4 );
#ifdef __cplusplus
}
#endif

	/* ozone in ppb */
	O3 = analogRead ( PIN_O3 );
#ifdef __cplusplus
extern "C"{
#endif 
	sprintf ( buf, "%u", O3 );
#ifdef __cplusplus
}
#endif

	/* carbon dioxide in ppm */
	CO2 = analogRead ( PIN_CO2 );
#ifdef __cplusplus
extern "C"{
#endif 
	sprintf ( buf, "%u", CO2 );

	strcat ( buf, '\n' );
#ifdef __cplusplus
}
#endif
	
	file.write ( buf );
	
	delay ( ms );
}
