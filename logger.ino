#include <SPI.h>
#include <SD.h>
#include <time.h>
#include <string.h>

#define PIN_SD_CS 0 /* digital pin to which sd-card cs slot is connected on the board */
#define PIN_LED 0 /* digital pin to which a red led is connected */

#define PIN_CO A0 /* analog pin for CO */
#define PIN_CH4 A0 /* analog pin for methane */
#define PIN_O3 A0 /* analog pin for ozone */

#define ms 5000 /* delay between writing data to sd card */

File file;
char header[] = "UTC_secs,CO_ppm,CH4_ppm,O3_ppb\n" /* currently 31 bytes */
char buf[50];
time_t utc_secs;
unsigned int CO;
unsigned int CH4;
unsigned int O3;

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
		file.write(header, 31);
	}
}

void loop()
{
	buf = "";
	
	/* utc time */
	utc_secs = time(NULL); /* seconds since January 1, 1970 */
	sprintf ( buf, "%ld", utc_secs );

	/* carbon monoxide in ppm */
	CO = analogRead ( PIN_CO );
	sprintf ( buf, "%u", CO );

	/* methane in ppm */
	CH4 = analogRead ( PIN_CH4 );
	sprintf ( buf, "%u", CH4 );

	/* ozone in ppb */
	O3 = analogRead ( PIN_O3 );
	sprintf ( buf, "%u", O3 );

	strcat ( buf, '\n' );
	file.write ( buf );
	
	delay ( ms );
}
