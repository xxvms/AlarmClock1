#include <Wire.h>
#include <RTClib.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
int buzzer = 11;
int potentiometerPin = 0;
int potentiometerPin1 = 1;
int potentiometerVal = 0;
int potentiometerVal1 = 0;
int hourSet;
int minSet;


LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
RTC_DS1307 rtc;

void setup() {
	Wire.begin();
	lcd.begin(16, 2);
	lcd.backlight();
	rtc.begin();
	rtc.adjust(DateTime(__DATE__, __TIME__));
	pinMode(buzzer, OUTPUT);
	lcd.print("  Good Day to you");
	delay(1000);
	lcd.clear();
}

void loop() {
	DateTime now = rtc.now();
	lcd.setCursor(0, 1);
	lcd.print(" Time: ");
	if (now.hour()<10)
	{
		lcd.print("0");
	}
	lcd.print(now.hour(), DEC);
	lcd.print(':');
	if (now.minute()<10)
	{
		lcd.print("0");
	}
	lcd.print(now.minute(), DEC);
	lcd.print(':');
	if (now.second()<10)
	{
		lcd.print("0");
	}
	lcd.print(now.second(), DEC);
	//Alarm.alarmRepeat(12, 11, 0, MorningAlarm);


	delay(100);
	// ALARM Below
	
	hourSet = analogRead(potentiometerPin);
	minSet = analogRead(potentiometerPin1);
	int setAlarm = map(hourSet, 0, 1023, 0, 23), map(minSet, 0, 1023, 0, 59);
	if (hourSet & minSet == rtc.now)
	{
		digitalWrite(buzzer, HIGH);
		lcd.print("Rise & Shine");
		delay(10000);
	}
	else
	{
		digitalWrite(buzzer, LOW);
	}
}