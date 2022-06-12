#include <SPI.h>
#include <SD.h>
#include <time.h>
#include <stdio.h>

#define PIN_SD_SS 4/* digital pin to which sd-card ss slot is connected on the board */
#define PIN_LED_RED 0
#define PIN_LED_GREEN 0 

#define PIN_CO A0 /* analog pin for CO */
#define PIN_CH4 A0 /* analog pin for methane */
#define PIN_O3 A0 /* analog pin for ozone */
#define PIN_CO2 A0 /* analog pin for carbon dioxide */

#define ms 5000 /* writing interval in milliseconds */

File file;
char header[] = "UTC_secs,CO_ppm,CH4_ppm,O3_ppb,CO2_ppm\n" /* currently 39 bytes */
char buf[26];
time_t utc_secs; 
unsigned int CO;
unsigned int CH4;
unsigned int O3;
unsigned int CO2;

void setup()
{
	pinMode ( PIN_LED_RED, OUTPUT );
	pinMode ( PIN_LED_GREEN, OUTPUT );

	if ( !SD.begin( PIN_SD_CS ) )
	{
		digitalWrite ( PIN_LED_RED, HIGH );
		while ( 1 );
	}

	SD.remove ( "log.csv" );
	
	file = SD.open ( "log.csv", FILE_WRITE );

	if ( file )
	{
		file.write(header, 39);
		digitalWrite ( PIN_LED_GREEN, HIGH );
	}
}

void loop()
{
	buf = {''};

	/* utc time */
	time(&utc_secs); /* seconds since January 1, 1970 */
	sprintf ( buf, "%ld,", (long)utc_secs );

	/* carbon monoxide in ppm */
	CO = analogRead ( PIN_CO );
	sprintf ( buf, "%u,", CO );

	/* methane in ppm */
	CH4 = analogRead ( PIN_CH4 );
	sprintf ( buf, "%u,", CH4 );

	/* ozone in ppb */
	O3 = analogRead ( PIN_O3 );
	sprintf ( buf, "%u,", O3 );

	/* carbon dioxide in ppm */
	CO2 = analogRead ( PIN_CO2 );
	sprintf ( buf, "%u\n", CO2 );

	file.write ( buf );
	
	delay ( ms );
}
