//#include "RTC.h"
#include <DS3231.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// initialize the stepper library on pins 10, 12, 11, 13
Stepper myStepper(stepsPerRevolution, 10, 12, 11, 13);
int stepCount = 0;  // number of steps the motor has taken
int rpm = 10;

void setup() {
  Serial.begin(9600);

  setClock();
  setAlarms();

  // set pin 10 as output, for the motor
  pinMode(10, OUTPUT);
}

void setClock() {
  // get date/time from DS3231 module
  DS3231 ds3231rtc;
  Wire.begin();

  // store date/time in Arduino RTC (Real-Time Clock)
  bool h12;
  bool hPM;
  bool CenturyBit;
  setTime(ds3231rtc.getHour(h12, hPM),ds3231rtc.getMinute(),ds3231rtc.getSecond(),ds3231rtc.getDate(),ds3231rtc.getMonth(CenturyBit),ds3231rtc.getYear());
  
  // Old version, using RTC.h
  //RTC.begin();
  //RTCTime startTime(ds3231rtc.getDate(), ds3231rtc.getMonth(), ds3231rtc.getYear(), ds3231rtc.getHour(), ds3231rtc.getMinute(), ds3231rtc.getSecond(), ds3231rtc.getDoW(), SaveLight::SAVING_TIME_ACTIVE);
  //RTC.setTime(startTime);
}

void setAlarms()
{
  // TimeAlarms library can store at most 6 alarms
  Alarm.alarmRepeat(21,00,0, feedAnimals);  // 20:45 every day
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void feedAnimals()
  // Turn on lights
{
   int motorSpeed(rpm);
  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(rpm); 
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution);
  } 
  delay(50000); // Wait 50 seconds
 // Play sound
 // Send signal to HomeAssistant via lora
  

  
}
