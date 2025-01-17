#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

/* Begin Additional Code */
#include <DallasTemperature.h>

/* Onewire bus */
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3

void setup()
{
    while (!Serial)
        ; // for Leonardo/Micro/Zero

    Serial.begin(115200);
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    } // end rtc.begin()

    // if (!rtc.isrunning())
    // {
    //     Serial.println("RTC is NOT running!");
    //     // following line sets the RTC to the date & time this sketch was compiled
    //     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //     // This line sets the RTC with an explicit date & time, for example to set
    //     // January 21, 2014 at 3am you would call:
    //     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    // }
    sensors.begin();
}

void loop()
{

    DateTime now = rtc.now();

    //buffer can be defined using following combinations:
    //hh - the hour with a leading zero (00 to 23)
    //mm - the minute with a leading zero (00 to 59)
    //ss - the whole second with a leading zero where applicable (00 to 59)
    //YYYY - the year as four digit number
    //YY - the year as two digit number (00-99)
    //MM - the month as number with a leading zero (01-12)
    //MMM - the abbreviated English month name ('Jan' to 'Dec')
    //DD - the day as number with a leading zero (01 to 31)
    //DDD - the abbreviated English day name ('Mon' to 'Sun')

    char buf1[] = "hh:mm";
    Serial.println(now.toString(buf1));

    // char buf2[] = "YYMMDD-hh:mm:ss";
    // Serial.println(now.toString(buf2));

    // char buf3[] = "Today is DDD, MMM DD YYYY";
    // Serial.println(now.toString(buf3));

    // char buf4[] = "MM-DD-YYYY";
    // Serial.println(now.toString(buf4));

    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(sensors.getTempCByIndex(0));

    delay(1000);
}